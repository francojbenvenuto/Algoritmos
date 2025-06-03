#include "Funciones.h"

int main()
{
    char cad[] = "(()[{()}])";

    if (EsCorrecta(cad) == 1)
        printf("La cadena %s es correcta\n", cad);
    else
        printf("La cadena %s NO es correcta\n", cad);

    return 0;

    return 0;
}
