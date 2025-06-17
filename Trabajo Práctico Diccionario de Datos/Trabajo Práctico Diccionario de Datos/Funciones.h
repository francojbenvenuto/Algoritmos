#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
// ANSI para windows 10 y evitar error en windows 11 :)
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
// =========================================================================

#include"..\t_diccionario\t_diccionario.h"
#include"..\Lista\Lista.h"

#define MAX_RUTA_ARCHIVO 512
#define MAX_LARGO_PALABRA 100
#define OK 0
//#define ERROR -1  //incuido en windows.h

void ProcesarRuta(char *rutaArchivo);
void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales);
void accion_imprimir_dic(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);

int ActualizarPodio(tLista *LPodio, const void *ElemNuevo, size_t tamElemen, int (*cmp)(const void*,const void*));
void BajarPalabras(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);
void BajarPalabrasPodio(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);
void *ObtenerMenorPuntaje(tLista* LPodio, int (*cmp)(const void*,const void*));
void liberarNodos(tLista *pl);
int cmptElem(const void *a, const void *b);
void mostrarPodioDic(tLista *LPodio);
void mostrar_lista_dic(tLista *pl);

#endif // FUNCIONES_H_INCLUDED
