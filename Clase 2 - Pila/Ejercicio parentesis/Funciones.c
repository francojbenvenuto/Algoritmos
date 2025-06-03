#include "Funciones.h"
//PILA
//No recorrer pila
int PonerEnPila(t_pila * pp,const void * dato,size_t tam)
{
    if(pp->tope < tam+sizeof(size_t))
        return PILA_LLENA; //return 0;
    pp->tope-=tam;
    memcpy(pp->vec+pp->tope,dato,tam);
    pp->tope-=sizeof(size_t);
    memcpy(pp->vec+pp->tope,&tam,sizeof(size_t));
    return OK;
}

int SacarDePila(t_pila * pp,void *dato,size_t tam)
{
    size_t tam_pila;
    if(pp->tope==TAM_PILA)
        return PILA_VACIA;
    memcpy(&tam_pila,pp->vec+pp->tope,sizeof(size_t)); // se puede de otra forma muy curiosa :)
    pp->tope += sizeof(size_t);
    memcpy(dato,pp->vec+pp->tope,Min(tam,tam_pila));
    pp->tope += tam_pila;
    return OK;
}

void CrearPila(t_pila *pp)
{
    pp->tope  = TAM_PILA;
}

//int VerTope(const t_pila *pp,void *dato,size_t tam);

void VaciarPila(t_pila *pp)
{
    pp->tope  = TAM_PILA;
}
int PilaVacia(const t_pila *pp)
{
    if(pp->tope==TAM_PILA)
        return OK;
    else return PILA_LLENA;
}

int PilaLlena(const t_pila *pp,size_t tam)
{
    if(pp->tope==0)
        return OK;
    else return PILA_LLENA;
}



int Min(int a,int b)
{
    if(a<b)return a;
    else return b;
}

int VerTope(t_pila *pp,void *dato,size_t tam)
{
    size_t tam_pila;
    if (pp->tope == TAM_PILA)
        return PILA_VACIA;

    // Hacemos una copia del tope para no modificar el original
    int pos = pp->tope;
    memcpy(&tam_pila, pp->vec + pos, sizeof(size_t));
    pos += sizeof(size_t);
    memcpy(dato, pp->vec + pos, Min(tam, tam_pila));
    return OK;

}

int EsCorrecta(char *cad)
{
    char aux2;
    t_pila pila;
    CrearPila(&pila);

    while (*cad)
    {
        // Si es un carácter de apertura, lo apilamos
        if (*cad == '(' || *cad == '[' || *cad == '{')
        {
            PonerEnPila(&pila, cad, sizeof(char));
        }
        // Si es un carácter de cierre, verificamos el tope
        else if (*cad == ')' || *cad == ']' || *cad == '}')
        {
            // Si la pila está vacía, es incorrecto
            if (VerTope(&pila, &aux2, sizeof(char)) == 0)
                return 0;

            // Comparamos que coincida el tipo de apertura con cierre
            if ((aux2 == '(' && *cad != ')') ||
                    (aux2 == '[' && *cad != ']') ||
                    (aux2 == '{' && *cad != '}'))
            {
                return 0;
            }

            SacarDePila(&pila, &aux2, sizeof(char));
        }

        cad++;
    }

    // Si la pila no está vacía, entonces hay aperturas sin cerrar
    if (!PilaVacia(&pila))
        return 0;

    return 1;


}




