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

TFunc *lerFuncionario(FILE *arq) {
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
    TFunc funcionarios[100];
    for (int i = 0; i < size; ++i) {
        funcionarios[i].cod = i;
        sprintf(funcionarios[i].nome, "%d", i);
        sprintf(funcionarios[i].cpf, "%d", i);
        sprintf(funcionarios[i].data_nascimento, "%d", i);
        funcionarios[i].salario = i;
    }

    embaralhar(funcionarios, size);
    for (int i = 0; i < size; ++i) {
        fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(&funcionarios[i], arq);
    }
}

TFunc *buscaSequencial(int cod, FILE *arq, int size, int *qtdComparacoes, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    TFunc *funcionario = NULL;
    int comparacoes = 0;


    for (int i = 0; i < size; ++i) {
        TFunc *func = lerFuncionario(arq);
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        comparacoes++;
        if (func->cod == cod) {
            funcionario = func;
            break;
        }
    }

    *tempoExecucao = current_time.tv_usec;
    *qtdComparacoes = comparacoes;
    fseek(arq, 0, SEEK_SET);
    return funcionario;
}

TFunc *buscaBinaria(int cod, FILE *arq, int size, int *qtdComparacoes, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    TFunc *funcionario = NULL;
    int inicio = 0, fim = size - 1, meio, comparacoes = 0;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        fseek(arq, meio* sizeof(TFunc), SEEK_SET);
        TFunc *func = lerFuncionario(arq);

        comparacoes++;
        if (cod == func->cod) {
            funcionario = func;
            break;
        }
        comparacoes++;
        if (cod < func->cod) {
            fim = meio - 1;
            continue;
        }
        comparacoes++;
        if (cod > func->cod) {
            inicio = meio + 1;
            continue;
        } else {
            funcionario = NULL;
            break;
        }
    }

    *tempoExecucao = current_time.tv_usec;
    *qtdComparacoes = comparacoes;
    return funcionario;
}

void keySort(FILE *arq, int size, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    TFuncKey *funcKey = (TFunc *) malloc(sizeof(TFunc));
    TFuncKey aux;

    for (int i = 0; i < size; ++i) {
        TFunc *func = lerFuncionario(arq);
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        funcKey[i].cod = func->cod;
        funcKey[i].RRN = func;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (funcKey[i].cod < funcKey[j].cod) {
                aux = funcKey[i];
                funcKey[i] = funcKey[j];
                funcKey[j] = aux;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        fseek(arq, i  * sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(funcKey[i].RRN, arq);
    }
    *tempoExecucao = current_time.tv_usec;
}

void insertionSort(FILE *arq, int size, float *tempoExecucao){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    rewind(arq);
    int i;

    for(int j = 2; j <= size; j++){
        fseek(arq, (j-1)*sizeof(TFunc), SEEK_SET);
        TFunc *fj = lerFuncionario(arq);
        i = j -1;
        fseek(arq, (i-1)*sizeof(TFunc), SEEK_SET);
        do{
            TFunc *fi = lerFuncionario(arq);
            if(fi->cod < fj->cod){
                break;
            }
            fseek(arq, i*sizeof(TFunc), SEEK_SET);
            salvarFuncionarios(fi, arq);
            i = i-1;
            fseek(arq, (i-1)*sizeof(TFunc), SEEK_SET);
            free(fi);
        } while(i > 0);
        fseek(arq, i*sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(fj, arq);
        free(fj);
    }

    fflush(arq);
    *tempoExecucao = current_time.tv_usec;
}

void imprimir(TFunc func) {
    printf("\n COD: %d", func.cod);
    printf("\n NOME: %s", func.nome);
    printf("\n CPF: %s", func.cpf);
    printf("\n DTA. NASC.: %s", func.data_nascimento);
    printf("\n SALARIO: %f", func.salario);
}