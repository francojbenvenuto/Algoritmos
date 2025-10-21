/** *************************************************************************
 **     arbol_bin_busq.h    declaración primitivas  TDA ÁRBOL  bin. de búsqueda
 ** *********************************************************************** */

#ifndef ARBOL_BIN_BUSQ_H_INCLUDED
#define ARBOL_BIN_BUSQ_H_INCLUDED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#ifndef TODO_OK
    #define TODO_OK 1
#endif // TODO_OK
#ifndef SIN_MEM
    #define SIN_MEM 2
#endif // SIN_MEM
#ifndef ERROR_ARCHIVO
    #define ERROR_ARCHIVO 3
#endif // ERROR_ARCHIVO
#ifndef DUPLICADO
    #define DUPLICADO 4
#endif // DUPLICADO
#ifndef NO_EXISTE
    #define NO_EXISTE 5
#endif // NO_EXISTE
#ifndef SIN_INICIALIZAR
    #define SIN_INICIALIZAR 6
#endif // SIN_INICIALIZAR


typedef struct sNodoArbol
{
    void *info;
    unsigned tamInfo;
    struct sNodoArbol *izq,
                      *der;
}tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;



void crearArbolBinBusq_res(tArbolBinBusq *p);

int insertarArbolBinBusq_res(tArbolBinBusq *p, const void *d, unsigned tam,
                         int (*cmp)(const void *, const void *));

int insertarRecArbolBinBusq_res(tArbolBinBusq *p, const void *d, unsigned tam,
                            int (*cmp)(const void*, const void *));

void recorrerEnOrdenArbolBinBusq_res(const tArbolBinBusq * p, void * params,
                                 void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenInversoArbolBinBusq_res(const tArbolBinBusq * p, void * params,
                                        void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPreOrdenArbolBinBusq_res(const tArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *));

void recorrerPosOrdenArbolBinBusq_res(const tArbolBinBusq * p, void * params,
                                  void (*accion)(void *, unsigned, unsigned, void *));

void recorrerEnOrdenSimpleArbolBinBusq_res(const tArbolBinBusq *p, void *params,
                                       void (*accion)(void *, unsigned, void *));

void recorrerPreOrdenSimpleArbolBinBusq_res(const tArbolBinBusq *p, void *params,
                                        void (*accion)(void *, unsigned, void *));

void recorrerPosOrdenSimpleArbolBinBusq_res(const tArbolBinBusq *p, void *params,
                                        void (*accion)(void *, unsigned, void *));

int eliminarRaizArbolBinBusq_res(tArbolBinBusq *p);

int eliminarElemArbolBinBusq_res(tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *));

int buscarElemArbolBinBusq_res(const tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *));

int cargarArchivoBinOrdenadoAbiertoArbolBinBusq_res(tArbolBinBusq *p, FILE *pf,
                                         unsigned tamInfo);

int cargarArchivoBinOrdenadoArbolBinBusq_res(tArbolBinBusq * p, const char * path,
                                         unsigned tamInfo);

int cargarDesdeDatosOrdenadosArbolBinBusq_res(tArbolBinBusq *p,
                        void *ds, unsigned cantReg,
                        unsigned (*leer)(void **, void *, unsigned, void *params),
                        void * params);


int mayorElemNoClaveArbolBinBusq_res(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

int menorElemNoClaveArbolBinBusq_res(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

int buscarElemNoClaveArbolBinBusq_res(const tArbolBinBusq *p, void *d, unsigned tam,
                                 int (*cmp)(const void *, const void *));

void eliminarElemNoClaveArbol_res(tArbolBinBusq *p, void *d,
                             int (*cmp)(const void *, const void *));

int cargarDesdeArchivoPreOrdenArbol_res(tArbolBinBusq * p,
                                    const char * path,
                                    unsigned tamInfo,
                                    int (*cmp)(const void *, const void *));

int cargarDesdeDatosPreOrdenArbol_res(tArbolBinBusq *p,
                        void *ds, unsigned cantReg,
                        unsigned (*leer)(void **, void *, unsigned, void *params),
                        int (*cmp)(const void *, const void *),
                        void * params);

int grabarEnArchivoOrdenadoArbolBin_res(tArbolBinBusq *p, const char * path);

///Utils

unsigned alturaArbolBin_res(const tArbolBinBusq *p);

unsigned cantNodosArbolBin_res(const tArbolBinBusq *p);

unsigned cantNodosHastaNivelArbolBin_res(const tArbolBinBusq *p, int n);

int mayorElemArbolBinBusq_res(const tArbolBinBusq *p, void *d, unsigned tam);

int menorElemArbolBinBusq_res(const tArbolBinBusq *p, void *d, unsigned tam);

int esCompletoArbolBin_res(const tArbolBinBusq *p);

int esBalanceadoArbolBin_res(const tArbolBinBusq *p);

int esAVLArbolBin_res(const tArbolBinBusq *p);

int esCompleto2ArbolBin_res(const tArbolBinBusq *p);

int esBalanceado2ArbolBin_res(const tArbolBinBusq *p);

int esAVL2ArbolBin_res(const tArbolBinBusq *p);

void vaciarArbolBin_res(tArbolBinBusq *p);

void arbolGrafico_res(const tArbolBinBusq *p, void(*mostrar)(const void *));



///************ NO RESUELTAS *************///

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
                        unsigned (*leer)(void **, void *, unsigned, void *params),
                        void * params);


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
                        unsigned (*leer)(void **, void *, unsigned, void *params),
                        int (*cmp)(const void *, const void *),
                        void * params);

int grabarEnArchivoOrdenadoArbolBin(tArbolBinBusq *p, const char * path);

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

void vaciarArbolBin(tArbolBinBusq *p);

void arbolGrafico(const tArbolBinBusq *p, void(*mostrar)(const void *));

#endif // ARBOL_BIN_BUSQ_H_INCLUDED

