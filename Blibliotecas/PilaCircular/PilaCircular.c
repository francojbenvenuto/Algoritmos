#include "PilaCircular.h"
#include <stdio.h>

void CrearPila(tpila *pp)
{
    *pp = NULL;
}

int PonerEnPila(tpila *pp,const void*pd,size_t tamDato)
{
    tNodo *nue;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;

    if(*pp == NULL)
    {
        nue->sig = nue;
        *pp = nue;
    }
    else
    {
        nue->sig = (*pp)->sig;
        (*pp)->sig = nue;
    }

    return 1;
}

int SacarDePila(tpila *pp,void *pd,size_t tamDato)
{
    tNodo *aux;

    if(*pp == NULL)
        return 0;
    aux = (*pp)->sig;
    memcpy(pd, aux->info, MINIMO(tamDato, aux->tamInfo));
    if(aux == *pp)
        *pp = NULL;
    else
        (*pp)->sig = aux->sig;

    free(aux->info);
    free(aux);
    return 1;
}

int VerTope(const tpila *pp,void *pd, size_t tamDato)
{
    tNodo *aux = *pp;
    if(!*pp)
        return 0;
    memcpy(pd,aux->info,MINIMO(aux->tamInfo,tamDato));
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
        tNodo *aux = (*pp)->sig;
        if(*pp == aux)
            *pp = NULL;
        else
            (*pp)->sig = aux->sig;
        free(aux->info);
        free(aux);
    }
}
