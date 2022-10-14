#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "Ordenacao.h"
#include "../data/Funcionarios.h"

void keySort(FILE *arq, int size, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    TFunc funcs[size];
    TFunc aux;

    for (int i = 0; i < size; ++i) {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        TFunc *fj = lerFuncionario(arq);
        funcs[i] = *fj;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (funcs[i].cod < funcs[j].cod) {
                aux = funcs[i];
                funcs[i] = funcs[j];
                funcs[j] = aux;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(&funcs[i], arq);
    }

    *tempoExecucao = current_time.tv_usec;
}