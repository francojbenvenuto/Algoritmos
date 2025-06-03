#include "Diccionario.h"

int crear_dic(tDiccionario* dic, size_t capacidad)
{
    dic->tabla = (tLista*) malloc(sizeof(tLista) * capacidad);
    //Al hacer esto no es necesario llamar a la funcion crear lista
    if(!dic->tabla)
        return ERROR;

    for (size_t i = 0; i < capacidad; i++)
    {
        dic->tabla[i] = NULL;
    }
    dic->capacidad = capacidad;
    dic->cantidad = 0;
    return 1;
}

int poner_dic(tDiccionario* dic, const void* clave, size_t tamClave,const void* valor, size_t tamValor,size_t (*hash)(const void*, size_t))
{
    size_t indice = hash(clave, tamClave) % dic->capacidad;
    tLista *lista = &dic->tabla[indice];
    tNodo *Actual = *lista;

    ////FUNCION A CHEQUEAR PORQUE NO ENTIENDO///////
    while(Actual)
    {
        tElementoDic *elem = (tElementoDic *)Actual->info;


        if(elem->tamClave == tamClave && memcmp(elem->clave,clave,tamClave)== 0)
        {
            ///manejar repeticiones de claves(imagino que hay que descartarlas)/////

            return 0;
        }
        Actual = Actual->sig;
    }
    /////////////////////////////////////////////////////

    // Crear el nuevo elemento del diccionario
    tElementoDic nuevo;

    // Copiar la clave
    nuevo.clave = malloc(tamClave);
    if (!nuevo.clave)
        return 0;
    memcpy(nuevo.clave, clave, tamClave);
    nuevo.tamClave = tamClave;

    // Copiar el valor
    nuevo.valor = malloc(tamValor);
    if (!nuevo.valor)
    {
        free(nuevo.clave);
        return 0;
    }
    memcpy(nuevo.valor, valor, tamValor);
    nuevo.tamValor = tamValor;

    // Insertar el elemento en la lista del bucket
    if (!poner_primero_lista(lista, &nuevo, sizeof(tElementoDic)))
    {
        free(nuevo.clave);
        free(nuevo.valor);
        return 0;
    }

    dic->cantidad++;
    return 1;

}

int obtener_dic(const tDiccionario* dic, const void* clave, size_t tamClave, void* valor, size_t tamValor, size_t (*hash)(const void*, size_t))
{

    size_t indice = hash(clave, tamClave) % dic->capacidad;
    tLista lista = dic->tabla[indice];
    tNodo* actual = lista;

    while (actual) {
        tElementoDic* elem = (tElementoDic*)actual->info;

        if (elem->tamClave == tamClave && memcmp(elem->clave, clave, tamClave) == 0) {
            // Encontramos la clave, copiamos el valor al buffer
            size_t bytesACopiar = (tamValor < elem->tamValor) ? tamValor : elem->tamValor;
            memcpy(valor, elem->valor, bytesACopiar);
            return 1;
        }

        actual = actual->sig;
    }

    return 0; // No se encontró la clave
}


//////Funcion de Hash////
size_t hash_simple(const void* clave, size_t tamClave)
{
    const unsigned char* bytes = (const unsigned char*)clave;
    size_t hash = 0;
    for (size_t i = 0; i < tamClave; i++)
        hash += bytes[i];
    return hash;
}



////////FUNCIONES DE LISTA////////////
int poner_primero_lista(tLista *pl, const void *pd, size_t tam)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0; ///LISTA_LLENA
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0; ///LISTA_LLENA
    }

    nue->tamInfo = tam;
    memcpy(nue->info,pd,tam);
    nue->sig = *pl;

    *pl = nue;

    return 1; ///OK
}





