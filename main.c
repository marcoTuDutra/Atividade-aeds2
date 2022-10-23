#include <stdio.h>
#include "data/Funcionarios.h"
#include "busca/Busca.h"
#include "ordenacao/Ordenacao.h"
#include "selecao/Selecao.h"
#include "hash/Hash.h"
#define MAX 100

int main() {
    TFunc *func;
    int qtdComparacoes = 0, cod = -1, opc = 0;
    float tempoExecucao;
    FILE *arq = fopen("funcionarios.bin", "wb+");
    FILE *arvoreBinaria = fopen("arvoreBinaria.dat","rb+");
    preencherFuncionarios(arq,MAX);
    gerarParicoesHash(arq,3,30);

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
            int qtd = 1;
            qtd += selecaoNatural(arq);
            arvoreBinariaVenc(qtd, &tempoExecucao);
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


    printf("\n<<<<<TABELA HASH>>>>>");

    opc = 0;
    int part;

    do {
        printf("\nEscolha um metodo: ");
        printf("\n  1- Imprimir particao");
        printf("\n  2- Inserir");
        printf("\n  3- Buscar");
        printf("\n  4- Remover");
        printf("\n  5- Sair");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                printf("\n>>>>>Imprimir particao<<<<<");
                printf("\nInforme a particao: ");
                scanf("%d", &part);
                imprimirParticao(part);
                break;
            case 2:
                printf("\n>>>>>Inserir<<<<<");
                TFunc funcIns;
                int part;
                printf("\nInforme o codigo do funcionario:  ");
                scanf("%d", &funcIns.cod);
                printf("\nInforme o nome do funcionario:  ");
                scanf("%s", &funcIns.nome);
                printf("\nInforme o cpf do funcionario:  ");
                scanf("%s", &funcIns.cpf);
                printf("\nInforme a data de nascimento do funcionario:  ");
                scanf("%s", &funcIns.data_nascimento);
                printf("\nInforme o salario do funcionario:  ");
                scanf("%f", &funcIns.salario);
                printf("\n-------");
                printf("\nInforme a particao a ser inserida:  ");
                scanf("%d", &part);
                inserir(&funcIns, part);
                break;
            case 3:
                printf("");
                printf("\n>>>>>Buscar<<<<<");
                printf("\nInforme o codigo do funcionario:  ");
                scanf("%d", &cod);
                printf("\nInforme a particao: ");
                scanf("%d", &part);
                imprimir(*busca(cod,part));
                break;
            case 4:

                printf("\n>>>>>Remover<<<<<");
                printf("\nInforme o codigo do funcionario:  ");
                scanf("%d", &cod);
                printf("\nInforme a particao: ");
                scanf("%d", &part);
                remover(cod,part);
                break;
        }
    } while (opc != 5);

    fclose(arq);
    fclose(arvoreBinaria);


    return 0;

}
