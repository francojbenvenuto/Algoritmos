#ifndef COLACIRCULAR_H_INCLUDED
#define COLACIRCULAR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tCola;

void CrearCola(tCola *pc);
int PonerEnCola(tCola *pc,const void *pd,size_t tam);
int SacarDeCola(tCola *pc,void *pd,size_t tam);
int VerPrimeroEnCola(const tCola *pc,void *pd, size_t tam);
int ColaLlena(const tCola *pc, size_t tam);
int ColaVacia(const tCola *pc);
void VaciarCola(tCola *pc);



#endif // COLACIRCULAR_H_INCLUDED
