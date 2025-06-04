#include "Lista.h"

void crear_lista(tLista *pl)
{
    *pl = NULL;
}

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

int sacar_primero_lista(tLista *pl, void *pd, size_t tam)
{
    tNodo *elim = *pl;
    if(!*pl)
        return 0; ///LISTA_VACIA
    memcpy(pd, elim->info, MINIMO(elim->tamInfo,tam));
    *pl = elim->sig;

    free(elim->info);
    free(elim);
    return 1; ///OK
}

int poner_ultimo_lista(tLista *pl, const void *pd, size_t tam)
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

    while(*pl)
        pl = &(*pl)->sig;

    nue->tamInfo = tam;
    memcpy(nue->info,pd,tam);
    nue->sig = *pl;

    *pl = nue;

    return 1; ///OK
}

int poner_pos_lista(tLista *pl, const void *pd, size_t tam, unsigned pos)
{
    tNodo *nue;

    while(*pl && pos)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    ///Esta validacion depende de la definicion del problema
    if(pos)
        return 0; ///Pos invalida

    nue = (tNodo*)malloc(sizeof(tNodo));
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

int poner_orden_lista(tLista *pl, const void *pd, size_t tam, int (*cmp)(const void*,const void*))
{
    tNodo * nue;
    int rc;

    while(*pl && (rc=cmp(pd,(*pl)->info))>0)
        pl = &(*pl)->sig;
    if(*pl && !rc)
        return 0; ///DUPLICADO
    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0; ///LISTA_LLENA
    nue->info = malloc(tam);
    if(!nue->tamInfo)
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

int sacar_elem_lista(tLista *pl, void *pd, size_t tam, int (*cmp)(const void*,const void*))
{
    tNodo *elim;
    while(*pl && cmp(pd,(*pl)->info)!=0)
        pl = &(*pl)->sig;
    if(!*pl)
        return 0; ///NO_EXISTE
    elim = *pl;
    memcpy(pd, elim->info, MINIMO(tam, elim->tamInfo));

    *pl = elim->sig;
    free(elim->info);
    free(elim);

    return 1; ///0K
}

int sacar_elem_ord_lista(tLista *pl, void *pd, size_t tam, int (*cmp)(const void*,const void*))
{
    tNodo *elim;
    int rc;
    while(*pl && (rc=cmp(pd,(*pl)->info))>0)
        pl = &(*pl)->sig;
    if(!*pl || rc)
        return 0; ///NO_EXISTE

    elim = *pl;
    memcpy(pd, elim->info, MINIMO(tam,elim->tamInfo));

    *pl = elim->sig;
    free(elim->info);
    free(elim);

    return 1; ///OK
}

void recorrerLista(tLista *pl, void (*accion)(void*,void*),void *param)
{
    while(*pl)
    {
        accion((*pl)->info, param);
        pl = &(*pl)->sig;
    }
}

///SOLO PARA TESTING!!!
void mostrar_lista(tLista *pl)
{
    while(*pl)
    {
        printf("-%d-", *((int*)(*pl)->info));
        pl=&(*pl)->sig;
    }
}

void reinsertar_nodo_menor(tLista *pl, tLista *men)
{
    tNodo *aux = *men;
    *men = aux->sig;

    aux->sig = *pl;
    *pl = aux;
}

void intercambio_info_nodos(tLista *n1, tLista *n2)
{
    unsigned aux_tam;
    void *aux = (*n1)->info;
    (*n1)->info = (*n2)->info;
    (*n2)->info = aux;

    aux_tam = (*n1)->tamInfo;
    (*n1)->tamInfo = (*n2)->tamInfo;
    (*n2)->tamInfo = aux_tam;
}

tNodo ** buscar_menor_nodo_lista(const tLista * pl, int (*cmp)(const void*, const void*))
{
    const tLista * men = pl;
    if (!*pl)
    {
        return NULL;
    }
    pl=&(*pl)->sig;
    while(*pl)
    {
        if(cmp((*pl)->info, (*men)->info)<0)
        {
            men = pl;
        }
        pl=&(*pl)->sig;
    }
    return (tNodo **)men;
}

void ordenar_sel_lista(tLista * pl, int (*cmp)(const void*, const void*))
{
    if(!*pl)
        return;
    while((*pl)->sig)
    {
        tNodo ** men = buscar_menor_nodo_lista(pl, cmp);
        if(pl != men)
        {
            //intercambio_info_nodos(pl, men);
            reinsertar_nodo_menor(pl, men);
        }
        pl= &(*pl)->sig;
    }
}

/**
1 - buscar menor
2 - intercambiar
3 - avanzar
**/

void eliminarDuplicadosListaOrdenada(tLista * pl, int (*cmp)(const void*, const void*), void (*accion) (void *, const void*))
{
    tLista * aux;
    tNodo * pelim;
    while(*pl)
    {
        aux = &(*pl)->sig;
        while(*aux && !cmp((*pl)->info, (*aux)->info))
        {
            accion((*pl)->info, (*aux)->info);
            pelim = *aux;
            *aux = pelim->sig;
            free(pelim->info);
            free(pelim);
        }
        pl = &(*pl)->sig;
    }
}
