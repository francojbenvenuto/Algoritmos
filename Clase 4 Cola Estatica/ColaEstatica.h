#ifndef COLAESTATICA_H_INCLUDED
#define COLAESTATICA_H_INCLUDED


#include <string.h>
#include <stdlib.h>

#define TAM_COLA 300

typedef struct
{
    char cola[TAM_COLA];
    size_t pri,ult,tamDisp;
}tCola;

void CrearCola(tCola *pc);
int ColaLlena(tCola *pc, size_t tam);
int ponerEnCola(tCola *pc, const void *pd, size_t tam);
int verPrimeroCola(const tCola *pc, void *pd, size_t tam);
int colaVacia(const tCola *pc);
int sacarDeCola(tCola *pc, void *pd, size_t tam);
void vaciarCola(tCola *pc);


#endif // COLAESTATICA_H_INCLUDED
