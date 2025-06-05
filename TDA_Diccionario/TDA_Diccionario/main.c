#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Diccionario.h"

#define MAX_RUTA_ARCHIVO 512
#define MAX_LARGO_PALABRA 100

int main()
{
    char rutaArchivo[MAX_RUTA_ARCHIVO];
    FILE *archivoEntrada = NULL;

    printf("=========================================\n");
    printf("   Procesador de Textos - Diccionario\n");
    printf("=========================================\n\n");
    printf("Por favor, ingrese la ruta del archivo de texto a procesar: ");

    if(!fgets(rutaArchivo, sizeof(rutaArchivo), stdin))
    {
        puts("Error: No se pudo leer la entrada para la ruta del archivo.\n");
        return EXIT_FAILURE;
    }

    char *aux = strchr(rutaArchivo,'\n');
    if(aux != NULL)
        *aux = '\0';

    size_t len = strlen(rutaArchivo);
    if (len > 0)
    {
        if (len < 4 || strcmp(rutaArchivo + len - 4, ".txt") != 0)
        {
            if (len + strlen(".txt") < MAX_RUTA_ARCHIVO)
                strcat(rutaArchivo, ".txt");
        } else puts("Error: La ruta del archivo es demasiado larga para añadir '.txt'");
    }else puts("Error: No se ingresó una ruta de archivo.\n");

    archivoEntrada = fopen(rutaArchivo, "r");
    if (!archivoEntrada)
    {
        puts("Error al intentar abrir el archivo especificado");
        printf("Asegúrese de que el archivo '%s' exista y tenga permisos de lectura.\n", rutaArchivo);
        return EXIT_FAILURE;
    }

    printf("\nArchivo '%s' abierto exitosamente.\n\n", rutaArchivo);

    // --- INICIO DE ETAPA 2 ---

    long totalPalabras = 0;
    long totalEspacios = 0;
    long totalSignosPuntuacion = 0;
    tDiccionario miDiccionario;

    if (crear_dic(&miDiccionario, 100, hash_string) != DIC_OK)
    {
        puts("Error: No se pudo crear el diccionario.\n");
        fclose(archivoEntrada);
        return EXIT_FAILURE;
    }
    printf("TDA Diccionario inicializado.\n");
    rewind(archivoEntrada);

    printf("Iniciando procesamiento del archivo...\n");

    // ACA HAY QUE SEPARAR EL TXT EN PALABRAS Y METERLAS TODAS AL DICCIONARIO

    printf("Procesamiento del archivo completado.\n\n");

    fclose(archivoEntrada);

    // --- FIN DE ETAPA 2 ---

//    //ESTO DE ACA LEE EL ARCHIVO, LO IMPRIME Y CUENTA LA CANTIDAD DE LINEAS
//    //ESTA DE MAS Y ERA PARA PROBAR, NO LO PIDE EL ENUNCIADO
//    int caracter;
//    printf("Iniciando lectura preliminar del archivo...\n");
//    printf("-------------------------------------------\n");
//    // --- Lectura Carácter por Carácter (Verificación inicial de lectura) ---
//    // Esta sección será reemplazada/expandida en la Etapa 2 para el procesamiento real.
//    int lineCount = 0;
//    while ((caracter = fgetc(archivoEntrada)) != EOF)
//    {
//        // Por ahora, solo imprimimos para mostrar que se lee.
//        // En la Etapa 2, aquí irá la lógica de tokenización.
//        putchar(caracter);
//        if (caracter == '\n')
//            lineCount++;
//    }
//    printf("\n-------------------------------------------\n");
//    printf("Lectura preliminar del archivo completada. %d líneas leídas.\n\n", lineCount > 0 ? lineCount + 1 : (ftell(archivoEntrada) > 0 ? 1 : 0) );
//
//    fclose(archivoEntrada);


    // --- Obtención del Top 5 (Etapa 3) ---
    // Aquí se recuperaría la información del diccionario y se ordenaría.

    // --- Informe de Datos Requeridos (Etapa 4) ---
    // Esta sección se llenará con los resultados reales.
    printf("\n=========================================\n");
    printf("         Resultados del Análisis\n");
    printf("=========================================\n");
    printf("Archivo Procesado: %s\n\n", rutaArchivo);

    printf("Estadísticas Generales (placeholders):\n");
    printf("  - Total de Palabras: [pendiente]\n");
    printf("  - Total de Espacios: [pendiente]\n");
    printf("  - Total de Signos de Puntuación: [pendiente]\n\n");

    printf("Podio - 5 Palabras Más Utilizadas (placeholders):\n");
    printf("  1. [palabra1] ([N] veces)\n");
    printf("  2. [palabra2] ([M] veces)\n");
    printf("  3. [palabra3] ([O] veces)\n");
    printf("  4. [palabra4] ([P] veces)\n");
    printf("  5. [palabra5] ([Q] veces)\n\n");

    printf("=========================================\n");
    printf("   Análisis de Texto Finalizado\n");
    printf("=========================================\n");

    return EXIT_SUCCESS;
}








