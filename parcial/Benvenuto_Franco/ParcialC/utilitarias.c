#include<utilitarias.h>
#include<varias.h>

int cmp_dni(const void *a1, const void *a2)
{
    const tRegInd *reg1 = (const tRegInd *)a1;
    const tRegInd *reg2 = (const tRegInd *)a2;
    return reg1->dni - reg2->dni;
}

int baja(tAlumno *alu, FILE *arch, tArbolBinBusq *pa)
{
    tRegInd registroInd;
    tAlumno aluEncontrado;
    registroInd.dni = alu->dni;
    if (buscarElemArbolBinBusq(pa, &registroInd, sizeof(tRegInd), cmp_dni) != TODO_OK)
        return NO_EXISTE;

    fseek(arch, registroInd.nro_reg * sizeof(tAlumno), SEEK_SET); ///posiciono en el indice pedido
    fread(&aluEncontrado, sizeof(tAlumno), 1, arch);

    if (aluEncontrado.estado == 'B')
        return NO_EXISTE;
    aluEncontrado.estado = 'B';

    fseek(arch, registroInd.nro_reg * sizeof(tAlumno), SEEK_SET); /// Volver a la posición
    fwrite(&aluEncontrado, sizeof(tAlumno), 1, arch);

    //fseek(arch, registroInd.nro_reg * sizeof(tAlumno), SEEK_SET);
    return eliminarElemArbolBinBusq(pa, &registroInd, sizeof(tRegInd), cmp_dni);
}
