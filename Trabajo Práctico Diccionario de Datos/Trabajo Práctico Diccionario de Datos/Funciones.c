#include "Funciones.h"

void ProcesarRuta(char *rutaArchivo)
{
    char *aux = strchr(rutaArchivo,'\n');    //  Buscar el caracter '\n' en la ruta del archivo
    if(aux != NULL)
        *aux = '\0';

    size_t len = strlen(rutaArchivo);       //  Longitud de la ruta del archivo
    if (len > 0)
    {
        if (len < 4 || strcmp(rutaArchivo + len - 4, ".txt") != 0) //  Comprobar si la ruta del archivo termina con '.txt' (puntero a inicio, va al final y vuelve 4)
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

    char *act = strchr(lineaAnalizar,'\n');    //  Buscar el caracter '\n' en la ruta del archivo
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
    /* strtok modifica la cadena original, por lo que no se puede usar lineaAnalizar despues de esto
       token se usa por convencion, es un puntero a la primera palabra encontrada en la cadena
       Se usa strtok para dividir la cadena en palabras, usando los delimitadores definidos
       Se usa un bucle para recorrer todas las palabras encontradas en la cadena                  */
    while (token != NULL)
    {
        int posicionPalabra = 0;
        for (int i = 0; token[i] != '\0' && posicionPalabra < MAX_LARGO_PALABRA - 1; i++)
        {
            palabraProcesada[posicionPalabra] = tolower(token[i]);
            posicionPalabra++;
        }
        palabraProcesada[posicionPalabra] = '\0';
        /* normalizamos la palabra en minúsculas con tolower y la guardamos en palabraProcesada
           Se asegura que no se exceda el tamaño máximo de palabra (MAX_LARGO_PALABRA - 1) para evitar desbordamientos
           Se termina la cadena con '\0' para que sea una cadena válida en C
           Si la palabra es vacía, no se procesa, ya que no es una palabra válida
        */
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


//=========================================================================================================================================
//  Funciones para el podio
//=========================================================================================================================================



void *ObtenerMenorPuntaje(tLista* LPodio, int (*cmp)(const void*,const void*))
{
    int empates,pos = 1;
    void *MenorPuntaje = NULL;  // ultimo puntaje del podio
    tNodo *aux,*act = *LPodio;

    while (act && pos <= 5)
    {
        MenorPuntaje = act->info;
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
    /*recore la lista podio, y busca el ultimo elemento con menor valor de puntaje contando los empates
    y devuelve el ultimo elemento */
    return MenorPuntaje;
}

int ActualizarPodio(tLista *LPodio, const void *ElemNuevo, size_t tamElemen, int (*cmp)(const void*,const void*))
{
/* Da bug
            // estamos analizando el nodo actual del recorrido.
            void *puntajeCorteActual = ObtenerMenorPuntaje(LPodio, cmp);  // ultimo elemnto del podio

        //=========================================================================================================================================
        // caso 1: nodo actual es menor que el ultimo del podio
        //=========================================================================================================================================
            if (puntajeCorteActual && cmp(ElemNuevo, puntajeCorteActual) > 0)
                return OK;
*/
//=========================================================================================================================================
// caso 2: nodo actual es mayor o igual que el ultimo del podio
//=========================================================================================================================================

    tLista *aux = LPodio;
    //recorremos el podio y sabemos en aux la posicion del nodo a ingresar(porque se insertan en orden)
    while (*aux && cmp(ElemNuevo, (*aux)->info) > 0)
        aux = &(*aux)->sig;

    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if (!nue)
        return ERROR;

    nue->info = malloc(tamElemen);
    if (!nue->info)
    {
        free(nue);
        return ERROR;
    }
    memcpy(nue->info, ElemNuevo, tamElemen);
    nue->tamInfo = tamElemen;
    nue->sig = *aux;
    *aux = nue;
    // insertamos el nuevo nodo en la lista (en siguiente guaramos la direccion del nodo siguiente y cambiamos aux por la direccion del nodo actual)


//==========================================================================================================================================
//  Si el podio con el nuevo nodo supera los 5 elementos, se eliminan los nodos fuera del podio
//==========================================================================================================================================

    void *nuevoPuntajeCorte = ObtenerMenorPuntaje(LPodio, cmp); //obtengo el nuevo ultimo del podio
    if (!nuevoPuntajeCorte)
        return ERROR;

    tNodo* ultimoDelPodio = NULL;
    tNodo* act = *LPodio;

    while (act && cmp(act->info, nuevoPuntajeCorte) >= 0)
    {
        ultimoDelPodio = act;
        act = act->sig;
    }

    if (ultimoDelPodio)
    {
        if (ultimoDelPodio->sig)
            liberarNodos(&ultimoDelPodio->sig);
    }
    return OK;
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

void mostrarPodioDic(tLista *LPodio)
{
    tNodo *actual = *LPodio; // Puntero para recorrer la lista ordenada
    int puestoReal = 1;

    // == CÓDIGO PARA ACTIVAR COLORES ANSI EN LA CONSOLA DE WINDOWS ==
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode(hConsole, &consoleMode);
    SetConsoleMode(hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    // ==================================================================

    puts("\033[1;35m+----------------------------+"); //  ANSI  magenta
    puts(          "|   Podio Palabras TOP 5     |");
    puts(          "+----------------------------+\033[0m");

    for (int puestoAct = 1; puestoAct <= 5; puestoAct++)
    {
        if (puestoAct == puestoReal && actual)
        {
            tElementoDic *infoActual = (tElementoDic*)actual->info;
            int puntaje_del_puesto = *(int*)infoActual->valor;
            int palabras_en_este_puesto = 0; // Para contar los empates

            switch (puestoAct)
            {
            case 1:
                printf("\n\033[1;32m%d Puesto (Cantidad de apariciones: %d):\033[0m\n", puestoAct, puntaje_del_puesto); //  ANSI verde brillante
                break;
            case 2:
                printf("\n\033[1;90m%d Puesto (Cantidad de apariciones: %d):\033[0m\n", puestoAct, puntaje_del_puesto); //  ANSI gris
                break;
            case 3:
                printf("\n\033[1;33m%d Puesto (Cantidad de apariciones: %d):\033[0m\n", puestoAct, puntaje_del_puesto); //  ANSI amarillo
                break;
            case 4:
                printf("\n\033[1;34m%d Puesto (Cantidad de apariciones: %d):\033[0m\n", puestoAct, puntaje_del_puesto); //  ANSI azul
                break;
            case 5:
                printf("\n\033[1;36m%d Puesto (Cantidad de apariciones: %d):\033[0m\n", puestoAct, puntaje_del_puesto); //  ANSI cian
                break;
            default:
                puts("\n\033[1;31mPuesto no valido\033[0m"); //  ANSI rojo
                //return ERROR;
                break;
            }
            tNodo* palabrasEmpate = actual;
            while (palabrasEmpate && (*(int*)((tElementoDic*)palabrasEmpate->info)->valor) == puntaje_del_puesto)
            {
                printf(" - %s\n", (char*)((tElementoDic*)palabrasEmpate->info)->clave);
                palabras_en_este_puesto++;
                palabrasEmpate = palabrasEmpate->sig;
            }
            actual = palabrasEmpate;
            puestoReal += palabras_en_este_puesto;

        }
        else
        {
            printf("\n\033[1;31m%d Puesto: -- Vacio --\033[0m\n", puestoAct); //  ANSI rojo
        }
    }
}

void BajarPalabrasPodio(const void* clave, size_t tamClave, void* valor, size_t tamValor, void* contexto)
{
    // en esta funcion solo le damos formato a los valores en modo de tElemntoDic y la lista y los insertamos en el podio(si es que es necesario)
    tLista *aux = (tLista *)contexto;
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
    ActualizarPodio(aux, &info, sizeof(tElementoDic), cmptElem);
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
