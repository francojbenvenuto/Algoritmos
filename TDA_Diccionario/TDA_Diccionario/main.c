#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Diccionario.h"

#define MAX_RUTA_ARCHIVO 512
#define MAX_LARGO_PALABRA 100

/*
INTEGRANTES DEL GRUPO:
-CHAT GPT
-GEMINI PRO
-AGUIRRE
-CACERES
*/
void ProcesarRuta(char *rutaArchivo);
void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales);
void accion_imprimir_dic(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);
void BajarPalabras(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto);
int cmptElem(const void *a, const void *b);
void mostrarPodioDic(tLista *pl);
void mostrar_lista_dic(tLista *pl);

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

    ProcesarRuta(rutaArchivo);


    pf = fopen(rutaArchivo, "r");
    if (!pf)
    {
        puts("Error al intentar abrir el archivo especificado");
        printf("Asegurese de que el archivo '%s' exista y tenga permisos de lectura.\n", rutaArchivo);
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

    return EXIT_SUCCESS;
}

void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales)
{
    const char *delimitadoresPalabras = " \t\n\r\f\v.,;:!?\"'()[]{}<>-_+=*&^%$#@~/|\\0123456789"; // Delimitadores para la extracci�n de palabras con strtok
    char *token,*punteroCaracter,palabraProcesada[MAX_LARGO_PALABRA];
    int ValorActual;

    char *act = strchr(lineaAnalizar,'\n');
    if(act)
        *act = '\0';

    // --- PASADA 1: Contar espacios y signos de puntuaci�n ---
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
    }
    else
    {
        printf("Palabra: \"%-20s\" -> Valor: [Dato no v�lido o inesperado]\n", palabra);
    }
}

void mostrarPodioDic(tLista *pl)
{
    tNodo *actual = *pl; // Puntero para recorrer la lista ordenada
    int puesto_real = 1; // El "ranking" real, que salta con los empates

    puts("--- Podio Palabras mas utilizadas ---");

    for (int puesto_a_imprimir = 1; puesto_a_imprimir <= 5; puesto_a_imprimir++)
    {
        if (puesto_a_imprimir == puesto_real && actual)
        {
            tElementoDic *infoActual = (tElementoDic*)actual->info;
            int puntaje_del_puesto = *(int*)infoActual->valor;
            int palabras_en_este_puesto = 0; // Para contar los empates

            printf("\n%d Puesto (Cantidad de apariciones: %d):\n", puesto_a_imprimir, puntaje_del_puesto);

            tNodo* scanner = actual;
            while (scanner && (*(int*)((tElementoDic*)scanner->info)->valor) == puntaje_del_puesto)
            {
                printf(" - %s\n", (char*)((tElementoDic*)scanner->info)->clave);
                palabras_en_este_puesto++;
                scanner = scanner->sig;
            }
            actual = scanner;
            puesto_real += palabras_en_este_puesto;

        }
        else
        {
            printf("\n%d Puesto: -- Vacio --\n", puesto_a_imprimir);
        }
    }
}

void BajarPalabras(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto)
{
    tLista *ctx = (tLista *)contexto;
    tElementoDic info;

    info.clave = malloc(tamClave);
    if (!info.clave)
        return;
    memcpy(info.clave, clave, tamClave);
    info.tamClave = tamClave;
    info.valor = malloc(tamValor);
    if (!info.valor)
    {
        free(info.clave);
        return;
    }
    memcpy(info.valor, valor, tamValor);
    info.tamValor = tamValor;
    poner_orden_lista_con_duplicados(ctx, &info, sizeof(tElementoDic), cmptElem);
}

int cmptElem(const void *a, const void *b)
{
    const tElementoDic *elemA = (const tElementoDic *)a;
    const tElementoDic *elemB = (const tElementoDic *)b;

    int valorA = *(int *)(elemA->valor);
    int valorB = *(int *)(elemB->valor);

    return valorB - valorA;
}

void mostrar_lista_dic(tLista *pl)
{
    while(*pl)
    {
        printf("-%d-", *((int*)((tElementoDic*)(*pl)->info)->valor));
        pl=&(*pl)->sig;
    }
}

void ProcesarRuta(char *rutaArchivo)
{
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
        }
        else puts("Error: La ruta del archivo es demasiado larga para anadir '.txt'");
    }
    else puts("Error: No se ingreso una ruta de archivo.\n");
}
