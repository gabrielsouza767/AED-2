#include <stdio.h>
#include <stdlib.h>
#include "../include/funcoes.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Arquivo nao encontrado\n");
        exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Arquivo nao existe\n");
        exit(1);
    }
    int linha, coluna;
    int i = 0, j = 0;
    fscanf(fp, "%d %d", &linha, &coluna);
    int **labirinto;
    scanMatriz(fp, &labirinto, linha, coluna);
    lab(linha, coluna, i, j, labirinto);
    printMatriz(labirinto, linha, coluna);
    for (int i = 0; i < linha; i++)
        free(labirinto[i]);
    free(labirinto);

    fclose(fp);
    return 0;
}
