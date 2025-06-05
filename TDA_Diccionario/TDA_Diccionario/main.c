#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Diccionario.h"

#define MAX_RUTA_ARCHIVO 512
#define MAX_LARGO_PALABRA 100

void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales);
void accion_imprimir_dic(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);

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

    pf = fopen(rutaArchivo, "r");
    if (!pf)
    {
        puts("Error al intentar abrir el archivo especificado");
        printf("Asegúrese de que el archivo '%s' exista y tenga permisos de lectura.\n", rutaArchivo);
        return EXIT_FAILURE;
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
        return EXIT_FAILURE;
    }

    char linea[512];
    while(fgets(linea,sizeof(linea),pf))
    {
        ProcesarLineaParaDiccionarioYContadores(&miDiccionario, linea, &totalPalabras , &totalEspacios, &totalSignosPuntuacion);
    }

    //recorrer_dic(&miDiccionario, accion_imprimir_dic, NULL);

    fclose(pf);


    // --- Obtención del Top 5 ---
    // Aca se recuperaría la información del diccionario y se ordenaría.

    vaciar_dic(&miDiccionario);

    printf("\n=========================================\n");
    printf("         Resultados del Analisis\n");
    printf("=========================================\n");
    printf("Archivo Procesado: %s\n\n", rutaArchivo);

    printf("Estadisticas Generales:\n");
    printf("  - Total de Palabras: %ld\n",totalPalabras);
    printf("  - Total de Espacios: %ld\n",totalEspacios);
    printf("  - Total de Signos de Puntuacion: %ld\n\n",totalSignosPuntuacion);

    printf("Podio - 5 Palabras Mas Utilizadas:\n");
    printf("  1. [palabra1] ([N] veces)\n");
    printf("  2. [palabra2] ([M] veces)\n");
    printf("  3. [palabra3] ([O] veces)\n");
    printf("  4. [palabra4] ([P] veces)\n");
    printf("  5. [palabra5] ([Q] veces)\n\n");

    printf("=========================================\n");
    printf("   Analisis de Texto Finalizado\n");
    printf("=========================================\n");

    return EXIT_SUCCESS;
}

void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales)
{
    const char *delimitadoresPalabras = " \t\n\r\f\v.,;:!?\"'()[]{}<>-_+=*&^%$#@~/|\\0123456789"; // Delimitadores para la extracción de palabras con strtok
    char *token,*punteroCaracter,palabraProcesada[MAX_LARGO_PALABRA];
    int ValorActual;

    char *act = strchr(lineaAnalizar,'\n');
    if(act)
        *act = '\0';

    // --- PASADA 1: Contar espacios y signos de puntuación ---
    for (punteroCaracter = lineaAnalizar; *punteroCaracter != '\0'; punteroCaracter++)
    {
        if (isspace(*punteroCaracter))
        {
            (*contadorEspaciosTotales)++;
        }
        else if (ispunct(*punteroCaracter))
        {
            (*contadorSignosTotales)++;
        }
    }
    // --- PASADA 2: Extraer palabras, normalizarlas y actualizar el diccionario ---
    token = strtok(lineaAnalizar, delimitadoresPalabras);
    while (token != NULL)
    {
        int indiceDestino = 0;
        for (int i = 0; token[i] != '\0' && indiceDestino < MAX_LARGO_PALABRA - 1; i++)
        {
            if (isalpha(token[i]))
            {
                palabraProcesada[indiceDestino++] = tolower(token[i]);
            }
        }
        palabraProcesada[indiceDestino] = '\0';

        if (strlen(palabraProcesada) > 0)
        {
            (*contadorPalabrasTotales)++;

            ValorActual = 0;

            if (obtener_dic(dic, palabraProcesada, strlen(palabraProcesada) + 1, &ValorActual, sizeof(int)) == DIC_OK)
            {
                ValorActual++; // La palabra existe, incrementar valor
            }
            else
            {
                ValorActual = 1; // Palabra nueva, valor inicial es 1
            }
            if (poner_dic(dic, palabraProcesada, strlen(palabraProcesada) + 1, &ValorActual, sizeof(int)) != DIC_OK)
            {
                printf("Advertencia: No se pudo insertar/actualizar la palabra '%s' en el diccionario.\n", palabraProcesada);
            }
        }
        token = strtok(NULL, delimitadoresPalabras);
    }
}

void accion_imprimir_dic(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto)
{
    const char* palabra = (const char*)clave;
    int Valor;

    if (valor != NULL && tamValor == sizeof(int))
    {
        Valor = *(int*)valor;
        printf("Palabra: \"%-20s\" -> Valor: %5d \n",palabra, Valor);
    } else {
        printf("Palabra: \"%-20s\" -> Valor: [Dato no válido o inesperado]\n", palabra);
    }
}
