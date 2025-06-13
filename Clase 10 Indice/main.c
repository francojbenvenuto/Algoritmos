#include <stdio.h>
#include <stdlib.h>

#define Sonic printf("\n			     ...,?77??I~~~~I???77?<~....\n                        ..?7`                           `7!.. \n                    .,=`          ..~7^`   I                  ?1. \n       ........  ..^            ?`  ..?7!1 .               ...??7\n      .        .7`        .,777.. .I.    . .!          .,7!\n      ..     .?         .^      .l   ?i. . .`       .,^\n       b    .!        .= .?7???7~.     .>r .      .= \n       .,.?4         , .^         1        `     4... \n        J   ^         ,            5       `         ?<.\n       ./.7;         .`     .,     .;                   .=. \n       .+^ .,       ./      MML     F       .,             ?, \n        P   ,,      J      .MMN     F        6               4.\n        l    d,    ,       .MMM!   .t        ..               ,,\n        ,    JMa..`         MMM`   .         .!                .; \n         r   .M#            .M#   ./  .      .~                 ., \n       dMMMNJ..!                 .P7!  .>    .         .         ,, \n       .WMMMMMm  ?^..       ..,?! ..    ..   ,  Z7`        `?^..  ,, \n          ?THB3       ?77?!        .Yr  .   .!   ?,              ?^C \n            ?,                   .,^.` ./  .^      5. \n              7,          .....?7     .^  ,`        ?. \n                `<.                 .= .`'           1 \n                ....dn... ... ...,7..J=!7,           ., \n             ..=     G.,7  ..,o..  .?    J.           F \n           .J.  .^ ,,,t  ,^        ?^.  .^  `?~.      F \n          r /J. $    5r J             ,r.1      .=.  ./ \n          r .77=?4.    ``,     l ., 1  .. <.       4., \n          .$..    .X..   .n..  ., J. r .`  J.       `' \n        .?`  .5        `` ./   ./ .' L.'    t \n        ,. ..1JL          .,   J .$.?`      . \n                1.          .=` ` .J7??7<.. .; \n                 JS..    ..^      L        7.: \n                   `> ..       J.  4. \n                    +   r `t   r ~=..G.\n                    =   $  ,.  J \n                    2   r   t  .; \n              .,7!  r   t`7~..  j.. \n              j   7~L...$=.?7r   r ;?1. \n               8.      .=    j ..,^   .. \n              r        G              . \n            .,7,        j,           .>=. \n         .J??,  `T....... /             .. \n      ..^     <.  ~.    ,.             .D \n    .?`        1   L     .7.........?Ti..l \n   ,`           L  .    ./    .`!       `j, \n.^             .  ..   .`   .^  .?7!?7+. 1 \n.`              .  .`..`7.  .^  ,`      .i.; \n.7<..........~<<3?7!`    4. r  `          G/ \n                          J.` .!           / \n                            JiJ           .` \n                              .1.         J \n                                 ?1.     .'  \n                                     7<../\n");
#include "E:\Blibliotecas\TDA_Arbol\TDA_Arbol.h"

int main()
{

    return 0;
}



// 1 generar indice

void generarIdx()
{
    reg =0;
    fread(&alu,sizeof(alu),1,f_alu);
    while(!feof(f_alu))
    {
        if(alu.estado == 'A')
        {
            t_ind.dni = alu.dni;
            t_ind.reg_ind =  reg;
            InsertarArbolBin(&indice,&reg_ind,sizeof(reg_ind),cmpDni);
            reg ++;
        }
        fread(&alu,sizeof(alu),1,f_alu);
    }
}


void guardarIndice()
{
FILE * pf_indice= fopen(alum.idx,wb);
RecorrerEnOrdenArbolBin(&indice,guardar_reg_ind_dni,pf_indice);
}

void cargarIdx()
{
    t_arbol indice_dni;
    generarIdx(&indice_dni);
    CargarDesdeDatosOrdenadosArbolBin(&indice_dni,"alumno_dni.idx",sizeof(t_ind_dni));
}

void DarAlta()
{
    //  1° buscar que existe, buscar en el arbol
    //  2°
    fseek(pf_alu,0L,SEEK_END);
    nro_reg= ftell(f_alu)/ sizeof(t_alu);
    //  3° insertar en el arbol

    reg_ind.dni = alu.dni;
    reg_ind.nro_reg = nro_reg;

    InsertarArbolBin(&indice.dni,&reg_ind, sizeof(reg_ind),cmp_dni);
    fwrite(&alu,....,pf_alu);
}


void darBaja()
{
    reg_ind.dni = dni;
    EliminarElemArbolBin(&indice,&reg_ind,cmp_dni);
    if (eliminar == ok)
    {
        fseek(pf_alu, reg_ind.nro_reg*sizeof(t-alu));
        fread(&alu,sizeof(alu),1,f_alu);
        alu.estado = 'B';
        fseek(pf_alu,-(LONG)sizeof(t_alu),SEEK_CUR);
        fwrite(&alu,....,pf_alu);

    }
}



void imprimirEnOrde()
{
}




