#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_MEM 0
#define TODO_BIEN 1
#define CLA_DUP 2

typedef struct sNodo
{
    void           *info;
    size_t        tamInfo;
    struct sNodo   *sig,
                   *ant;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *pl);
int vaciarLista(tLista *pl);
int listaVacia(const tLista *pl);
int listaLlena(const tLista *pl, size_t tam);
int insertarAlFinal(tLista *pl, const void *pd, size_t tam);
int insertarAlComienzo(tLista *pl, const void *pd, size_t tam);
int mostrarDeIzqADer(const tLista *pl,
                     void (*mostrar)(const void *));
int mostrarDeDerAIzq(const tLista *pl,
                     void (*mostrar)(const void *));
int insertarEnOrden(tLista *pl, const void *pd, size_t tam,
                    int (*comparar)(const void *, const void *),
                    int (*acumular)(void **, size_t *,
                                    const void *, size_t));
void ordenarLista(tLista *pl, int (*comparar)(const void *, const void *));
int eliminarPorClave(tLista *pl, void *pd, size_t tam,
                     int (*comparar)(const void *, const void *));


#endif // LISTADOBLE_H_INCLUDED
