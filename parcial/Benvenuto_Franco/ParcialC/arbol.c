#include <tipos.h>
#include <arbol.h>

static void grabarNodoEnArchivo(void *info, unsigned tam, void *params);
static tNodoArbol **buscarNodoArbolBinBusq(tArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *));
static tNodoArbol **mayorNodoArbolBinBusq(const tArbolBinBusq * p);
static tNodoArbol **menorNodoArbolBinBusq(const tArbolBinBusq * p);

void vaciarArbolBin(tArbolBinBusq *p)
{
    if (!*p)
        return;

    vaciarArbolBin(&(*p)->izq);
    vaciarArbolBin(&(*p)->der);

    free((*p)->info);
    free(*p);
    *p = NULL;
}

int grabarEnArchivoOrdenadoArbolBin(tArbolBinBusq *p, const char *path)
{
    FILE *pf = fopen(path, "wb");
    if (!pf)
        return ERROR_ARCHIVO;
    recorrerEnOrdenSimpleArbolBinBusq(p, pf, grabarNodoEnArchivo);
    fclose(pf);
    return TODO_OK;
}


void recorrerEnOrdenSimpleArbolBinBusq(const tArbolBinBusq *p, void *params,
                                       void (*accion)(void *, unsigned, void *))
{
    if (!*p)
        return;

    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->izq, params, accion);
    accion((*p)->info, (*p)->tamInfo, params);
    recorrerEnOrdenSimpleArbolBinBusq(&(*p)->der, params, accion);
}



static void grabarNodoEnArchivo(void *info, unsigned tam, void *params)
{
    FILE *pf = (FILE*)params;
    fwrite(info, tam, 1, pf);
}



int buscarElemArbolBinBusq(const tArbolBinBusq *p, void *d, unsigned tam,
                           int (*cmp)(const void *, const void *))
{
    tNodoArbol **NodoBusqueda = buscarNodoArbolBinBusq((tArbolBinBusq *)p, d, cmp);

    if (!NodoBusqueda)
        return NO_EXISTE;

    memcpy(d, (*NodoBusqueda)->info, tam < (*NodoBusqueda)->tamInfo ? tam : (*NodoBusqueda)->tamInfo);

    return TODO_OK;
}


static tNodoArbol **buscarNodoArbolBinBusq(tArbolBinBusq *p, const void *d, int (*cmp)(const void *, const void *))
{
    while (*p)
    {
        int aux = cmp(d, (*p)->info);
        if (aux == 0)
            return p;
        if (aux < 0)
            p = &(*p)->izq;
        else
            p = &(*p)->der;
    }
    return NULL;
}

int eliminarElemArbolBinBusq(tArbolBinBusq *p, void *d, unsigned tam,
                             int (*cmp)(const void *, const void *))
{
    tNodoArbol **nodoElim = buscarNodoArbolBinBusq(p, d, cmp);

    if (!nodoElim)
        return NO_EXISTE;

    memcpy(d, (*nodoElim)->info, tam < (*nodoElim)->tamInfo ? tam : (*nodoElim)->tamInfo);

    return eliminarRaizArbolBinBusq(nodoElim);
}


int eliminarRaizArbolBinBusq(tArbolBinBusq *p)
{
    tNodoArbol **rem, *elim;
    if(!*p)
        return NO_EXISTE;

    free((*p)->info);

    if(!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p = NULL;
        return TODO_OK;
    }

    rem = alturaArbolBin(&(*p)->izq)>alturaArbolBin(&(*p)->der) ? mayorNodoArbolBinBusq(&(*p)->izq) : menorNodoArbolBinBusq(&(*p)->der);
    elim = *rem;
    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;
    *rem = elim->izq ? elim->izq : elim->der;
    free(elim);
    return TODO_OK;
}

unsigned alturaArbolBin(const tArbolBinBusq *p)
{
    int hi, hd;
    if (!*p)
        return TODO_OK;
    hi = alturaArbolBin(&(*p)->izq);
    hd = alturaArbolBin(&(*p)->der);
    return (hi > hd ? hi : hd) + 1;
}

static tNodoArbol **mayorNodoArbolBinBusq(const tArbolBinBusq * p)
{
    if(!*p)
        return NULL;
    while((*p)->der)
        p = &(*p)->der;
    return (tNodoArbol **) p;
}

static tNodoArbol **menorNodoArbolBinBusq(const tArbolBinBusq * p)
{
     if(!*p)
        return NULL;
    while((*p)->izq)
        p = &(*p)->izq;
    return (tNodoArbol **) p;
}
