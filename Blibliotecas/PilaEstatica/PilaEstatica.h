#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_PILA 300


typedef struct
{
  char vec[TAM_PILA];
  unsigned tope;
}t_pila;

void CrearPila(t_pila *pp);
int PonerEnPila(t_pila * pp,const void * dato,size_t tam);
int SacarDePila(t_pila * pp,void *dato,size_t tam);
int VerTope(const t_pila *pp,void *dato,size_t tam);
int PilaVacia(const t_pila *pp);
int PilaLlena(const t_pila *pp,size_t tam);
void VaciarPila(t_pila *pp);

#endif // FUNCIONES_H_INCLUDED
