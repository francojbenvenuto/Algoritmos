#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PILA 100
#define OK 1
#define PILA_LLENA 0
#define PILA_VACIA 0

typedef struct
{
  char vec[TAM_PILA];
  unsigned tope;
}t_pila;

int Min(int a,int b);
int PonerEnPila(t_pila * pp,const void * dato,size_t tam);
int SacarDePila(t_pila * pp,void *dato,size_t tam);
void CrearPila(t_pila *pp);
void VaciarPila(t_pila *pp);
int PilaVacia(const t_pila *pp);
int PilaLlena(const t_pila *pp,size_t tam);
int VerTope(t_pila *pp,void *dato,size_t tam);

#endif // FUNCIONES_H_INCLUDED
