#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stddef.h>
#include "../Lista/Lista.h"

// --- Códigos de retorno ---

#define DIC_OK 1
#define DIC_ERROR 0
#define DIC_ERROR_MEMORIA -1
#define DIC_CLAVE_DUPLICADA 2
#define DIC_CLAVE_NO_ENCONTRADA -2

typedef size_t (*funcion_hash_t)(const void* clave, size_t tamClave);
typedef int (*funcion_comparacion_t)(const void* clave1, const void* clave2, size_t tamClave);
typedef void (*accion_dic_t)(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);

typedef struct
{
    tLista *tabla;      // Vector de punteros a tNodo (cada puntero es una cabeza de lista)
    size_t capacidad;   // Cantidad de buckets (tamaño del vector tabla)
    size_t cantidad;    // Cantidad total de elementos (pares clave-valor) en el diccionario
    funcion_hash_t func_hash;
} tDiccionario;

// Esta estructura es la que realmente se almacena en cada nodo de las listas
typedef struct tElementoDic
{
    void* clave;
    size_t tamClave;
    void* valor;
    size_t tamValor;
} tElementoDic;

// --- Prototipos de Funciones ---

int crear_dic(tDiccionario* dic, size_t capacidad, funcion_hash_t hash_func_param);
int poner_dic(tDiccionario* dic, const void* clave, size_t tamClave, const void* valor, size_t tamValor);
int obtener_dic(const tDiccionario* dic, const void* clave, size_t tamClave, void* valor, size_t tamValorDestino);
int sacar_dic(tDiccionario* dic, const void* clave, size_t tamClave);
void recorrer_dic(tDiccionario* dic, accion_dic_t accion, void* contexto);
void vaciar_dic(tDiccionario* dic);


size_t hash_simple(const void* clave, size_t tamClave); //anda a saber q mierda es este
size_t hash_string(const void *clave, size_t tamClave); //djb2


#endif // DICCIONARIO_H_INCLUDED
