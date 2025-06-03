#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MINIMO(X,Y) ((X)<(Y) ? (X): (Y))

typedef struct sNodo {
    void *info;
    unsigned tamInfo;
    struct sNodo *sig;
} tNodo;

typedef struct {
    tNodo *pri, *ult;
} tCola;

void crearCola(tCola *p);
int  colaLlena(const tCola *p, unsigned cantBytes);
int  ponerEnCola(tCola *p, const void *d, unsigned cantBytes);
int  verPrimeroCola(const tCola *p, void *d, unsigned cantBytes);
int  colaVacia(const tCola *p);
int  sacarDeCola(tCola *p, void *d, unsigned cantBytes);
void vaciarCola(tCola *p);


