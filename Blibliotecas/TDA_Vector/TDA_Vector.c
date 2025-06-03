#include "TDA_Vector.h"

bool crearVector(Vector *v,size_t tamElem, size_t cap)
{
    v->vec=(void*)malloc(cap*tamElem);
    if(!v->vec)
        return false;

    v->ce=0;
    v->cap=cap;
    v->tamElem=tamElem;

    return true;
}
bool redimensionar (Vector * v, size_t nuevacap)
{
    void *nvec;
    nvec= (void*) realloc(v->vec,nuevacap*v->tamElem);
    if(!nvec)
        return false;
    v->vec=nvec;
    v->cap=nuevacap;
    return true;
}

void destruirVector(Vector *v)
{
    free(v->vec);
}

int insertarAlFinal(Vector *v,const void* elem)
{
    if(v->ce==v->cap)
    {
        if(!redimensionar(v,v->cap*2))
            return -1;
    }
    void * posIns = v->vec + v->ce*v->tamElem;
    memcpy(posIns,elem,v->tamElem);
    v->ce++;

    return 0;
}

int insertarEnOrden(Vector *v,void* elem, Cmp cmp)
{
    if(v->ce==v->cap)
    {
       if(!redimensionar(v,v->cap*2))
       {
           return -1;
       }
    }



    void *i = v->vec;
    void *ult = v->vec + (v->ce-1)*v->tamElem;

    while (i<=ult && cmp(elem,i)>0)
        i+= v->tamElem;

    if(i<=ult && cmp(elem,i) == 0)
        return -2;
    memmove(i+v->tamElem,i,ult-i+v->tamElem);
    memcpy(i,elem,v->tamElem);
    v->ce++;
    return 0;
}

bool VectorEliminarOrdenado(Vector *v,void* elem, Cmp cmp)
{
    void *i= v->vec;
    void *ult = v->vec + (v->ce-1)*v->tamElem;
    void *j;

    while (i<=ult && cmp(elem,i)>0)
        i+=v->tamElem;
    if(i>ult || cmp(elem,i)<0)
        return false;
    for (j=i+v->tamElem; j<ult; j+=v->tamElem)
        memcpy(j-v->tamElem,j,v->tamElem);
    v->ce--;

    if(v->ce*3<=v->cap)
        redimensionar(v,v->cap/2);

    return true;
}

bool vectorBuscarOrdenado(const Vector *v,void *elem,Cmp cmp)
{
    void *ult = v->vec + (v->ce-1)*v->tamElem;
    void *i = v->vec;
    while(i<=ult && cmp(elem,i)>0)
        i+=v->tamElem;

    if(i>ult || cmp(elem,i)<0)
        return false;

    memcpy(elem,i,v->tamElem);
    return true;
}

void OrdenarSeleccion(Vector *v, Cmp cmp)
{
    void* ult = v->vec + (v->ce-1)*v->tamElem;
    void *m,*i;
    for(i=v->vec; i<ult; i+=v->tamElem)
    {
        m = buscarMenor(i,ult,v->tamElem,cmp);
        intercambiarGen(m,i,v->tamElem);
    }
}

void * buscarMenor(void *ini, void *fin, size_t tamElem, Cmp cmp)
{
    void *m =ini,*j;
    for(j = ini+tamElem; j<=fin; j+=tamElem)
    {
        if(cmp(j,m)<0)
            m=j;
    }
    return m;
}

void intercambiarGen(void *a, void *b, size_t tamElem)
{
    void *aux = malloc(tamElem);
    memcpy(aux,a,tamElem);
    memcpy(a,b,tamElem);
    memcpy(b,aux,tamElem);
    free(aux);
}

void Ordenamiento_burbujeo(void *vec,size_t tamElem,int ce,Cmp cmp)
{
    void *lec= vec;
    void *esc= vec+tamElem;
    int i,j;
    for(i=0; i<ce-1 ; i++)
    {
        for(j=0; j<ce-i-1; j++)
        {
            if(cmp(lec,esc)>0)
            {
                intercambiarGen(lec,esc,tamElem);
            }
            lec+= tamElem;
            esc+= tamElem;
        }
        lec = vec;
        esc = vec+tamElem;
    }
}

int ordenarInsercion(void *vec, int cantElem, size_t tamElem, Cmp cmp)
{
    char *v = (char *)vec;
    int i, j;
    void *elemAIns = malloc(tamElem);
    if (!elemAIns)
    {
        printf("Error al reservar memoria.\n");
        return -1;
    }

    for (i = 1; i < cantElem; i++)
    {
        memcpy(elemAIns, v + i * tamElem, tamElem);
        j = i - 1;

        while (j >= 0 && cmp(v + j * tamElem, elemAIns) > 0)
        {
            memcpy(v + (j + 1) * tamElem, v + j * tamElem, tamElem);
            j--;
        }
        memcpy(v + (j + 1) * tamElem, elemAIns, tamElem);
    }

    free(elemAIns);
    return 0;
}

void mostrar(const Vector *v, Accion accion)
{
    void *i=v->vec;
    void *ult=v->vec + (v->ce-1)*v->tamElem;
    for(i=v->vec; i<=ult; i+=v->tamElem)
        accion(i);
}
