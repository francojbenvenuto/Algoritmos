#include "Lista.h"

void crear_lista(tLista *pl)
{
    *pl = NULL;
}

int listaVacia(const tLista *p)
{
    return *p == NULL;
}

int listaLlena(const tLista *p, size_t tam)
{
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(tam);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

int vaciarLista(tLista *p)
{
    int cant = 0;
    tNodo *aux;
    while(*p)
    {
        aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
        cant++;
    }
    return cant;
}

int vaciarListaYMostrar(tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    int cant = 0;
    tNodo *aux;
    while(*p)
    {
        aux = *p;
        *p = aux->sig;

        if(mostrar)
        {
            mostrar(aux->info, fp);
        }

        free(aux->info);
        free(aux);
        cant++;
    }
    return cant;
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

int verPrimeroLista(const tLista *p, void *d, size_t tam)
{
    if (*p == NULL)
        return 0;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
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

int sacarUltimoLista(tLista *p, void *d, size_t tam)
{
    if (!*p)
        return 0;
    while ((*p)->sig)
        p = &(*p)->sig;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    free((*p)->info);
    free(*p);
    *p = NULL;
    return 1;
}

int verUltimoLista(const tLista *p, void *d, size_t tam)
{
    if (!*p)
        return 0;
    while ((*p)->sig)
        p = &(*p)->sig;
    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    return 1;
}

int mostrarListaAlReves(const tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    if (*p)
    {
        int n = mostrarListaAlReves(&(*p)->sig, mostrar, fp);
        if (mostrar)
        {
            mostrar((*p)->info, fp);
        }
        return n + 1;
    }
    return 0;
}

int mostrarListaAlRevesYVaciar(tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp)
{
    if (*p)
    {
        int n = mostrarListaAlRevesYVaciar(&(*p)->sig, mostrar, fp);

        if (mostrar)
        {
            mostrar((*p)->info, fp);
        }
        free((*p)->info);
        free(*p);
        *p = NULL;
        return n + 1;
    }
    return 0;
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

int poner_orden_lista_con_duplicados(tLista *pl, const void *pd, size_t tam, int (*cmp)(const void*,const void*))
{
    tNodo *nue;
    int rc;

    while(*pl && (rc = cmp(pd, (*pl)->info)) > 0)
        pl = &(*pl)->sig;
    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->sig = *pl;

    *pl = nue;

    return 1;
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
