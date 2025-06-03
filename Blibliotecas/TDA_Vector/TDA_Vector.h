#ifndef TDA_VECTOR_H_INCLUDED
#define TDA_VECTOR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    void *vec;
    size_t tamElem;
    size_t cap;
    int ce;
}Vector;

typedef int (*Cmp)(const void*, const void*);
typedef void(*Accion)(void*);

bool crearVector(Vector *v,size_t tamElem, size_t cap);
bool redimensionar (Vector * v, size_t nuevacap);
void destruirVector(Vector *v);
int insertarAlFinal(Vector *v,const void* elem);
int insertarEnOrden(Vector *v,void* elem, Cmp cmp);
bool VectorEliminarOrdenado(Vector *v,void* elem, Cmp cmp);
bool vectorBuscarOrdenado(const Vector *v,void *elem,Cmp cmp);


void OrdenarSeleccion(Vector *v, Cmp cmp);
void * buscarMenor(void *ini, void *fin, size_t tamElem, Cmp cmp);
void intercambiarGen(void *a, void *b, size_t tamElem);
void Ordenamiento_burbujeo(void *vec,size_t tamElem,int ce,Cmp cmp);
int ordenarInsercion(void *vec, int cantElem, size_t tamElem, Cmp cmp);


void mostrar(const Vector *v, Accion accion);

#endif // TDA_VECTOR_H_INCLUDED
