#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

typedef struct {
    int id;
    char nombre[30];
    float precio;
} Producto;

typedef struct sNodo
{
    void * info;
    size_t tamInfo;
    struct sNodo * sig;
}tNodo;

typedef tNodo * tPila;

void crear_pila(tPila * pp);

int poner_en_pila(tPila * pp, const void * pd, size_t tamDato);
int sacar_de_pila(tPila * pp, void * pd, size_t tamDato);
int ver_tope_pila(const tPila * pp, void * pd, size_t tamDato);

int pila_vacia(const tPila * pp);
int pila_llena(const tPila * pp, size_t tamDato);

void vaciar_pila(tPila * pp);






#endif // FUNCIONES_H_INCLUDED
