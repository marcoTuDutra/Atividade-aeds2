

#ifndef PROVA01_HASH_H
#define PROVA01_HASH_H


void gerarParicoesHash(FILE *arq, int qtdParticoes, int tam);
void imprimirParticao(int part);
TFunc *busca(int cod, int codParticao);
void remover(int cod, int codParticao);
void inserir(TFunc *func, int codParticao);

#endif //PROVA01_HASH_H
