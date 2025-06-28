#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
/** *************************************************************************
 **     arbol_bin_busq.h    declaraci�n primitivas  TDA �RBOL  bin. de b�squeda
 ** *********************************************************************** */
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define CLA_DUP 0
#define SIN_MEM 0
#define SIN_INICIALIZAR 0
#define ERROR_ARCH 0
#define TODO_BIEN 1


typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
}tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;



void crearArbolBinBusq(tArbolBinBusq *p);

int insertarArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                         int (*cmp)(const void *, const void *));

int insertarRecArbolBinBusq(tArbolBinBusq *p, const void *d, unsigned tam,
                            int (*cmp)(const void*, const void *));

void recorrerEnOrdenArbolBinBusq(const tArbolBinBusq * p, void * params,
                                 void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenInversoArbolBinBusq(const tArbolBinBusq * p, void * params,
                                        void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPreOrdenArbolBinBusq(const tArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPosOrdenArbolBinBusq(const tArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                       void (*accion)(void *, unsigned, void *));

void recorrerPreOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                        void (*accion)(void *, unsigned, void *));

void recorrerPosOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                        void (*accion)(void *, unsigned, void *));

int eliminarRaizArbolBinBusq(tArbolBinBusq *p);

int eliminarElemArbolBinBusq(tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *));

int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *));

int cargarArchivoBinOrdenadoAbiertoArbolBinBusq(tArbolBinBusq *p, FILE *pf,
                                         unsigned tamInfo);

int cargarArchivoBinOrdenadoArbolBinBusq(tArbolBinBusq * p, const char * path,
                                         unsigned tamInfo);

int cargarDesdeDatosOrdenadosArbolBinBusq(tArbolBinBusq *p,
                        void *ds, unsigned cantReg,
                        int (*leer)(void*, void *, unsigned, size_t tam),
                        size_t tam);


int mayorElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

int menorElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

int buscarElemNoClaveArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

void eliminarElemNoClaveArbol(tArbolBinBusq *p, void *d,
                             int (*cmp)(const void *, const void *));

int cargarDesdeArchivoPreOrdenArbol(tArbolBinBusq * p,
                                    const char * path,
                                    unsigned tamInfo,
                                    int (*cmp)(const void *, const void *));

int cargarDesdeDatosPreOrdenArbol(tArbolBinBusq *p,
                        void *ds, unsigned cantReg,
                        int (*leer)(void *,void *, unsigned, size_t tam),
                        int (*cmp)(const void *, const void *),
                        size_t tam);



///Utils

unsigned alturaArbolBin(const tArbolBinBusq *p);

unsigned cantNodosArbolBin(const tArbolBinBusq *p);

unsigned cantNodosHastaNivelArbolBin(const tArbolBinBusq *p, int n);

int mayorElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam);

int menorElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam);

int esCompletoArbolBin(const tArbolBinBusq *p);

int esBalanceadoArbolBin(const tArbolBinBusq *p);

int esAVLArbolBin(const tArbolBinBusq *p);

int esCompleto2ArbolBin(const tArbolBinBusq *p);

int esBalanceado2ArbolBin(const tArbolBinBusq *p);

int esAVL2ArbolBin(const tArbolBinBusq *p);

#endif // ARBOL_H
