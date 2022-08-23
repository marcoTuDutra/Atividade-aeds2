#include <stdio.h>
#include "Funcionarios.h"

#define MAX 100

int main() {
    TFunc funcionarios[MAX];

    preencherFuncionarios(&funcionarios, MAX);
    salvarFuncionarios(&funcionarios, MAX);

    TFunc func = buscaSequencial(99, funcionarios, MAX);
    printf("\n---------------");
    func = buscaBinaria(99, funcionarios, MAX);
    return 0;
}
