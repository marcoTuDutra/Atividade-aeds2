#include <stdio.h>
#include "Funcionarios.h"

#define MAX 100

int main() {
    TFunc *func;
    TFuncKey *funcKey;
    int qtdComparacoes = 0;
    float tempoExecucao;

    FILE *arq = fopen("funcionarios.bin", "wb+");

    preencherFuncionarios(arq, MAX);

    func = buscaSequencial(10, arq, MAX, &qtdComparacoes, &tempoExecucao);
    printf("\nQuntidade de comparacoes: %d", qtdComparacoes);
    printf("\nTempo de execucao em microsegundos: : %f", tempoExecucao);

    if(func == NULL){
        printf("\nFuncionario nao encontrado!");
    } else{
        imprimir(*func);
    }

    printf("\n---------");

    funcKey = keySorting(arq, MAX);
    func = buscaBinaria(34, funcKey, MAX, &qtdComparacoes, &tempoExecucao);
    printf("\nQuntidade de comparacoes: %d", qtdComparacoes);
    printf("\nTempo de execucao em microsegundos: : %f", tempoExecucao);

    if(func == NULL){
        printf("\nFuncionario nao encontrado!");
    } else{
        imprimir(*func);
    }

    return 0;

}
