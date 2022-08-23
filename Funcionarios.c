#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "Funcionarios.h"

void embaralhar(TFunc *vet, int vetSize) {
    for (int i = 0; i < vetSize; i++) {
        int r = rand() % vetSize;

        TFunc temp = vet[i];
        vet[i] = vet[r];
        vet[r] = temp;
    }
}

void preencherFuncionarios(TFunc *funcionarios, int size) {
    for (int i = 0; i < size; ++i) {
        funcionarios[i].cod = i;
        printf("");
        sprintf(funcionarios[i].nome, "%d", i);
        sprintf(funcionarios[i].cpf, "%d", i);
        sprintf(funcionarios[i].data_nascimento, "%d", i);
        funcionarios[i].salario = i;
    }
    //embaralhar(funcionarios, MAX);
}

void salvarFuncionarios(TFunc vet[], int size) {
    FILE *arq = fopen("funcionarios.bin", "wb");

    if (arq != NULL) {
        for (int i = 0; i < size; ++i) {
            fwrite(&vet[i], sizeof(TFunc), 1, arq);
        }
        fclose(arq);
    }
}

TFunc buscaSequencial(int cod, TFunc funcionarios[], int size) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int contComparacoes = 0, achou = 0;
    TFunc funcionario;


    for (int i = 0; i < size; ++i) {
        contComparacoes++;
        if (cod == funcionarios[i].cod) {
            funcionario = funcionarios[i];
            achou = 1;
            break;
        }
    }

    if (achou == 1) {
        printf("\nFuncionario encontrado!");
    } else {
        printf("\nFuncionario nao encontrado!");
    }
    printf("\nQuantidade de comparacoes: %d", contComparacoes);
    printf("\nTempo de execucao em microsegundos : %ld", current_time.tv_usec);

    return funcionario;
}

TFunc buscaBinaria(int cod, TFunc funcionarios[], int size) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int inicio = 0, fim = size - 1, meio, controle_pesquisa = 1, contComparacoes = 0;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        contComparacoes++;
        if (cod == funcionarios[meio].cod) {
            controle_pesquisa = 0;
            break;
        }
        contComparacoes++;
        if (cod < funcionarios[meio].cod) {
            fim = meio - 1;
            continue;
        }
        contComparacoes++;
        if (cod > funcionarios[meio].cod) {
            inicio = meio + 1;
            continue;
        } else {
            controle_pesquisa = 1;
            break;
        }

    }

    if (controle_pesquisa == 0) {
        printf("\nFuncionario encontrado!");
        printf("\nQuantidade de comparacoes: %d", contComparacoes);
        printf("\nTempo de execucao em microsegundos : %ld", current_time.tv_usec);
        return funcionarios[meio];
    } else {
        printf("\nFuncionario nao encontrado!");
        printf("\nQuantidade de comparacoes: %d", contComparacoes);
        printf("\nTempo de execucao em microsegundos : %ld", current_time.tv_usec);
    }
}

void keySorting(TFunc *funcionarios) {

}