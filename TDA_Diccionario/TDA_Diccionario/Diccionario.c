#include "Diccionario.h"

int crear_dic(tDiccionario* dic, size_t capacidad)
{
    // Es buena práctica verificar si dic es NULL antes de usarlo
    if (!dic) return DIC_ERROR; // O tu código de error preferido

    // calloc es mejor aquí porque inicializa la memoria a cero (todos los punteros a NULL)
    dic->tabla = (tLista*) calloc(capacidad, sizeof(tLista));
    if(!dic->tabla)
        return DIC_ERROR_MEMORIA; // Error específico de memoria

    // No es necesario el bucle si usas calloc:
    // for (size_t i = 0; i < capacidad; i++)
    // {
    //     dic->tabla[i] = NULL;
    // }

    dic->capacidad = capacidad;
    dic->cantidad = 0;
    return DIC_OK; // Éxito
}

int poner_dic(tDiccionario* dic, const void* clave, size_t tamClave, const void* valor, size_t tamValor, funcion_hash_t hash) // Usando el typedef
{
    if (!dic || !clave || !valor || !hash) return DIC_ERROR; // Validaciones básicas
    if (dic->capacidad == 0) return DIC_ERROR; // Evitar división por cero si capacidad es 0

    size_t indice = hash(clave, tamClave) % dic->capacidad;
    tLista *pListaEnBucket = &dic->tabla[indice]; // Puntero a la cabeza de la lista en el bucket
    tNodo *Actual = *pListaEnBucket;

    // Buscar si la clave ya existe para ACTUALIZAR el valor
    while(Actual)
    {
        tElementoDic *elem = (tElementoDic *)Actual->info;
        if(elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0)
        {
            // Clave encontrada, actualizar valor
            // Primero, liberar el valor antiguo si es de diferente tamaño o si prefieres siempre reemplazar
            if (elem->tamValor != tamValor)   // Opcional: solo reemplazar si el tamaño cambia
            {
                free(elem->valor);
                elem->valor = malloc(tamValor);
                if (!elem->valor)
                {
                    // Aquí la situación es complicada: no pudimos actualizar.
                    // Podrías dejar el valor viejo o retornar un error crítico.
                    // Por simplicidad, muchos TDA podrían retornar error aquí.
                    return DIC_ERROR_MEMORIA;
                }
            }
            else if (!elem->valor && tamValor > 0)     // Si antes no había valor o era NULL
            {
                elem->valor = malloc(tamValor);
                if(!elem->valor) return DIC_ERROR_MEMORIA;
            }
            else if (elem->valor && tamValor == 0)     // Si el nuevo valor es "nada"
            {
                free(elem->valor);
                elem->valor = NULL;
            }
            // Si elem->valor ya tiene el tamaño correcto, podemos reusar el buffer
            // o si es NULL y tamValor es 0, no hacer nada.
            if (tamValor > 0 && elem->valor)   // Solo copiar si hay algo que copiar y dónde copiar
            {
                memcpy(elem->valor, valor, tamValor);
            }
            elem->tamValor = tamValor;
            return DIC_OK; // Éxito (valor actualizado)
        }
        Actual = Actual->sig;
    }

    // Si la clave no existe, crear el nuevo elemento y agregarlo
    tElementoDic nuevoElemento; // Se crea en el stack temporalmente

    nuevoElemento.clave = malloc(tamClave);
    if (!nuevoElemento.clave)
        return DIC_ERROR_MEMORIA;
    memcpy(nuevoElemento.clave, clave, tamClave);
    nuevoElemento.tamClave = tamClave;

    nuevoElemento.valor = malloc(tamValor);
    if (!nuevoElemento.valor)
    {
        free(nuevoElemento.clave);
        return DIC_ERROR_MEMORIA;
    }
    memcpy(nuevoElemento.valor, valor, tamValor);
    nuevoElemento.tamValor = tamValor;

    // Insertar el nuevoElemento (que contiene punteros a la clave y valor copiados)
    // en la lista del bucket. poner_primero_lista DEBE copiar nuevoElemento.
    if (!poner_primero_lista(pListaEnBucket, &nuevoElemento, sizeof(tElementoDic)))
    {
        free(nuevoElemento.clave);
        free(nuevoElemento.valor);
        return DIC_ERROR_MEMORIA; // O error genérico de lista
    }

    dic->cantidad++;
    return DIC_OK; // Éxito (nuevo elemento insertado)
}

