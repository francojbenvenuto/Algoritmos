#include "ColaCircular.h"

void CrearCola(tCola *pc)
{
    *pc = NULL;
}

int PonerEnCola(tCola *pc,const void *pd,size_t tam)
{
    tNodo *nue;

    if((nue = (tNodo *)malloc(sizeof(tNodo))) == NULL || (nue->info = malloc(tam)) == NULL)
    {
        free(nue);
        return 0;
    }
    memcpy(nue->info, pd, tam);
    nue->tamInfo = tam;

    if(*pc == NULL)
    {
        nue->sig = nue;
    }
    else
    {
        nue->sig = (*pc)->sig;
        (*pc)->sig = nue;
    }

    *pc = nue;

    return 1;
}

int SacarDeCola(tCola *pc,void *pd,size_t tam)
{
    tNodo *aux;
     if(*pc == NULL)
        return 0;
     aux = (*pc)->sig;
     memcpy(pd, aux->info, MINIMO(tam, aux->tamInfo));
     if(aux == *pc)
        *pc = NULL;
     else
        (*pc)->sig = aux->sig;
     free(aux->info);
     free(aux);
     return 1;
}

int VerPrimeroEnCola(const tCola *pc,void *pd, size_t tam)
{
    if(*pc == NULL)
        return 0;
    memcpy(pd,(*pc)->sig->info,MINIMO(tam,(*pc)->sig->tamInfo));
    return 1;
}

int ColaLlena(const tCola *pc, size_t tam)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tam);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}

int ColaVacia(const tCola *pc)
{
    return *pc == NULL;
}

void VaciarCola(tCola *pc)
{
    while(*pc)
    {
        tNodo *aux = (*pc)->sig;

        if(*pc == aux)
            *pc = NULL;
        else
            (*pc)->sig = aux->sig;

        free(aux->info);
        free(aux);
    }
}
