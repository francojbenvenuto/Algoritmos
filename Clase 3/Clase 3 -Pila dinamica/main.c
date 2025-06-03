#include"Funciones.h"

int main()
{
    tPila PilaDinamica;

    crear_pila(&PilaDinamica);

    Producto prod,   prodTope;

    prod.id = 1;
    strcpy(prod.nombre,"Yerba Mate");
    prod.precio = 321312;



    if (poner_en_pila(&PilaDinamica, &prod, sizeof(Producto)))
    {
        printf("Producto apilado: %s - $%.2f\n", prod.nombre, prod.precio);
    }
    else
    {
        printf("Error al apilar producto\n");
    }

    // Ver el tope
    if (ver_tope_pila(&PilaDinamica, &prodTope, sizeof(Producto)))
    {
        printf("Tope de pila: %s - $%.2f\n", prodTope.nombre, prodTope.precio);
    }
    else
    {
        printf("La pila está vacía\n");
    }

    // Sacar de la pila
    if (sacar_de_pila(&PilaDinamica, &prodTope, sizeof(Producto)))
    {
        printf("Producto desapilado: %s - $%.2f\n", prodTope.nombre, prodTope.precio);
    }
    else
    {
        printf("No se pudo desapilar\n");
    }

    // Verificar si está vacía
    if (pila_vacia(&PilaDinamica))
    {
        printf("La pila está vacía ahora\n");
    }
    else
    {
        printf("La pila aún tiene elementos\n");
    }

    return 0;
}
