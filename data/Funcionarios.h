

#ifndef PROVA01_FUNCIONARIOS_H
#define PROVA01_FUNCIONARIOS_H

typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

typedef struct File{
    TFunc *func;
    long init_p;
    long end_p;
    FILE *filePartition;
}TVetFile;

void preencherFuncionarios(FILE *arq, int size);
TFunc *lerFuncionario(FILE *arq);
void salvarFuncionarios(TFunc *func, FILE *arq);
void imprimir(TFunc func);
int tamanhoArquivo(FILE *arq, int contSizeFile);
#endif //PROVA01_FUNCIONARIOS_H
