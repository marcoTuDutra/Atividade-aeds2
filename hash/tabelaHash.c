#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../data/Funcionarios.h"
#include "Hash.h"

void gerarParicoesHash(FILE *arq, int qtdParticoes, int tam) {

    rewind(arq);

    char nomeArq[100], nome1[100] , nome2[100] = ".dat";

    for (int i = 0; i < tam; ++i) {

        TFunc *funcAuxiliar= lerFuncionario(arq);

        int particao = funcAuxiliar->cod % qtdParticoes;

        itoa(particao, nome1, 10);
        strcat(strcpy(nomeArq, "tblHash"), nome1);
        strcat(strcpy(nomeArq, nomeArq), nome2);

        FILE *arqParticao = fopen(nomeArq, "ab+");

        salvarFuncionarios(funcAuxiliar, arqParticao);

        fclose(arqParticao);

    }
}

void imprimirParticao(int part){
    char nomeArq[100], nome1[100] , nome2[100] = ".dat";
    itoa(part, nome1, 10);
    strcat(strcpy(nomeArq, "tblHash"), nome1);
    strcat(strcpy(nomeArq, nomeArq), nome2);

    FILE *arqParticao = fopen(nomeArq, "rb+");

    imprimirParticaoFunc(arqParticao, nomeArq);

    fclose(arqParticao);

}

TFunc *buscaSequencialHash(int cod, FILE *arq, int *qtdComparacoes) {
    int posicao = 0;

    while (!feof(arq)) {

        fseek(arq, posicao * sizeof(TFunc), SEEK_SET) ;
        TFunc *func = lerFuncionario(arq);

        posicao++;

        if (func == NULL) {
            *qtdComparacoes += 1;
            return NULL;
        } else if (cod == func->cod) {
            *qtdComparacoes += 1;
            return func;
        } else {
            *qtdComparacoes += 1;
        }

    }

    return NULL;
}

TFunc *busca(int cod, int codParticao) {

    char nomeArq[100], nome1[100], nome2[100] = ".dat";
    int qtdComparacoes;

    itoa(codParticao, nome1, 10);
    strcat(strcpy(nomeArq, "tblHash"), nome1);
    strcat(strcpy(nomeArq, nomeArq), nome2);


    FILE *arqParticao = fopen(nomeArq, "rb+");

    TFunc *funcAuxiliar = buscaSequencialHash(cod, arqParticao, &qtdComparacoes);

    fclose(arqParticao);

    return funcAuxiliar;
}

void remover(int cod, int codParticao) {
    int totalCompararisons = 0;
    char nomeArq[100], nome1[100], nome2[100] = ".dat";


    itoa(codParticao, nome1, 10);
    strcat(strcpy(nomeArq, "tblHash"), nome1);
    strcat(strcpy(nomeArq, nomeArq), nome2);

    FILE *arqParticao = fopen(nomeArq, "r+b");
    TFunc *funcAuxiliar = buscaSequencialHash(cod, arqParticao, &totalCompararisons);

    if (funcAuxiliar != NULL) {
        fseek(arqParticao, (totalCompararisons - 1) * sizeof(TFunc), SEEK_SET);
        TFunc funcRemover;

        funcRemover.cod = 101;
        sprintf(funcRemover.nome, "%s", funcAuxiliar->nome);
        sprintf(funcRemover.cpf, "%s", funcAuxiliar->cpf);
        sprintf(funcRemover.data_nascimento, "%s", funcAuxiliar->data_nascimento);

        salvarFuncionarios(&funcRemover, arqParticao);

        printf("\n<<<<<Funcionario removido!>>>>>");
    } else {
        printf("\n<<<<<Funcionario nao encontrado!>>>>>");
    }

    fclose(arqParticao);
}

void inserir(TFunc *func, int codParticao) {
    int qtdComp = 0, qtdCompD = 0, tamArq = 0;
    char nomeArq[100], nome1[100], nome2[100] = ".dat";

    itoa(codParticao, nome1, 10);
    strcat(strcpy(nomeArq, "tblHash"), nome1);
    strcat(strcpy(nomeArq, nomeArq), nome2);

    FILE *arqParticao = fopen(nomeArq, "r+b");

    tamArq = tamanhoArquivo(arqParticao, 0);
    rewind(arqParticao);
    TFunc *funcAuxiliar = buscaSequencialHash(func->cod, arqParticao, &qtdComp);
    rewind(arqParticao);
    TFunc *funcAuxiliarD = buscaSequencialHash(101, arqParticao, &qtdCompD);
    rewind(arqParticao);

    if (funcAuxiliar == NULL && funcAuxiliarD == NULL) {
        fseek(arqParticao, (tamArq) * sizeof(TFunc), SEEK_SET);\
        salvarFuncionarios(func, arqParticao);
        printf("\n<<<<<Funcionario adicionado!>>>>>");
    } else if (funcAuxiliar == NULL && funcAuxiliarD != NULL) {
        fseek(arqParticao, (qtdCompD - 1) * sizeof(TFunc), SEEK_SET);\
        salvarFuncionarios(func, arqParticao);
        printf("\n<<<<<Funcionario adicionado!>>>>>");
    } else {
        printf("\n<<<<<Funcionario ja existe!>>>>>");

    }

    fclose(arqParticao);
}


