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

    ProcesarRuta(rutaArchivo);

    pf = fopen(rutaArchivo, "r");
    if (!pf)
    {
        puts("Error al intentar abrir el archivo especificado");
        printf("Asegurese de que el archivo '%s' exista y tenga permisos de lectura.\n", rutaArchivo);
        return ERROR;
    }

    printf("\nArchivo '%s' abierto exitosamente.\n\n", rutaArchivo);

    long totalPalabras = 0;
    long totalEspacios = 0;
    long totalSignosPuntuacion = 0;
    tDiccionario miDiccionario;

    if (crear_dic(&miDiccionario, 100, hash_string) != DIC_OK)
    {
        puts("Error: No se pudo crear el diccionario.\n");
        fclose(pf);
        return ERROR;
    }

    char linea[512];
    while(fgets(linea,sizeof(linea),pf))
    {
        ProcesarLineaParaDiccionarioYContadores(&miDiccionario, linea, &totalPalabras, &totalEspacios, &totalSignosPuntuacion);
    }

    //recorrer_dic(&miDiccionario, accion_imprimir_dic, NULL);

    fclose(pf);

    tLista palabras;
    crear_lista(&palabras);

    recorrer_dic(&miDiccionario, BajarPalabras, &palabras);
    //mostrar_lista_dic(&palabras);

    vaciar_dic(&miDiccionario);

    printf("\n=========================================\n");
    printf("         Resultados del Analisis\n");
    printf("=========================================\n");
    printf("Archivo Procesado: %s\n\n", rutaArchivo);

    printf("Estadisticas Generales:\n");
    printf("  - Total de Palabras: %ld\n",totalPalabras);
    printf("  - Total de Espacios: %ld\n",totalEspacios);
    printf("  - Total de Signos de Puntuacion: %ld\n\n",totalSignosPuntuacion);

    mostrarPodioDic(&palabras);

    printf("=========================================\n");
    printf("   Analisis de Texto Finalizado\n");
    printf("=========================================\n");

    vaciarLista(&palabras);

    return OK;
}
