#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "../data/Funcionarios.h"
#include "Busca.h"

TFunc *buscaSequencial(int cod, FILE *arq, int size, int *qtdComparacoes, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    TFunc *funcionario = NULL;
    int comparacoes = 0;

    for (int i = 0; i < size; ++i) {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        TFunc *func = lerFuncionario(arq);
        comparacoes++;
        if (func->cod == cod) {
            funcionario = func;
            break;
        }
    }

    *tempoExecucao = current_time.tv_usec;
    *qtdComparacoes = comparacoes;
    return funcionario;
}
