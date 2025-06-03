#include "PilaEstatica.h"

#define MINIMO(X,Y)((X)<(Y)?(X):(Y))

int PonerEnPila(t_pila * pp,const void * dato,size_t tam)
{
    if(pp->tope < tam+sizeof(size_t))
        return 0;
    pp->tope-=tam;
    memcpy(pp->vec+pp->tope,dato,tam);
    pp->tope-=sizeof(size_t);
    memcpy(pp->vec+pp->tope,&tam,sizeof(size_t));
    return 1;
}

int SacarDePila(t_pila * pp,void *dato,size_t tam)
{
    size_t tam_pila;
    if(pp->tope==TAM_PILA)
        return 0;
    memcpy(&tam_pila,pp->vec+pp->tope,sizeof(size_t));
    pp->tope += sizeof(size_t);
    memcpy(dato,pp->vec+pp->tope,MINIMO(tam,tam_pila));
    pp->tope += tam_pila;
    return 1;
}

void CrearPila(t_pila *pp)
{
    pp->tope  = TAM_PILA;
}

int VerTope(const t_pila *pp,void *dato,size_t tam)
{
    size_t tam_pila;
    if(pp->tope == TAM_PILA)
        return 0;
    int pos = pp->tope;
    memcpy(&tam_pila,pp->vec+pos,sizeof(size_t));
    pos+=sizeof(size_t);
    memcpy(dato,pp->vec+pos,MINIMO(tam,tam_pila));
    return 1;
}

void VaciarPila(t_pila *pp)
{
    pp->tope  = TAM_PILA;
}

int PilaVacia(const t_pila *pp)
{
    if(pp->tope==TAM_PILA)
        return 0;
    else return 1;
}

int PilaLlena(const t_pila *pp,size_t tam)
{
    if(pp->tope==0)
        return 0;
    else return 1;
}
