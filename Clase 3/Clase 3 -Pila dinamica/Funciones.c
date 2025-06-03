#include"Funciones.h"

void crear_pila(tPila * pp)
{
    *pp = NULL;
}

int poner_en_pila(tPila * pp, const void * pd, size_t tam)
{
    tNodo * nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue)
    {
        return 0; ///PILA_LLENA
    }
    nue->info = malloc(tam);
    if (!nue->info)
    {
        free(nue);
        return 0; ///PILA_LLENA
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);

    nue->sig = *pp;

    *pp = nue;
    return 1; ///OK
}

int sacar_de_pila(tPila * pp, void * pd, size_t tam)
{
    tNodo * elim = *pp;
    if(!*pp)
    {
        return 0; ///PILA_VACIA
    }

    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tam));
    *pp = elim->sig;

    free(elim->info);
    free(elim);
    return 1; ///OK
}

int ver_tope_pila(const tPila * pp, void * pd, size_t tamDato)
{
    tNodo *aux  = *pp;
    if(*pp == NULL)
    {
        return 0;
    }
    memcpy(pd,aux->info,MINIMO(tamDato,aux->tamInfo));
    return 1;
}

int pila_vacia(const tPila * pp)
{
    return *pp == NULL;
}

int pila_llena(const tPila * pp, size_t tam)
{
    void * nodo = malloc(sizeof(tNodo));
    void * info = malloc(tam);
    free(nodo);
    free(info);

    return !nodo || !info;
}

void vaciar_pila(tPila * pp)
{
    while(*pp)
    {
        tNodo * elim = *pp;
        *pp = elim->sig;
        free(elim->info);
        free(elim);
    }
}
