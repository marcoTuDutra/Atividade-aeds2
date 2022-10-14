#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include "../data/Funcionarios.h"

void arvoreVenc(TFunc **func, FILE *arq, int tam, int *arvoreAux) {
    int aux;

    for (int i = tam - 1; i > 0; i--){

        if (i % 2 != 0 && i == tam - 1){
            aux = (i - 1) / 2;
            *func[aux] = *func[i];
        }
        else{
            if (i % 2 == 0 && func[i]->cod < func[i-1]->cod){
                aux = (i - 2) / 2;
                *func[aux] = *func[i];
            }
            else if (i % 2 == 0 && func[i-1]->cod < func[i]->cod){
                aux = (i - 2) / 2;
                *func[aux] = *func[i - 1];
            }
        }
    }

    salvarFuncionarios(func[0], arq);
    *arvoreAux +=1;
}

void arvoreBinariaVenc(int qtdParticoes, float *tempoExecucao){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);


    int auxQtdParticoes = qtdParticoes;
    int flagAuxFinal = 0;
    int arvoreAux = 0;
    int tam;

    if (qtdParticoes % 2 == 0){
        tam = 2 * qtdParticoes - 1;
        auxQtdParticoes--;
    }
    else {
        tam = 2 * qtdParticoes;
    }

    int aux = tam - 1;

    TVetFile *auxArq = calloc(sizeof(*auxArq), qtdParticoes);
    TFunc *menor = calloc(sizeof(*menor), 1);
    TFunc **funcAux = calloc(sizeof(**funcAux), tam);

    for (int i = 0; i < auxQtdParticoes; i++){
        funcAux[i] = calloc(sizeof(TFunc), 1);
    }

    FILE *arvoreBinaria = fopen("arvoreBinaria.dat", "wb+");

    for (int i = 0; i < qtdParticoes; i++){
        auxArq[i].init_p = 0;

        char nomeParticao[100];
        char nome1[50];
        char nome2[50] = ".dat";

        itoa(i, nome1, 10);
        strcat(strcpy(nomeParticao, "slcNat"), nome1);
        strcat(strcpy(nomeParticao, nomeParticao), nome2);

        auxArq[i].filePartition = fopen (nomeParticao, "rb+");
        fseek(auxArq[i].filePartition, 0 * sizeof(TFunc), SEEK_SET);

        if (aux+1 >= qtdParticoes){
            funcAux[aux] = lerFuncionario(auxArq[i].filePartition);
            aux--;
        }
        auxArq[i].end_p = 0;
    }

    arvoreVenc(funcAux, arvoreBinaria, tam, &arvoreAux);

    while (flagAuxFinal < qtdParticoes){
        aux = tam - 1;

        for (int i = 0; i < qtdParticoes; i++){

            if (fgetc(auxArq[i].filePartition) == EOF && auxArq[i].end_p == 0 && menor->cod == funcAux[aux]->cod){
                flagAuxFinal++;
                auxArq[i].end_p = 1;
                i--;

                if (flagAuxFinal == qtdParticoes) {
                    break;
                }

                for (int j = 0; j < tam; j++){
                    if (funcAux[j]->cod == menor->cod) funcAux[j]->cod = 15000;
                }

                arvoreVenc(funcAux, arvoreBinaria, tam, &arvoreAux);
            } else {
                *menor = *funcAux[0];

                if (menor->cod == funcAux[aux]->cod && auxArq[i].end_p == 0){
                    auxArq[i].init_p += 1;

                    if (fgetc(auxArq[i].filePartition) != EOF){
                        fseek (auxArq[i].filePartition, auxArq[i].init_p * sizeof(TFunc), SEEK_SET);
                        free(funcAux[aux]);
                        funcAux[aux] = lerFuncionario(auxArq[i].filePartition);
                        arvoreVenc(funcAux, arvoreBinaria, tam, &arvoreAux);
                    }
                }
                aux--;
            }
        }
    }

    for (int i = 0; i < qtdParticoes; i++) {
        fclose(auxArq[i].filePartition);
    }

    for (int i = 0; i < tam; i++){
        free(funcAux[i]);
    }

    free(funcAux);
    free(menor);
    free(auxArq);
    fclose(arvoreBinaria);
    *tempoExecucao = current_time.tv_usec;
}

