#include "Funciones.h"

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

void ProcesarLineaParaDiccionarioYContadores(tDiccionario *dic, char *lineaAnalizar, long *contadorPalabrasTotales, long *contadorEspaciosTotales, long *contadorSignosTotales)
{
    const char *delimitadoresPalabras = " \t\n\r\f\v.,;:!?\"'()[]{}<>-_+=*&^%$#@~/|\\0123456789"; // Delimitadores para la extraccion de palabras con strtok
    char *token,*punteroCaracter,palabraProcesada[MAX_LARGO_PALABRA];
    int ValorActual;

    char *act = strchr(lineaAnalizar,'\n');
    if(act)
        *act = '\0';

    // --- PASADA 1: Contar espacios y signos de puntuacion ---
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
            palabraProcesada[indiceDestino++] = tolower(token[i]);
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
        printf("Palabra: \"%-20s\" -> Valor: [Dato no valido o inesperado]\n", palabra);
    }
}

void *ObtenerPuntajeDeCorte(tLista* pl, int (*cmp)(const void*,const void*))
{
    int empates,pos = 1;
    void *puntajeDeCorte = NULL;
    tNodo *aux,*act = *pl;

    while (act && pos <= 5)
    {
        puntajeDeCorte = act->info;
        empates = 0;
        aux = act;
        while (aux && cmp(act->info, aux->info) == 0)
        {
            empates++;
            aux = aux->sig;
        }
        pos += empates;
        act = aux;
    }
    return puntajeDeCorte;
}

int ActualizarPodio(tLista *pl, const void *pd, size_t tam, int (*cmp)(const void*,const void*))
{
    void *puntajeCorteActual = ObtenerPuntajeDeCorte(pl, cmp);
    if (puntajeCorteActual && cmp(pd, puntajeCorteActual) > 0)
        return 0; //Es menor que el ultimo del podio

    tLista *aux = pl;
    while (*aux && cmp(pd, (*aux)->info) > 0)
        aux = &(*aux)->sig;
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if (!nue)
        return 0;
    nue->info = malloc(tam);
    if (!nue->info)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->sig = *aux;
    *aux = nue;

    void *nuevoPuntajeCorte = ObtenerPuntajeDeCorte(pl, cmp);
    if (!nuevoPuntajeCorte)
        return 1;

    tNodo* ultimoDelPodio = NULL;
    tNodo* act = *pl;

    while (act && cmp(act->info, nuevoPuntajeCorte) <= 0)
    {
        ultimoDelPodio = act;
        act = act->sig;
    }

    if (ultimoDelPodio)
    {
        if (ultimoDelPodio->sig)
            liberarNodos(&ultimoDelPodio->sig);
    }
    else liberarNodos(pl);

    return 1;
}

void liberarNodos(tLista *pl)
{
    tNodo *aux;
    while(*pl)
    {
        aux = *pl;
        *pl = aux->sig;
        free(aux->info);
        free(aux);
    }
}

void mostrarPodioDic(tLista *pl)
{
    tNodo *actual = *pl; // Puntero para recorrer la lista ordenada
    int puesto_real = 1;

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

void BajarPalabrasPodio(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto)
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
    ActualizarPodio(ctx, &info, sizeof(tElementoDic), cmptElem);
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
    puts("\n");
}