// ESTE ES EL MAIN VIEJO PARA PROBAR EL DICCIONARIO
//int main()
//{
//    tDiccionario dic;
//
//    // Usar los códigos de retorno definidos
//    if (crear_dic(&dic, 10, hash_simple) != DIC_OK) // Asumiendo DIC_OK = 1
//    {
//        printf("No se pudo crear el diccionario\n");
//        return 1; // O EXIT_FAILURE
//    }
//
//    const char* claves[] = {"perro", "gato", "pez", "raton", "perro"}; // Añadí "perro" duplicado para probar actualización
//    const char* valores[] =
//    {
//        "animal que ladra",
//        "animal que maulla",
//        "animal que nada",
//        "animal que come queso",
//        "otro perro que ladra mucho" // Nuevo valor para "perro"
//    };
//
//    for (int i = 0; i < 5; i++) // Actualizado a 5 para la clave duplicada
//    {
//        printf("Intentando insertar: %s -> %s\n", claves[i], valores[i]);
//        int ok = poner_dic(&dic, claves[i], strlen(claves[i]) + 1, // +1 para el '\0'
//                           valores[i], strlen(valores[i]) + 1); // +1 para el '\0'
//
//        if (ok == DIC_OK) // Chequear contra DIC_OK
//            printf("Insertado/Actualizado OK: %s -> %s\n", claves[i], valores[i]);
//        else if (ok == DIC_ERROR_MEMORIA)
//            printf("Error de memoria al insertar la clave: %s\n", claves[i]);
//        else
//            printf("Error desconocido (%d) al insertar la clave: %s\n", ok, claves[i]);
//    }
//
//    // --- Prueba de obtener_dic ---
//    printf("\n--- Probando obtener_dic ---\n");
//    const char* clave_a_buscar = "gato";
//    char buffer_valor[100]; // Buffer para almacenar el valor recuperado
//
//    int res_obtener = obtener_dic(&dic, clave_a_buscar, strlen(clave_a_buscar) + 1,
//                                  buffer_valor, sizeof(buffer_valor));
//
//    if (res_obtener == DIC_OK) {
//        printf("Valor para '%s': %s\n", clave_a_buscar, buffer_valor);
//    } else if (res_obtener == DIC_CLAVE_NO_ENCONTRADA) {
//        printf("Clave '%s' no encontrada.\n", clave_a_buscar);
//    } else {
//        printf("Error al obtener la clave '%s'.\n", clave_a_buscar);
//    }
//
//    // Probar obtener una clave que no existe
//    clave_a_buscar = "loro";
//    res_obtener = obtener_dic(&dic, clave_a_buscar, strlen(clave_a_buscar) + 1,
//                              buffer_valor, sizeof(buffer_valor));
//    if (res_obtener == DIC_OK) {
//        printf("Valor para '%s': %s\n", clave_a_buscar, buffer_valor);
//    } else if (res_obtener == DIC_CLAVE_NO_ENCONTRADA) {
//        printf("Clave '%s' no encontrada.\n", clave_a_buscar);
//    } else {
//        printf("Error al obtener la clave '%s'.\n", clave_a_buscar);
//    }
//
//
//    // --- PRUEBA DE SACAR_DIC (cuando la implementes) ---
//     printf("\n--- Probando sacar_dic ---\n");
//     const char* clave_a_sacar = "pez";
//     int res_sacar = sacar_dic(&dic, clave_a_sacar, strlen(clave_a_sacar) + 1);
//     if (res_sacar == DIC_OK) {
//         printf("Clave '%s' eliminada.\n", clave_a_sacar);
//         // Intentar obtenerla de nuevo (debería fallar)
//         res_obtener = obtener_dic(&dic, clave_a_sacar, strlen(clave_a_sacar) + 1, buffer_valor, sizeof(buffer_valor));
//         if (res_obtener == DIC_CLAVE_NO_ENCONTRADA) printf("Verificado: Clave '%s' ya no existe.\n", clave_a_sacar);
//     } else {
//         printf("Error al sacar la clave '%s'.\n", clave_a_sacar);
//     }
//
//
////     --- PRUEBA DE RECORRER_DIC (cuando la implementes) ---
//     void mi_accion_imprimir(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto) {
//         // Asumimos que clave y valor son strings para este ejemplo de acción
//         printf("Recorrer: Clave: %s (%lu bytes) -> Valor: %s (%lu bytes)\n",
//                (const char*)clave, (unsigned long)tamClave, (const char*)valor, (unsigned long)tamValor);
//         if (contexto) {
//              int* contador = (int*)contexto;
//              (*contador)++;
//         }
//     }
//     printf("\n--- Probando recorrer_dic ---\n");
//     recorrer_dic(&dic, mi_accion_imprimir, NULL);
//
//
//    // --- Liberar memoria al final ---
//    vaciar_dic(&dic);
//    printf("\nDiccionario vaciado.\n");
//
//    return 0;
//}
