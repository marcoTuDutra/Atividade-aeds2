#include <stdio.h>
#include "data/Funcionarios.h"
#include "busca/Busca.h"
#include "ordenacao/Ordenacao.h"
#include "selecao/Selecao.h"
#define MAX 100

int main() {
    TFunc *func;
    int qtdComparacoes = 0, cod = -1, opc = 0;
    float tempoExecucao;
    FILE *arq = fopen("funcionarios.bin", "wb+");
    FILE *arvoreBinaria = fopen("arvoreBinaria.dat","rb+");
    preencherFuncionarios(arq,MAX);

    do {
        printf("\nInforme o valor do codigo do funcionario (entre 0 e 100): ");
        scanf("%d", &cod);
    } while (cod < 0 || cod>=100);

    do {
        printf("\nEscolha o metodo de ordenacao: ");
        printf("\n  1- Key Sort");
        printf("\n  2- Insertion Sort");
        printf("\n  3- Arvore de vencedores");
        scanf("%d", &opc);
    } while (opc < 1 || opc > 3);



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

    switch (opc) {
        case 1:
            printf("\n>>>>>Key Sort<<<<<");
            keySort(arq,MAX, &tempoExecucao);
            printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
            printf("\n ");
            break;
        case 2:
            printf("\n>>>>>Insertion Sort<<<<<");
            insertionSort(arq,MAX, &tempoExecucao);
            printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
            printf("\n ");
            break;
        case 3:
            printf("\n>>>>>Arvore Binaria de Vencedores<<<<<");
            int numberOfPartition = 1;
            numberOfPartition += selecaoNatural(arq);
            arvoreBinariaVenc(numberOfPartition, &tempoExecucao);
            FILE *arvoreBinaria = fopen("arvoreBinaria.dat","rb+");
            printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
            printf("\n ");
    }

    if(opc == 3){
        printf("\n>>>>>Binaria<<<<<");
        func = buscaBinaria(cod, arvoreBinaria,MAX, &qtdComparacoes, &tempoExecucao);
        printf("\nQuantidade de comparacoes: %d", qtdComparacoes);
        printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
    } else{
        printf("\n>>>>>Binaria<<<<<");
        func = buscaBinaria(cod, arq,MAX, &qtdComparacoes, &tempoExecucao);
        printf("\nQuantidade de comparacoes: %d", qtdComparacoes);
        printf("\nTempo de execucao em microsegundos: %f", tempoExecucao);
    }

    if(func == NULL){
        printf("\nFuncionario nao encontrado!");
    } else{
        imprimir(*func);
        printf("\n ");
    }


    fclose(arq);
    fclose(arvoreBinaria);

    return 0;

}
