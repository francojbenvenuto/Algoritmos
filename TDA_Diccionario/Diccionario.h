#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -1

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;


typedef struct
{
    tLista *tabla;       // Vector de listas (cada uno es una cabeza de lista de nodos)
    size_t capacidad;    // Cantidad de buckets
    size_t cantidad;     // Cantidad total de elementos en el diccionario
} tDiccionario;

typedef struct tElementoDic{
    void* clave;
    size_t tamClave;
    void* valor;
    size_t tamValor;
} tElementoDic;

int crear_dic(tDiccionario* dic, size_t capacidad);
int poner_dic(tDiccionario* dic, const void* clave, size_t tamClave,
              const void* valor, size_t tamValor,
              size_t (*hash)(const void*, size_t));

size_t hash_simple(const void* clave, size_t tamClave);

int poner_primero_lista(tLista *pl, const void *pd, size_t tam);








#endif // DICCIONARIO_H_INCLUDED
