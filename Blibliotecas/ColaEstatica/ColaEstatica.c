#include "ColaEstatica.h"

#define minimo( X , Y ) (( X ) <= ( Y ) ? ( X ) : ( Y ))

void CrearCola(tCola *pc)
{
    pc->pri = TAM_COLA - 70;
    pc->ult = TAM_COLA - 70;
    pc->tamDisp = TAM_COLA;
}

int PonerEnCola(tCola *pc, const void *pd, size_t tam)
{
    size_t ini, fin;

    if(pc->tamDisp < sizeof(tam) + tam)
        return 0;

    if((ini = minimo(sizeof(tam), TAM_COLA - pc->ult)) > 0)
        memcpy(pc->cola + pc->ult, &tam, ini);

    if((fin = sizeof(tam) - ini) > 0)
        memcpy(pc->cola, ((char *)&tam) + ini, fin);

    pc->ult = fin ? fin : pc->ult + ini;

    if((ini = minimo(tam, TAM_COLA - pc->ult)) > 0)
        memcpy(pc->cola + pc->ult, pd, ini);

    if((fin = tam - ini) > 0)
        memcpy(pc->cola, ((char *)pd) + ini, fin);

    pc->ult = fin ? fin : pc->ult + ini;

    pc->tamDisp -= sizeof(tam) + tam;

    return 1;
}

int SacarDeCola(tCola *pc, void *pd, size_t tam)
{
    size_t tamInfo, ini, fin;

    if(pc->tamDisp == TAM_COLA)
        return 0;

    if((ini = minimo(sizeof(tam), TAM_COLA - pc->pri)) > 0)
        memcpy(&tamInfo, pc->cola + pc->pri, ini);

    if((fin = sizeof(tam) - ini) > 0)
        memcpy(((char *)&tamInfo) + ini, pc->cola, fin);

    pc->pri = fin ? fin : pc->pri + sizeof(tam);

    if((ini = minimo(tamInfo, TAM_COLA - pc->pri)) > 0)
        memcpy(pd, pc->cola + pc->pri, minimo(ini,tam));

    if((fin = tamInfo - ini) > 0 && (tam-ini) > 0)
        memcpy(((char *)pd) + ini, pc->cola, minimo(fin,tam-ini));

    pc->pri = fin ? fin : pc->pri + tamInfo;

    pc->tamDisp += sizeof(tam) + tamInfo;

    return 1;
}

int VerPrimeroEnCola(const tCola *pc, void *pd, size_t tam)
{
    size_t tamInfo, ini, fin, pos = pc->pri;

    if(pc->tamDisp == TAM_COLA)
        return 0;

    if((ini = minimo(sizeof(tam), TAM_COLA - pos)) > 0)
        memcpy(&tamInfo, pc->cola + pos, ini);

    if((fin = sizeof(tam) - ini) > 0)
        memcpy(((char *)&tamInfo) + ini, pc->cola, fin);

    pos = fin ? fin : pos + ini;

    tamInfo = minimo(tamInfo, tam);

    if((ini = minimo(tamInfo, TAM_COLA - pos)) > 0)
        memcpy(pd, pc->cola + pos, ini);

    if((fin = tamInfo - ini) > 0)
        memcpy(((char *)pd) + ini, pc->cola, fin);

    return 1;
}

int ColaLlena(tCola *pc, size_t tam)
{
    return pc->tamDisp < tam + sizeof(tam);
}

int ColaVacia(const tCola *pc)
{
    return pc->tamDisp == TAM_COLA;
}

void VaciarCola(tCola *pc)
{
    pc->ult = pc->pri;
    pc->tamDisp = TAM_COLA;
}
