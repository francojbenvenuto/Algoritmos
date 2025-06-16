#include "Funciones.h"

int main()
{
    char rutaArchivo[MAX_RUTA_ARCHIVO];
    FILE *pf;

    printf("=========================================\n");
    printf("   Procesador de Textos - Diccionario\n");
    printf("=========================================\n\n");
    printf("Por favor, ingrese la ruta del archivo de texto a procesar: ");

    if(!fgets(rutaArchivo, sizeof(rutaArchivo), stdin))
    {
        puts("Error: No se pudo leer la entrada para la ruta del archivo.\n");
        return ERROR;
    }

    ProcesarRuta(rutaArchivo); // Procesar la ruta para asegurarnos de que tenga el formato correcto

    pf = fopen(rutaArchivo, "r"); // Intentar abrir el archivo
    if (!pf)
    {
        puts("Error al intentar abrir el archivo especificado\n");
        printf("Asegurese de que el archivo '%s' exista y tenga permisos de lectura.\n", rutaArchivo);
        return ERROR;
    }

    printf("\nArchivo '%s' abierto exitosamente.\n\n", rutaArchivo);


    // ============================================================================================================================================
    //  empieza el procesamiento del archivo
    // ============================================================================================================================================

    long totalPalabras = 0;
    long totalEspacios = 0;
    long totalSignosPuntuacion = 0;
    tDiccionario miDiccionario;

    if (crear_dic(&miDiccionario, 100, hash_simple) != DIC_OK) // Crear diccionario con el tdiccionario, 100 buckets y hash_simple como funcion de hash
    {
        puts("Error: No se pudo crear el diccionario.\n");
        fclose(pf);
        return ERROR;
    }

    char linea[512];
    while(fgets(linea,sizeof(linea),pf))       // Leer cada linea del archivo hasta el final y procesarla con el diccionario
    {
        ProcesarLineaParaDiccionarioYContadores(&miDiccionario, linea, &totalPalabras, &totalEspacios, &totalSignosPuntuacion);
    }

//    recorrer_dic(&miDiccionario, accion_imprimir_dic, NULL);

    fclose(pf);
//=========================================================================================================================================
//  Diccionario completo, ahora se procesa la lista de palabras
//=========================================================================================================================================

    tLista podio;   
    crear_lista(&podio);

    recorrer_dic(&miDiccionario, BajarPalabrasPodio, &podio); // en cada nodo realiza baja de palabras

//    mostrar_lista_dic(&podio);

    vaciar_dic(&miDiccionario);

    printf("\n=========================================\n");
    printf("         Resultados del Analisis\n");
    printf("=========================================\n");
    printf("Archivo Procesado: %s\n\n", rutaArchivo);

    printf("Estadisticas Generales:\n");
    printf("  - Total de Palabras: %ld\n",totalPalabras);
    printf("  - Total de Espacios: %ld\n",totalEspacios);
    printf("  - Total de Signos de Puntuacion: %ld\n\n",totalSignosPuntuacion);

    mostrarPodioDic(&podio);

    printf("=========================================\n");
    printf("   Analisis de Texto Finalizado\n");
    printf("=========================================\n");

    vaciarLista(&podio);

    return OK;
}
