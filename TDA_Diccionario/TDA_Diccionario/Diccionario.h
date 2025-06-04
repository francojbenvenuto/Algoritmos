#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #define ERROR -1 // Ya existe EXIT_FAILURE en stdlib.h, o puedes usar 0 para error y 1 para OK

// --- AGREGAR stddef.h para size_t y stdbool.h para bool ---
#include <stddef.h> // Para size_t
#include <stdbool.h> // Para bool, true, false (si usas booleanos para retornos)
#include "../Lista/Lista.h"

// --- C�digos de retorno sugeridos (opcional, pero ayuda a la legibilidad) ---
#define DIC_OK 1
#define DIC_ERROR 0 // O -1 si prefieres, pero s� consistente
#define DIC_ERROR_MEMORIA -1 // Ejemplo m�s espec�fico
#define DIC_CLAVE_DUPLICADA 2 // Ejemplo para poner_dic si no actualiza
#define DIC_CLAVE_NO_ENCONTRADA -2 // Ejemplo

typedef struct
{
    tLista *tabla;      // Vector de punteros a tNodo (cada puntero es una cabeza de lista)
    size_t capacidad;   // Cantidad de buckets (tama�o del vector tabla)
    size_t cantidad;    // Cantidad total de elementos (pares clave-valor) en el diccionario
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

// El typedef para la funci�n hash es una buena pr�ctica:
typedef size_t (*funcion_hash_t)(const void* clave, size_t tamClave);
// El typedef para la funci�n de comparaci�n (si la a�ades expl�citamente)
// typedef int (*funcion_comparacion_t)(const void* clave1, const void* clave2, size_t tamClave);
// El typedef para la funci�n de acci�n de recorrer_dic
typedef void (*accion_dic_t)(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);


int crear_dic(tDiccionario* dic, size_t capacidad); // [cite: 9]

int poner_dic(tDiccionario* dic, const void* clave, size_t tamClave,
              const void* valor, size_t tamValor,
              funcion_hash_t hash); // [cite: 10] Cambiado el tipo del par�metro hash

// Prototipo para obtener_dic (est� en tu .c pero no aqu�)
int obtener_dic(const tDiccionario* dic, const void* clave, size_t tamClave,
                void* valor, size_t tamValorDestino, // Renombrado para claridad
                funcion_hash_t hash); // [cite: 11] A�adido aqu�

// Primitivas Faltantes (seg�n el PDF [cite: 12, 13])
int sacar_dic(tDiccionario* dic, const void* clave, size_t tamClave, funcion_hash_t hash);
void recorrer_dic(tDiccionario* dic, accion_dic_t accion, void* contexto);
void vaciar_dic(tDiccionario* dic); // Si solo libera internos. Si libera 'dic' mismo y *dic=NULL, necesita tDiccionario**

// Funciones de utilidad que ya tienes
size_t hash_simple(const void* clave, size_t tamClave); // Prototipo
int poner_primero_lista(tLista *pl, const void *pd, size_t tam); // Prototipo


// En Diccionario.h (o donde tengas tus typedefs)
typedef void (*accion_dic_t)(const void* clave, size_t tamClave,
                             void* valor, size_t tamValor,
                             void* contexto);

#endif // DICCIONARIO_H_INCLUDED
