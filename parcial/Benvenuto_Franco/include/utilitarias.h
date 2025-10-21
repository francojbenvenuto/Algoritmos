#ifndef UTILITARIAS_H_INCLUDED
#define UTILITARIAS_H_INCLUDED
#include<stdio.h>
#include<arbol.h>
#include<tipos.h>


void restaurarPrueba_res(char * path_arch_alu, char* path_arch_ind);

int alta_res (tAlumno * alu, FILE * arch, tArbolBinBusq* pa);
int alta (tAlumno * alu, FILE * arch, tArbolBinBusq* pa);

int baja_res (tAlumno * alu, FILE * arch, tArbolBinBusq* pa);
int baja (tAlumno * alu, FILE * arch, tArbolBinBusq* pa);

int bajaUltimo_res (FILE * arch, tArbolBinBusq* pa);
int baja_ultimo (FILE * arch, tArbolBinBusq* pa);

int agregarMateria_res(FILE * arch, tArbolBinBusq * pindice);
int agregar_materia(FILE * arch, tArbolBinBusq * pindice);

int compactarYReindexar_res(FILE ** arch, tArbolBinBusq * pindice, const char * path);
int compactar_y_reindexar(FILE ** arch, tArbolBinBusq * pindice, const char * path);

void ingresarAlumno_res(tAlumno* alu);
void ingresar_alumno(tAlumno* alu);
void ingresarDniAlumno_res(tAlumno* alu);
void ingresar_dni_alumno(tAlumno* alu);
void ingresarNuevaMateria_res(tAlumno* alu);
void ingresar_nueva_materia(tAlumno* alu);
void imprimirAlumno_res(const tAlumno* alu);
void imprimir_alumno(const tAlumno* alu);
void mostrarDni_res(const void* vr);
void mostrar_dni(const tRegInd* r);
void imprimirArchivo_res(FILE * arch);
void imprimir_archivo(FILE * arch);

void imprimirArchivoOrdenado_res(FILE * arch, tArbolBinBusq* pa);
void imprimir_archivo_ordenado(FILE * arch, tArbolBinBusq* pa);


#endif // UTILITARIAS_H_INCLUDED
