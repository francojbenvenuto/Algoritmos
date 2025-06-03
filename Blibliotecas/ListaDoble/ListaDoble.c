/* -----------------------------o--X--o-------------------------------
 *         listaDoble.c        LISTA DOBLEMENTE ENLAZADA
 * -----------------------------o--X--o------------------------------- */

#include "listaDoble.h"

void crearLista(tLista *pl)
{
    *pl = NULL;
}

int vaciarLista(tLista *pl)
{
    int cant = 0;
    tNodo *act = *pl;

    if (act)
    {
        while (act->ant)
            act = act->ant;
        while (act)
        {
            tNodo *aux = act->sig;
            free(act->info);
            free(act);
            act = aux;
            cant++;
        }
        *pl = NULL;
    }

    return cant;
}

int listaVacia(const tLista *pl)
{
    return *pl == NULL;
}

int listaLlena(const tLista *pl, size_t tam)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
    void  *aux = malloc(tam);

    free(nue);
    free(aux);
    return aux == NULL || nue == NULL;
}

int insertarAlFinal(tLista *pl, const void *pd, size_t tam)
{
    tNodo *act = *pl,
          *nue;

    if (act)
        while (act->sig)
            act = act->sig;

    if ((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
        (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->sig = NULL;
    nue->ant = act;

    if (act)
        act->sig = nue;
    *pl = nue;
    return 1;
}

int insertarAlComienzo(tLista *pl, const void *pd, size_t tam)
{
    tNodo *act = *pl,
          *nue;

    if (act)
        while (act->ant)
            act = act->ant;

    if ((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
        (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->sig = act;
    nue->ant = NULL;

    if (act)
        act->ant = nue;
    *pl = nue;
    return 1;
}

int mostrarDeIzqADer(const tLista *pl, void (*mostrar)(const void *))
{
    tNodo *act = *pl;
    int cant = 0;

    if (act)
    {
        mostrar(NULL);
        while (act->ant)
            act = act->ant;

        while (act)
        {
            mostrar(act->info);
            act = act->sig;
            cant++;
        }
    }
    return cant;
}

int mostrarDeDerAIzq(const tLista *pl, void (*mostrar)(const void *))
{
    tNodo *act = *pl;
    int cant = 0;

    if (act)
    {
        mostrar(NULL);
        while (act->sig)
            act = act->sig;

        while (act)
        {
            mostrar(act->info);
            act = act->ant;
            cant++;
        }
    }
    return cant;
}

int insertarEnOrden(tLista *pl, const void *pd, size_t tam,
                    int (*comparar)(const void *, const void *),
                    int (*acumular)(void **, size_t *, const void *, size_t))
{
    tNodo *act = *pl,
          *sig,
          *ant,
          *nue;

    if (act == NULL)
    {
        ant = NULL;
        sig = NULL;
    }
    else
    {
        int aux;
        while (act->sig && comparar(act->info, pd) < 0)
            act = act->sig;

        while (act->ant && comparar(act->info, pd) > 0)
            act = act->ant;

        aux = comparar(act->info, pd);

        if (aux == 0)
        {
            *pl = act;
            if (acumular)
                if (acumular(&act->info, &act->tamInfo, pd, tam) == 0)
                    return SIN_MEM;
            return CLA_DUP;
        }

        if (aux < 0)
        {
            ant = act;
            sig = act->sig;
        }
        else
        {
            ant = act->ant;
            sig = act;
        }
    }

    if ((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL ||
        (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;
    nue->sig = sig;
    nue->ant = ant;

    if (sig)
        sig->ant = nue;
    if (ant)
        ant->sig = nue;
    *pl = nue;
    return TODO_BIEN;
}

void ordenarLista(tLista *pl, int (*comparar)(const void *, const void *))
{
    tNodo *act = *pl,
          *sup = NULL,
          *inf = NULL;
    int marca = 1;

    if (act == NULL)
        return;

    while (act->ant)
        act = act->ant;

    while (marca)
    {
        marca = 0;
        while (act->sig != sup)
        {
            if (comparar(act->info, act->sig->info) > 0)
            {
                void *inf = act->info;
                size_t tam = act->tamInfo;

                marca = 1;
                act->info = act->sig->info;
                act->sig->info = inf;
                act->tamInfo = act->sig->tamInfo;
                act->sig->tamInfo = tam;
            }
            act = act->sig;
        }
        sup = act;

        while (act->ant != inf)
        {
            if (comparar(act->info, act->ant->info) < 0)
            {
                void *inf = act->info;
                size_t tam = act->tamInfo;

                marca = 1;
                act->info = act->ant->info;
                act->ant->info = inf;
                act->tamInfo = act->ant->tamInfo;
                act->ant->tamInfo = tam;
            }
            act = act->ant;
        }
        inf = act;
    }
}


//////////////////////FORMA DEL PROFE DE HACER EL INSERTAR EN ORDEN//////////////////////////
/*
typedef struct sNodoD
{
    void * info;
    unsigned tamInfo;
    struct sNodoD* sig,
                 * ant;
}tNodoD;

typedef tNodoD* tListaD;

void crearListaD(tListaD* pl);

int ponerOrdListaD(tListaD* pl, const void * pd, unsigned tam,
                   int (*cmp)(const void*, const void*));

#include "lista_doble.h"
#include <stdlib.h>
#include <string.h>


void crearListaD(tListaD* pl)
{
    *pl = NULL;
}

int ponerOrdListaD(tListaD* pl, const void * pd, unsigned tam,
                   int (*cmp)(const void*, const void*))
{
    tNodoD* auxSig = *pl,
          * auxAnt = auxSig? auxSig->ant : NULL,
          * nue;

    while(auxSig && cmp(pd, auxSig->info)>0)
    {
        auxAnt = auxSig;
        auxSig = auxSig->sig;
    }

    while(auxAnt && cmp(pd, auxAnt->info)<0)
    {
        auxSig = auxAnt;
        auxAnt = auxAnt->ant;
    }

    if((auxSig && cmp(pd, auxSig->info)==0)
       || (auxAnt && cmp(pd, auxAnt->info)==0))
    {
        return 0; ///Duplicado
    }

    if ((nue = (tNodoD*)malloc(sizeof(tNodoD)))==NULL
        || (nue->info = malloc(tam))==NULL)
    {
        free(nue);
        return 0; ///Sin Mem
    }

    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    nue->sig = auxSig;
    nue->ant = auxAnt;
    if (auxSig)
        auxSig->ant = nue;
    if (auxAnt)
        auxAnt->sig = nue;

    *pl = nue;

    return 1;
}

*/
////////////////////////////////////////////////////////////////////////////////////////////////////

int eliminarPorClave(tLista *pl, void *pd, size_t tam,
                     int (*comparar)(const void *, const void *))
{
    tNodo *act = *pl;
    int aux;

    if (act == NULL)
        return 0;  /** Lista vacía **/

    while (act->sig && comparar(act->info, pd) < 0)
        act = act->sig;

    while (act->ant && comparar(act->info, pd) > 0)
        act = act->ant;

    aux = comparar(act->info, pd);

    if (aux == 0)  /** Encontró la clave **/
    {
        tNodo *ant = act->ant,
              *sig = act->sig;

        if (ant)
            ant->sig = sig;
        if (sig)
        {
            sig->ant = ant;
            *pl = sig;
        }
        else
            *pl = ant;

        memcpy(pd, act->info, tam);
        free(act->info);
        free(act);
        return 1;
    }
    return 0;
}
