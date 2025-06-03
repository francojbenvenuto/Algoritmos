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
int PonerEnCola(tCola *pc, const void *pd, size_t tam);
int SacarDeCola(tCola *pc, void *pd, size_t tam);
int VerPrimeroEnCola(const tCola *pc, void *pd, size_t tam);
int ColaLlena(tCola *pc, size_t tam);
int ColaVacia(const tCola *pc);
void VaciarCola(tCola *pc);

#endif // COLAESTATICA_H_INCLUDED
