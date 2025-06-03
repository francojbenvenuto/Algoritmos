#include"Funciones.h"

void crear_cola(tCola *pc)
{
    pc->pri = pc->ult = NULL;
}


int poner_en_cola(tCola *pc, const void *pd, unsigned tam)
{
    tNodo * nue = (tNodo*) malloc(sizeof(tNodo));
    if(!nue)
    {
        return 0; //COLA_LLENA
    }

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0; //COLA_LLENA
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = NULL;
    if(pc->ult)
    {
        pc->ult->sig = nue;
    }
    else
    {
        pc->pri = nue;
    }
    pc->ult = nue;

    return 1;  // OK
}

int sacar_de_cola(tCola *pc, void *pd, unsigned tam)
{
    tNodo * elim = pc->pri;
    if(!elim)
    {
        return 0;  ///COLA_VACIA
    }
    memcpy(pd, elim->info, MINIMO(tam, elim->tamInfo));
    pc->pri = elim->sig;

    if(!pc->pri)
    {
        pc->ult = NULL;
    }

    free(elim->info);
    free(elim);

    return 1;  ///OK
}

int cola_vacia(const tCola *pc)
{
    return !pc->pri;
}

int verPrimeroCola(const tCola *p, void *d, unsigned cantBytes)
{
    if(p->pri == NULL)
        return 0;
    memcpy(d, p->pri->info, MINIMO(cantBytes, p->pri->tamInfo));
    return 1;
}
void vaciarCola(tCola *p)
{
    while(p->pri)
    {
        tNodo *aux = p->pri;
        p->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->ult = NULL;
}

int colaLlena(const tCola *p, unsigned cantBytes) {
    tNodo *aux = (tNodo *)malloc(sizeof(tNodo));
    void *info = malloc(cantBytes);
    free(aux);
    free(info);
    return aux == NULL || info == NULL;
}
