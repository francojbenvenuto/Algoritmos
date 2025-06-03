#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tpila;

void CrearPila(tpila *pp);
int PonerEnPila(tpila *pp,const void*pd,size_t tamDato);
int SacarDePila(tpila *pp,void *pd,size_t tamDato);
int VerTope(const tpila *pp,void *pd, size_t tamDato);
int PilaVacia(const tpila *pp);
int PilaLlena(const tpila *pp, size_t tamDato);
void VaciarPila(tpila *pp);

#endif // PILACIRCULAR_H_INCLUDED