// Asegúrate que el prototipo esté en Diccionario.h
int obtener_dic(const tDiccionario* dic, const void* clave, size_t tamClave, void* valorDestino, size_t tamValorDestino, funcion_hash_t hash)
{
    if (!dic || !clave || !valorDestino || !hash) return DIC_ERROR;
    if (dic->capacidad == 0) return DIC_ERROR;


    size_t indice = hash(clave, tamClave) % dic->capacidad;
    tLista listaBucket = dic->tabla[indice]; // No es puntero a lista, es la lista (el puntero al primer nodo)
    tNodo* actual = listaBucket;

    while (actual)
    {
        tElementoDic* elem = (tElementoDic*)actual->info;

        if (elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0)
        {
            // Clave encontrada. Copiar el valor al buffer del usuario.
            // Asegurarse de no copiar más de lo que cabe en el buffer destino.
            size_t bytesACopiar = (tamValorDestino < elem->tamValor) ? tamValorDestino : elem->tamValor;
            memcpy(valorDestino, elem->valor, bytesACopiar);
            // Sería útil informar al usuario cuántos bytes se copiaron,
            // o si el buffer era muy pequeño. Podrías retornar 'bytesACopiar'.
            // O si la función solo retorna éxito/fracaso, entonces 1 (DIC_OK).
            return DIC_OK;
        }
        actual = actual->sig;
    }
    return DIC_CLAVE_NO_ENCONTRADA; // No se encontró la clave
}

int sacar_dic(tDiccionario* dic, const void* clave, size_t tamClave, funcion_hash_t hash)
{
    if (!dic || !clave || !hash) return DIC_ERROR;
    if (dic->capacidad == 0) return DIC_ERROR;

    size_t indice = hash(clave, tamClave) % dic->capacidad;
    tLista *pLista = &(dic->tabla[indice]);
    tNodo *actual = *pLista;
    tNodo *anterior = NULL;

    while(actual != NULL)
    {
        tElementoDic *elem = (tElementoDic *)actual->info;
        if(elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0)
        {
            // Encontrado. Eliminarlo de la lista.
            if(anterior == NULL)   // Es el primer nodo de la lista
            {
                *pLista = actual->sig;
            }
            else
            {
                anterior->sig = actual->sig;
            }
            // Liberar memoria del elemento (clave, valor) y del nodo mismo
            free(elem->clave);
            free(elem->valor);
            free(elem); // elem es actual->info
            free(actual); // el nodo de la lista
            dic->cantidad--;
            return DIC_OK;
        }
        anterior = actual;
        actual = actual->sig;
    }
    return DIC_CLAVE_NO_ENCONTRADA; // No encontrado
}



 void recorrer_dic(tDiccionario* dic, accion_dic_t accion, void* contexto) {
     if (!dic || !accion) return;

     for (size_t i = 0; i < dic->capacidad; i++) {
         tNodo* actual = dic->tabla[i];
         while (actual != NULL) {
             tElementoDic* elem = (tElementoDic*)actual->info;
             accion(elem->clave, elem->tamClave, elem->valor, elem->tamValor, contexto);
             actual = actual->sig;
        }
     }
 }


//////Funciones de Hash////


size_t hash_simple(const void* clave, size_t tamClave)
{
    const unsigned char* bytes = (const unsigned char*)clave;
    size_t hash = 0;
    for (size_t i = 0; i < tamClave; i++)
        hash += bytes[i];
    return hash;
}

// Función de hash para strings (djb2)
size_t hash_string(const void *clave)
{
    const char *str = clave;
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}
