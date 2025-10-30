#include "funciones.h"

int main()
{
    t_pila pila;
    CrearPila(&pila);

    char oracion[] = "Hola, esto es una oraci�n en la pila.";
    char dato[100]; // para leer desde la pila

    PonerEnPila(&pila,oracion,strlen(oracion)+1);

    VerTope(&pila,dato,100000);
    printf("%s",dato);


    printf("HOLA");
    return 0;

}
