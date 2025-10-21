#include "t_diccionario.h"

int crear_dic(tDiccionario* dic, size_t capacidad, funcion_hash_t hash_param)
{
    if (!dic || !hash_param)
        return DIC_ERROR;

    dic->tabla = (tLista*) calloc(capacidad, sizeof(tLista)); // calloc es para inicializar en null y no tener errores de acceso a memoria no inicializada
    if(!dic->tabla)
        return DIC_ERROR_MEMORIA;

    dic->capacidad = capacidad;
    dic->cantidad = 0;
    dic->func_hash = hash_param;
    return DIC_OK;
}

int poner_dic(tDiccionario* dic, const void* clave, size_t tamClave, const void* valor, size_t tamValor)
{
    if (!dic || !clave || !valor || !dic->func_hash)
        return DIC_ERROR;
    if (dic->capacidad == 0)
        return DIC_ERROR;

    size_t indice = dic->func_hash(clave, tamClave) % dic->capacidad;
    tLista *pListaEnBucket = &dic->tabla[indice]; // Puntero a la cabeza de la lista en el bucket
    tNodo *Actual = pListaEnBucket;

    /* calculo el indice de la posicion de la clave en la tabla, y con una tabla de búsqueda se busca la clave
       si la clave no existe, se devuelve DIC_CLAVE_NO_ENCONTRADA,
       igualamos un nodo actual a la cabeza de la lista del bucket, para recorrer cada nodo de la lista*/

    while(Actual) // Buscar si la clave ya existe para ACTUALIZAR el valor
    {
        tElementoDic *elem = (tElementoDic *)Actual->info;
        if(elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0)
        {
            // Clave encontrada, actualizar valor

            free(elem->valor);    
            elem->valor = malloc(tamValor);
            memcpy(elem->valor, valor, tamValor);
            
            // Si elem->valor ya tiene el tamano correcto, podemos reusar el buffer
            // o si es NULL y tamValor es 0, no hacer nada.

            elem->tamValor = tamValor;
            return DIC_OK;
        }

        Actual = Actual->sig; //si no se encuentra, se pasa al siguiente nodo (manejo de colisiones)
    }
//=========================================================================================================================================
//  Si la clave no existe, crear el nuevo elemento y agregarlo
//=========================================================================================================================================
    // Crear un nuevo elemento diccionario    
    tElementoDic nuevoElemento;

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
        return DIC_ERROR_MEMORIA;
    }

    dic->cantidad++;
    return DIC_OK;
}

int obtener_dic(const tDiccionario* dic, const void* clave, size_t tamClave, void* valorDestino, size_t tamValorDestino)
{
    if (!dic || !clave || !valorDestino || !dic->func_hash)
        return DIC_ERROR;
    if (dic->capacidad == 0)
        return DIC_ERROR;

    size_t indice = dic->func_hash(clave, tamClave) % dic->capacidad;
    tLista listaBucket = dic->tabla[indice];
    tNodo* actual = listaBucket; 
    /* calculo el indice de la posicion de la clave en la tabla, y con una tabla de búsqueda se busca la clave
       si la clave no existe, se devuelve DIC_CLAVE_NO_ENCONTRADA,
       igualamos un nodo actual a la cabeza de la lista del bucket, para recorrer cada nodo de la lista*/
    
    while (actual)
    {
        tElementoDic* elem = (tElementoDic*)actual->info;

        if (elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0)
        {
            // Clave encontrada. Copiar el valor al buffer del usuario.
            size_t bytesACopiar = (tamValorDestino < elem->tamValor) ? tamValorDestino : elem->tamValor;
            memcpy(valorDestino, elem->valor, bytesACopiar);
            // se copia el valor almacenado en el nodo actual a la variable del usuario
            return DIC_OK;
        }
        actual = actual->sig; //si no se encuentra, se pasa al siguiente nodo (manejo de colisiones)
    }
    return DIC_CLAVE_NO_ENCONTRADA;
}

int sacar_dic(tDiccionario* dic, const void* clave, size_t tamClave)
{
    if (!dic || !clave || !dic->func_hash)
        return DIC_ERROR;
    if (dic->capacidad == 0)
        return DIC_ERROR;

    size_t indice = dic->func_hash(clave, tamClave) % dic->capacidad;
    tLista *pLista = &(dic->tabla[indice]);
    tNodo *actual = *pLista;
    tNodo *anterior = NULL;

    while(actual != NULL)
    {
        tElementoDic *elem = (tElementoDic *)actual->info;
        if(elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0)
        {
            // Encontrado. Eliminarlo de la lista.
            if(anterior == NULL)
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
            free(elem);
            free(actual);
            dic->cantidad--;
            return DIC_OK;
        }
        anterior = actual;
        actual = actual->sig;
    }
    return DIC_CLAVE_NO_ENCONTRADA;
}

 void recorrer_dic(tDiccionario* dic, accion_dic_t accion, void* contexto)
 {
     if (!dic || !accion)
        return;

     for (size_t i = 0; i < dic->capacidad; i++)
     {
         tNodo* actual = dic->tabla[i];
         while (actual != NULL)
         {
             tElementoDic* elem = (tElementoDic*)actual->info;
             accion(elem->clave, elem->tamClave, elem->valor, elem->tamValor, contexto);
             actual = actual->sig;
         }
     }
 }


void vaciar_dic(tDiccionario* dic)
{
    if (!dic)
        return;

    for (size_t i = 0; i < dic->capacidad; i++)
    {
        tNodo* actual = dic->tabla[i];
        while (actual != NULL)
        {
            tNodo* siguiente = actual->sig; // Guardar el siguiente antes de liberar 'actual'
            tElementoDic* elem = (tElementoDic*)actual->info;
            free(elem->clave);
            free(elem->valor);
            free(elem);
            free(actual);
            actual = siguiente;
        }
        dic->tabla[i] = NULL;
    }
    free(dic->tabla);
    dic->tabla = NULL;
    dic->cantidad = 0;
    dic->capacidad = 0;
 }


void imprimir_clave_valor_str(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto)
{
    const char* str_clave = (const char*)clave;
    const char* str_valor = (const char*)valor;

    printf("Clave: [%s] -> Valor: [%s]\n", str_clave, str_valor);
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

// Funcion de hash (djb2)
size_t hash_string(const void *clave, size_t tamClave)
{
    const char *str = (const char *)clave;
    size_t hash = 5381; // Valor inicial comun para djb2
    size_t i;

    for (i = 0; i < tamClave; i++)
        hash = ((hash << 5) + hash) + str[i]; // hash * 33 + str[i]

    return hash;
}
