#include "Diccionario.h"

int main()
{
    tDiccionario dic;

    if (!crear_dic(&dic, 10))
    {
        printf("No se pudo crear el diccionario\n");
        return 1;
    }

    const char* claves[] = {"perro", "gato", "pez", "ratón"};
    const char* valores[] =
    {
        "animal que ladra",
        "animal que maulla",
        "animal que nada",
        "animal que come queso"
    };

    for (int i = 0; i < 4; i++)
    {
        int ok = poner_dic(&dic, claves[i], strlen(claves[i]) + 1,
                           valores[i], strlen(valores[i]) + 1,
                           hash_simple);

        if (ok)
            printf("Insertado: %s -> %s\n", claves[i], valores[i]);
        else
            printf("Error al insertar la clave: %s\n", claves[i]);
    }

    return 0;
}
