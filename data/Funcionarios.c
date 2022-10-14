#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "Funcionarios.h"


void salvarFuncionarios(TFunc *func, FILE *arq) {
    fwrite(&func->cod, sizeof(int), 1, arq);
    fwrite(&func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(&func->cpf, sizeof(char), sizeof(func->cpf), arq);
    fwrite(&func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
    fwrite(&func->salario, sizeof(double), 1, arq);
}

TFunc *lerFuncionario(FILE *arq) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));

    if (0 >= fread(&func->cod, sizeof(int), 1, arq)) {
        free(func);
        return NULL;
    }

    fread(&func->nome, sizeof(char), sizeof(func->nome), arq);
    fread(&func->cpf, sizeof(char), sizeof(func->cpf), arq);
    fread(&func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), arq);
    fread(&func->salario, sizeof(double), 1, arq);

    return func;
}

void preencherFuncionarios(FILE *arq, int size) {
    TFunc funcionarios[size];
    int cods[size], i = 0, igual;
    srand(time(NULL));
    do {
        cods[i] = rand() %size;
        igual = 0;
        for (int j = 0; j < i; ++j) {
            if(cods[j] == cods[i]){
                igual = 1;
            }
        }
        if(igual == 0){
            i++;
        }

    } while (i < size);


    for (int i = 0; i < size; ++i) {

        funcionarios[i].cod = cods[i];
        sprintf(funcionarios[i].nome, "%d", cods[i]);
        sprintf(funcionarios[i].cpf, "%d", cods[i]);
        sprintf(funcionarios[i].data_nascimento, "%d", cods[i]);
        funcionarios[i].salario = cods[i];

        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        salvarFuncionarios(&funcionarios[i], arq);
    }

}

int tamanhoArquivo(FILE *arq, int contSizeFile) {
    int i = 0;
    while(!feof(arq)) {
        fseek(arq, i * sizeof(TFunc), SEEK_SET);
        TFunc *aux = lerFuncionario(arq);
        if(aux != NULL) {
            contSizeFile++;
        }
        i++;
    }
    return contSizeFile;
}

void imprimirParticao(FILE *file, char partitionName[]) {

    printf("\nParticao %s: \n: ", partitionName);

    for (int i = 0; i < tamanhoArquivo(file, 0); ++i) {

        fseek(file, i * sizeof(TFunc), SEEK_SET) ;
        TFunc *aux = lerFuncionario(file);

        printf(" %i ", aux->cod);
    }

    printf("\n");
}

void imprimir(TFunc func) {
    printf("\n COD: %d", func.cod);
    printf("\n NOME: %s", func.nome);
    printf("\n CPF: %s", func.cpf);
    printf("\n DTA. NASC.: %s", func.data_nascimento);
    printf("\n SALARIO: %f", func.salario);
}