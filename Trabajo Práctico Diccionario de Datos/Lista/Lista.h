#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

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

typedef tNodo *tLista;

void crear_lista(tLista *pl);
int vaciarLista(tLista *p);

int listaVacia(const tLista *p);
int listaLlena(const tLista *p, size_t tam);
int vaciarListaYMostrar(tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp);
int verPrimeroLista(const tLista *p, void *d, size_t tam);
int sacarUltimoLista(tLista *p, void *d, size_t tam);
int verUltimoLista(const tLista *p, void *d, size_t tam);
int mostrarListaAlReves(const tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp);
int mostrarListaAlRevesYVaciar(tLista *p, void (*mostrar)(const void *, FILE *), FILE *fp);

int poner_primero_lista(tLista *pl,const void *pd, size_t tam);
int sacar_primero_lista(tLista *pl,void *pd, size_t tam);
int poner_ultimo_lista(tLista *pl,const void *pd, size_t tam);

int poner_pos_lista(tLista *pl,const void *pd, size_t tam,unsigned pos);
int poner_orden_lista(tLista *pl,const void *pd,size_t tam, int (*cmp)(const void*,const void*));
int poner_orden_lista_con_duplicados(tLista *pl, const void *pd, size_t tam, int (*cmp)(const void*,const void*));


int sacar_elem_lista(tLista *pl, void *pd, size_t tam, int (*cmp)(const void*,const void*));
int sacar_elem_ord_lista(tLista *pl, void *pd, size_t tam, int (*cmp)(const void*,const void*));

void ordenar_sel_lista(tLista *pl, int (*cmp)(const void*,const void*));

void recorrerLista(tLista *pl, void (*accion)(void*,void*), void *param);

void eliminarDuplicadosListaOrdenada(tLista *pl, int (*cmp)(const void*,const void*),void (*accion)(void*,const void*));

///SOLO PARA TESTING!!!
void mostrar_lista(tLista *pl);


#endif // LISTA_H_INCLUDED
