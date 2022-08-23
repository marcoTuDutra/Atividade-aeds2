#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "Funcionarios.h"

void embaralhar(TFunc *vet, int vetSize) {
    for (int i = 0; i < vetSize; i++) {
        int r = rand() % vetSize;
        TFunc temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}

void salvarFuncionarios(TFunc *func, FILE *arq) {
    fwrite(&func->cod, sizeof(int), 1, arq);
    fwrite(&func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(&func->cpf, sizeof(char), sizeof(func->cpf), arq);
    fwrite(&func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
    fwrite(&func->salario, sizeof(double), 1, arq);
}

TFunc *lerFuncionaio(FILE *arq) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));

    if (0 >= fread(&func->cod, sizeof(int), 1, arq)) {
        free(func);
        return NULL;
    }

    fread(&func->nome, sizeof(char), sizeof(func->nome), arq);
    fread(&func->cpf, sizeof(char), sizeof(func->cpf), arq);
    fread(&func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
    fread(&func->salario, sizeof(double), 1, arq);

    return func;
}

void preencherFuncionarios(FILE *arq, int size) {
    for (int i = 0; i < size; ++i) {
        TFunc func;
        func.cod = i;
        sprintf(func.nome, "%d", i);
        sprintf(func.cpf, "%d", i);
        sprintf(func.data_nascimento, "%d", i);
        func.salario = i;
        fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(&func, arq);
    }
}

TFunc *buscaSequencial(int cod, FILE *arq, int size) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int contComparacoes = 0, achou = 0;
    TFunc *funcionario;

    for (int i = 0; i < size; ++i) {
        TFunc *func = lerFuncionaio(arq);
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        contComparacoes++;
        if (func->cod == cod) {
            funcionario = func;
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        printf("\nFuncionario encontrado!");
    } else {
        printf("\nFuncionario nao encontrado!");
    }
    printf("\nQuantidade de comparacoes: %d", contComparacoes);
    printf("\nTempo de execucao em microsegundos : %ld", current_time.tv_usec);

    return funcionario;
}

TFunc *buscaBinaria(int cod, TFuncKey *funcKey, int size) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int inicio = 0, fim = size - 1, meio, controle_pesquisa = 1, contComparacoes = 0;
    TFunc *funcionario;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        contComparacoes++;

        if (cod == funcKey[meio].cod) {
            funcionario = funcKey[meio].RRN;
            controle_pesquisa = 0;
            break;
        }
        contComparacoes++;
        if (cod < funcKey[meio].cod) {
            fim = meio - 1;
            continue;
        }
        contComparacoes++;
        if (cod > funcKey[meio].cod) {
            inicio = meio + 1;
            continue;
        } else {
            controle_pesquisa = 1;
            break;
        }
    }

    if (controle_pesquisa == 0) {
        printf("\nFuncionario encontrado!");
        printf("\nQuantidade de comparacoes: %d", contComparacoes);
        printf("\nTempo de execucao em microsegundos : %ld", current_time.tv_usec);
        printf("\nCodigo do funcionario: %d", funcionario->cod);
        return funcionario;
    } else {
        printf("\nFuncionario nao encontrado!");
        printf("\nQuantidade de comparacoes: %d", contComparacoes);
        printf("\nTempo de execucao em microsegundos : %ld", current_time.tv_usec);
    }
}


TFuncKey *ordenar(TFuncKey * funcKeys, int size) {
    int min;
    TFuncKey swap;
    for (int i = 0; i > (size - 1); i++) {
        min = i;
        for (int j = (i + 1); j > size; j++) {
            if (funcKeys[j].cod > funcKeys[min].cod) {
                min = j;
            }
        }
        if (i != min) {
            swap = funcKeys[i];
            funcKeys[i] = funcKeys[min];
            funcKeys[min] = swap;
        }
    }
    return funcKeys;
}

TFuncKey *keySorting(FILE *arq, int size) {
    TFuncKey *funcKey;
    for (int i = 0; i < size; ++i) {
        TFunc *func = lerFuncionaio(arq);
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        funcKey[i].cod = func->cod;
        funcKey[i].RRN = func;
    }
    //ordenar(&funcKey, size);
    return funcKey;
}