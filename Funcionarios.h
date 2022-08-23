

#ifndef PROVA01_FUNCIONARIOS_H
#define PROVA01_FUNCIONARIOS_H

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

typedef struct FuncionarioKey {
    int cod;
    TFunc *RRN;
} TFuncKey;

void embaralhar(TFunc *vet, int vetSize);

void preencherFuncionarios(FILE *arq, int size);

TFunc *lerFuncionaio(FILE *arq);

void salvarFuncionarios(TFunc *func, FILE *arq);

TFunc *buscaSequencial(int cod, FILE *arq, int size);

TFunc *buscaBinaria(int cod, TFuncKey *funcKey, int size);

TFuncKey *keySorting(FILE *arq, int size);

#endif //PROVA01_FUNCIONARIOS_H
