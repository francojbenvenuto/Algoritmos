#include "ColaDinamica.h"

void CrearCola(tCola *pc)
{
    pc->pri = pc->ult = NULL;
}

int PonerEnCola(tCola *pc,const void *pd,size_t tam)
{
    tNodo *nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }
    nue->tamInfo = tam;
    memcpy(nue->info,pd,tam);
    nue->sig = NULL;

    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;
    pc->ult = nue;

    return 1;
}

int SacarDeCola(tCola *pc,void *pd,size_t tam)
{
    tNodo *elim = pc->pri;
    if(!elim)
        return 0;
    memcpy(pd,elim->info,MINIMO(tam,elim->tamInfo));
    pc->pri = elim->sig;
    if(!pc->pri)
        pc->ult = NULL;
    free(elim->info);
    free(elim);
    return 1;
}

int VerPrimeroEnCola(const tCola *pc,void *pd, size_t tam)
{
    if(pc->pri == NULL)
        return 0;
    memcpy(pd,pc->pri->info,MINIMO(tam,pc->pri->tamInfo));
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
    return !pc->pri;
}

void VaciarCola(tCola *pc)
{
    while(pc->pri)
    {
        tNodo *aux = pc->pri;
        pc->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    pc->ult = NULL;
}
