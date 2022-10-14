//
// Created by marco on 14/10/2022.
//

#ifndef PROVA01_BUSCA_H
#define PROVA01_BUSCA_H

TFunc *buscaSequencial(int cod, FILE *arq, int size, int *qtdComparacoes, float *tempoExecucao);
TFunc *buscaBinaria(int cod, FILE *arq, int size, int *qtdComparacoes, float *tempoExecucao);

#endif //PROVA01_BUSCA_H
