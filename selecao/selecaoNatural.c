#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../data/Funcionarios.h"
#include "Selecao.h"


int selecaoNatural(FILE *arq) {

    int  tamArq = tamanhoArquivo(arq, 0);
    int pos = 0;
    int qtdParticao = 0;
    int menor = 10000000;
    int posMenor = 0;
    int tamReservoir = 0;
    int opc = 0;

    TFunc func[6];

    int auxFuncVet[6] = {0, 0, 0, 0, 0, 0};

    rewind(arq);

    while (!feof(arq)) {

        FILE *fileReservoir = fopen("reservoir.dat", "wb+");

        char partitionName[100];
        char nome1[100];
        char nome2[100] = ".dat";

        itoa(qtdParticao, nome1, 10);
        strcat(strcpy(partitionName, "slcNat"), nome1);
        strcat(strcpy(partitionName, partitionName), nome2);

        FILE *arqParticao = fopen(partitionName, "wb+");

        if (opc == 0) {
            for (int i = 0; i < 6; ++i) {

                TFunc *auxFunc = lerFuncionario(arq);
                pos++;

                func[i] = *auxFunc;
                auxFuncVet[i] = auxFunc->cod;
            }
        }

        while (!feof(arq)) {

            for (int i = 0; i < 6; ++i) {

                if (auxFuncVet[i] < menor) {
                    menor = auxFuncVet[i];
                    posMenor = i;
                }
            }

            TFunc *auxFunc = lerFuncionario(arq);
            pos++;
            if (auxFunc->cod < func[posMenor].cod) {
                salvarFuncionarios(auxFunc, fileReservoir);
                tamReservoir++;

                if (tamReservoir == 6) {

                    break;
                }

            } else {
                salvarFuncionarios(&func[posMenor], arqParticao);
                auxFuncVet[posMenor] = auxFunc->cod;
                func[posMenor] = *auxFunc;
            }

            menor = 999999999;

            if (pos >= tamArq) {
                break;
            }

        }

        TFunc aux;

        int k, j;

        for (k = 1; k < 6; k++) {

            for (j = 0; j < 6 - 1; j++) {

                if (func[j].cod> func[j + 1].cod) {
                    aux = func[j];
                    func[j] = func[j + 1];
                    func[j + 1] = aux;
                }
            }
        }

        for (int i = 0; i < 6; ++i) {
            salvarFuncionarios(&func[i], arqParticao);
        }

        rewind(fileReservoir);

        for (int i = 0; i < tamReservoir; ++i) {
            TFunc *auxFuncReservoir = lerFuncionario(fileReservoir);
            func[i] = *auxFuncReservoir;
            auxFuncVet[i] = auxFuncReservoir->cod;
            opc = 1;
        }


        fclose(fileReservoir);
        fclose(arqParticao);

        if (pos >= tamArq) {
            break;
        }

        tamReservoir = 0;
        qtdParticao++;

    }

    for (int i = 0; i <= qtdParticao; ++i) {

        char partitionName[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(partitionName, "slcNat"), str1);
        strcat(strcpy(partitionName, partitionName), str2);

        FILE *arqParticao = fopen(partitionName, "rb+");
        fclose(arqParticao);
    }

    return qtdParticao;
}
