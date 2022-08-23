

#ifndef PROVA01_FUNCIONARIOS_H
#define PROVA01_FUNCIONARIOS_H

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

void embaralhar(TFunc *vet, int vetSize);

void preencherFuncionarios(TFunc *funcionarios, int size);

void salvarFuncionarios(TFunc vet[], int size);

TFunc buscaSequencial(int cod, TFunc funcionarios[],int size);

TFunc buscaBinaria(int cod, TFunc funcionarios[], int size);

void keySorting(TFunc *funcionarios);

#endif //PROVA01_FUNCIONARIOS_H
