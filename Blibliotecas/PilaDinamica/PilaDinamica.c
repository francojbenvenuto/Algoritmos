#include "PilaDinamica.h"

void CrearPila(tpila *pp)
{
    *pp=NULL;
}

int PonerEnPila(tpila *pp,const void*pd,size_t tamDato)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->info = malloc(tamDato);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    nue->tamInfo = tamDato;
    memcpy(nue->info,pd,tamDato);
    nue->sig = *pp;
    *pp=nue;

    return 1;
}

int SacarDePila(tpila *pp,void *pd, size_t tamDato)
{
    tNodo *elim = *pp;
    if(!*pp)
        return 0;
    memcpy(pd,elim->info,MINIMO(elim->tamInfo,tamDato));
    *pp = elim->sig;
    free(elim->info);
    free(elim);
    return 1;
}

int PilaVacia(const tpila *pp)
{
    return *pp == NULL;
}

int PilaLlena(const tpila *pp, size_t tamDato)
{
    void *nodo = malloc(sizeof(tNodo));
    void *info = malloc(tamDato);
    free(nodo);
    free(info);

    return !nodo || !info;
}

void VaciarPila(tpila *pp)
{
    while(*pp)
    {
        tNodo * elim = *pp;
        *pp = elim->sig;
        free(elim->info);
        free(elim);
    }
}

int VerTope(const tpila *pp,void *pd, size_t tamDato)
{
    tNodo *aux = *pp;
    if(!*pp)
        return 0;
    memcpy(pd,aux->info,MINIMO(aux->tamInfo,tamDato));
    return 1;
}
