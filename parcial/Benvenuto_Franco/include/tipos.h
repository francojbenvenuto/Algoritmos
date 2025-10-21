#ifndef TIPOS_H_INCLUDED
#define TIPOS_H_INCLUDED


#define TODO_OK 1
#define SIN_MEM 2
#define ERROR_ARCHIVO 3
#define DUPLICADO 4
#define NO_EXISTE 5
#define SIN_INICIALIZAR 6

#define VERDADERO 1
#define FALSO 0

typedef struct{
    int dni;
    char apyn[40];
    int cant_materias;
    float promedio;
    char estado; ///'A' Activo - 'B' Baja
}tAlumno;

typedef struct
{
	int dni;
	int nro_reg;
}
tRegInd;


#endif // TIPOS_H_INCLUDED
