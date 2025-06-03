#include "funciones.h"

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

int VerTope(t_pila *pp,void *dato,size_t tam)
{
    size_t tam_pila;
    if(pp->tope==TAM_PILA)
        return PILA_VACIA;
    memcpy(&tam_pila,pp->vec+pp->tope,sizeof(size_t)); // se puede de otra forma muy curiosa :)
    pp->tope += sizeof(size_t);
    memcpy(dato,pp->vec+pp->tope,Min(tam,tam_pila));
    return OK;

}

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

















//////////////////////////////////El PODEROSO SONIC////////////////////////
void Sonic()
{
    printf("\n			     ...,?77??I~~~~I???77?<~....\n                        ..?7`                           `7!.. \n                    .,=`          ..~7^`   I                  ?1. \n       ........  ..^            ?`  ..?7!1 .               ...??7\n      .        .7`        .,777.. .I.    . .!          .,7!\n      ..     .?         .^      .l   ?i. . .`       .,^\n       b    .!        .= .?7???7~.     .>r .      .= \n       .,.?4         , .^         1        `     4... \n        J   ^         ,            5       `         ?<.\n       ./.7;         .`     .,     .;                   .=. \n       .+^ .,       ./      MML     F       .,             ?, \n        P   ,,      J      .MMN     F        6               4.\n        l    d,    ,       .MMM!   .t        ..               ,,\n        ,    JMa..`         MMM`   .         .!                .; \n         r   .M#            .M#   ./  .      .~                 ., \n       dMMMNJ..!                 .P7!  .>    .         .         ,, \n       .WMMMMMm  ?^..       ..,?! ..    ..   ,  Z7`        `?^..  ,, \n          ?THB3       ?77?!        .Yr  .   .!   ?,              ?^C \n            ?,                   .,^.` ./  .^      5. \n              7,          .....?7     .^  ,`        ?. \n                `<.                 .= .`'           1 \n                ....dn... ... ...,7..J=!7,           ., \n             ..=     G.,7  ..,o..  .?    J.           F \n           .J.  .^ ,,,t  ,^        ?^.  .^  `?~.      F \n          r /J. $    5r J             ,r.1      .=.  ./ \n          r .77=?4.    ``,     l ., 1  .. <.       4., \n          .$..    .X..   .n..  ., J. r .`  J.       `' \n        .?`  .5        `` ./   ./ .' L.'    t \n        ,. ..1JL          .,   J .$.?`      . \n                1.          .=` ` .J7??7<.. .; \n                 JS..    ..^      L        7.: \n                   `> ..       J.  4. \n                    +   r `t   r ~=..G.\n                    =   $  ,.  J \n                    2   r   t  .; \n              .,7!  r   t`7~..  j.. \n              j   7~L...$=.?7r   r ;?1. \n               8.      .=    j ..,^   .. \n              r        G              . \n            .,7,        j,           .>=. \n         .J??,  `T....... /             .. \n      ..^     <.  ~.    ,.             .D \n    .?`        1   L     .7.........?Ti..l \n   ,`           L  .    ./    .`!       `j, \n.^             .  ..   .`   .^  .?7!?7+. 1 \n.`              .  .`..`7.  .^  ,`      .i.; \n.7<..........~<<3?7!`    4. r  `          G/ \n                          J.` .!           / \n                            JiJ           .` \n                              .1.         J \n                                 ?1.     .'  \n                                     7<../\n");
}

