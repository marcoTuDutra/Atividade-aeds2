#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "../data/Funcionarios.h"

void insertionSort(FILE *arq, int size, float *tempoExecucao) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    rewind(arq);
    int i;

    for (int j = 2; j <= size; j++) {
        fseek(arq, (j - 1) * sizeof(TFunc), SEEK_SET);
        TFunc *fj = lerFuncionario(arq);
        i = j - 1;
        fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
        do {
            TFunc *fi = lerFuncionario(arq);
            if (fi->cod < fj->cod) {
                break;
            }
            fseek(arq, i * sizeof(TFunc), SEEK_SET);
            salvarFuncionarios(fi, arq);
            i = i - 1;
            fseek(arq, (i - 1) * sizeof(TFunc), SEEK_SET);
            free(fi);
        } while (i > 0);
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(fj, arq);
        free(fj);
    }

    fflush(arq);
    *tempoExecucao = current_time.tv_usec;
}
