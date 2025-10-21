#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/include.h"

int main(int argc, char const *argv[])
{
    char nomeArquivos[50];
    int tmp, leituraarq;
    float *vetAux;
    //Enquanto eu nao gerar os 5 relatorios
    while (arquivos < 5)                                                               
    {
        contChamadas=0;
        leituraarq=2;
        sprintf(nomeArquivos, "../../saidas/relatorio%d.csv", arquivos + 1);
        FILE *criarArquivoCsv = fopen(nomeArquivos, "w");
        //Leio a quantidade de entradas
        for (int j = 0; j < 14; j++)
        {
            char converter[50];
            leituraarq *= 2;
            sprintf(converter, "../../entradas/alunos_%d.csv", leituraarq);
            FILE *leituraArqCsv = fopen(converter, "r");
            tmp = alocAluno(leituraArqCsv);
            vetAux = (float *)malloc(tmp * sizeof(float));
            TempoDeProcessamento(tmp, &vetAux, criarArquivoCsv, leituraArqCsv);
            fclose(leituraArqCsv);
            free(vetAux);
        } // Le todos os .csv em uma execução, e libera a memoria utilizada
        arquivos++;
        fclose(criarArquivoCsv);
    }

    //Gero um relatório da media de cada entrada dos 5 relatorios de tempo de execução gerados
    MediaAlgoritmos();
    system("start ../../Graficos/graficoTempo.pyw");
    return 0;
}
