#include <stdio.h>
#include "Funcionarios.h"

#define MAX 100

int main() {
    TFunc *funcionario;
    TFuncKey *funcKey;
    FILE *arq = fopen("funcionarios.bin", "wb+");
    preencherFuncionarios(arq, MAX);
    buscaSequencial(90, arq, MAX);
    printf("\n---------");

    funcKey = keySorting(arq, MAX);
    funcionario = buscaBinaria(91, funcKey, MAX);
    return 0;
}
