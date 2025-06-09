#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include"..\t_diccionario\t_diccionario.h"
#include"..\Lista\Lista.h"

#define MAX_RUTA_ARCHIVO 512
#define MAX_LARGO_PALABRA 100
#define OK 0
#define ERROR -1


void ProcesarRuta(char *rutaArchivo);
void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales);
void accion_imprimir_dic(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);
void BajarPalabras(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);
int cmptElem(const void *a, const void *b);
void mostrarPodioDic(tLista *pl);
void mostrar_lista_dic(tLista *pl);

#endif // FUNCIONES_H_INCLUDED
