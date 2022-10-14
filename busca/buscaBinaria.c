#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "../data/Funcionarios.h"
#include "Busca.h"

TFunc *buscaBinaria(int cod, FILE *arq, int size, int *qtdComparacoes, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    TFunc *funcionario = NULL;
    int inicio = 0, fim = size - 1, meio, comparacoes = 0;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        fseek(arq, meio * sizeof(TFunc), SEEK_SET);
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