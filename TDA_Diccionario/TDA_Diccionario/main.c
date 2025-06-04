#include <stdio.h>    // Para printf
#include <string.h>   // Para strlen

#include "Diccionario.h" // Bien

int main()
{
    tDiccionario dic;

    // Usar los códigos de retorno definidos
    if (crear_dic(&dic, 10) != DIC_OK) // Asumiendo DIC_OK = 1
    {
        printf("No se pudo crear el diccionario\n");
        return 1; // O EXIT_FAILURE
    }

    const char* claves[] = {"perro", "gato", "pez", "raton", "perro"}; // Añadí "perro" duplicado para probar actualización
    const char* valores[] =
    {
        "animal que ladra",
        "animal que maulla",
        "animal que nada",
        "animal que come queso",
        "otro perro que ladra mucho" // Nuevo valor para "perro"
    };

    for (int i = 0; i < 5; i++) // Actualizado a 5 para la clave duplicada
    {
        printf("Intentando insertar: %s -> %s\n", claves[i], valores[i]);
        int ok = poner_dic(&dic, claves[i], strlen(claves[i]) + 1, // +1 para el '\0'
                           valores[i], strlen(valores[i]) + 1, // +1 para el '\0'
                           hash_simple);

        if (ok == DIC_OK) // Chequear contra DIC_OK
            printf("Insertado/Actualizado OK: %s -> %s\n", claves[i], valores[i]);
        else if (ok == DIC_ERROR_MEMORIA)
            printf("Error de memoria al insertar la clave: %s\n", claves[i]);
        else
            printf("Error desconocido (%d) al insertar la clave: %s\n", ok, claves[i]);
    }

    // --- Prueba de obtener_dic ---
    printf("\n--- Probando obtener_dic ---\n");
    const char* clave_a_buscar = "gato";
    char buffer_valor[100]; // Buffer para almacenar el valor recuperado

    int res_obtener = obtener_dic(&dic, clave_a_buscar, strlen(clave_a_buscar) + 1,
                                  buffer_valor, sizeof(buffer_valor), hash_simple);

    if (res_obtener == DIC_OK) {
        printf("Valor para '%s': %s\n", clave_a_buscar, buffer_valor);
    } else if (res_obtener == DIC_CLAVE_NO_ENCONTRADA) {
        printf("Clave '%s' no encontrada.\n", clave_a_buscar);
    } else {
        printf("Error al obtener la clave '%s'.\n", clave_a_buscar);
    }

    // Probar obtener una clave que no existe
    clave_a_buscar = "loro";
    res_obtener = obtener_dic(&dic, clave_a_buscar, strlen(clave_a_buscar) + 1,
                              buffer_valor, sizeof(buffer_valor), hash_simple);
    if (res_obtener == DIC_OK) {
        printf("Valor para '%s': %s\n", clave_a_buscar, buffer_valor);
    } else if (res_obtener == DIC_CLAVE_NO_ENCONTRADA) {
        printf("Clave '%s' no encontrada.\n", clave_a_buscar);
    } else {
        printf("Error al obtener la clave '%s'.\n", clave_a_buscar);
    }


    // --- PRUEBA DE SACAR_DIC (cuando la implementes) ---
     printf("\n--- Probando sacar_dic ---\n");
     const char* clave_a_sacar = "pez";
     int res_sacar = sacar_dic(&dic, clave_a_sacar, strlen(clave_a_sacar) + 1, hash_simple);
     if (res_sacar == DIC_OK) {
         printf("Clave '%s' eliminada.\n", clave_a_sacar);
         // Intentar obtenerla de nuevo (debería fallar)
         res_obtener = obtener_dic(&dic, clave_a_sacar, strlen(clave_a_sacar) + 1, buffer_valor, sizeof(buffer_valor), hash_simple);
         if (res_obtener == DIC_CLAVE_NO_ENCONTRADA) printf("Verificado: Clave '%s' ya no existe.\n", clave_a_sacar);
     } else {
         printf("Error al sacar la clave '%s'.\n", clave_a_sacar);
     }


//     --- PRUEBA DE RECORRER_DIC (cuando la implementes) ---
     void mi_accion_imprimir(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto) {
         // Asumimos que clave y valor son strings para este ejemplo de acción
         printf("Recorrer: Clave: %s (%lu bytes) -> Valor: %s (%lu bytes)\n",
                (const char*)clave, (unsigned long)tamClave, (const char*)valor, (unsigned long)tamValor);
         if (contexto) {
              int* contador = (int*)contexto;
              (*contador)++;
         }
     }
     printf("\n--- Probando recorrer_dic ---\n");
     recorrer_dic(&dic, mi_accion_imprimir, NULL);


    // --- Liberar memoria al final ---
    vaciar_dic(&dic);
    printf("\nDiccionario vaciado.\n");


    return 0;
}
