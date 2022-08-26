#include <stdio.h>
#include <stdlib.h>
#include "Funcionarios.h"

#define MAX 100

int main() {
    TFunc *func;
    int qtdComparacoes = 0, cod = -1, opc = 0;
    float tempoExecucao;
    FILE *arq = fopen("funcionarios.bin", "wb+");

    preencherFuncionarios(arq, MAX);

    do {
        printf("\nInforme o valor do codigo do funcionario (entre 0 e 100): ");
        scanf("%d", &cod);
    } while (cod < 0 || cod>=100);

    do {
        printf("\nEscolha o metodo de ordenacao: ");
        printf("\n  1- Key Sort");
        printf("\n  2- Insertion Sort");
        scanf("%d", &opc);
    } while (opc != 1 && opc!= 2);



    printf("\n>>>>>Sequencial<<<<");
    func = buscaSequencial(cod, arq, MAX, &qtdComparacoes, &tempoExecucao);
    printf("\nQuantidade de comparacoes: %d", qtdComparacoes);
    printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);

    if(func == NULL){
        printf("\nFuncionario nao encontrado!");
    } else{
        imprimir(*func);
        printf("\n ");
    }

    if(opc == 1){
        printf("\n>>>>>Key Sort<<<<<");
        keySort(arq,MAX, &tempoExecucao);
        printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
        printf("\n ");
    } else{
        printf("\n>>>>>Insertion Sort<<<<<");
        insertionSort(arq,MAX, &tempoExecucao);
        printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
        printf("\n ");
    }


    printf("\n>>>>>Binaria<<<<<");
    func = buscaBinaria(cod, arq,MAX, &qtdComparacoes, &tempoExecucao);
    printf("\nQuantidade de comparacoes: %d", qtdComparacoes);
    printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);

    if(func == NULL){
        printf("\nFuncionario nao encontrado!");
    } else{
        imprimir(*func);
        printf("\n ");
    }

    return 0;

}
