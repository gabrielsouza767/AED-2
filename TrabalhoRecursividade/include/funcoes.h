#include <stdio.h>
#include <stdlib.h>

/**
 * @param labirinto o endereço de uma matriz, por malloc ("vetor de ponteiros")
 * @brief Aloco uma matriz dinamicamente, variando o tamanho de acordo com a quantidade de linhas e colunas
 * descritas na primeira linha dos arquivos de texto.
 * Leio os valores da matriz nos arquivos e os aloco
 */
void scanMatriz(FILE *fp, int ***labirinto, int linha, int coluna)
{

    *labirinto = (int **)malloc(linha * sizeof(int *));
    for (int i = 0; i < linha; i++)
        (*labirinto)[i] = (int *)malloc(coluna * sizeof(int));
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
            fscanf(fp, "%d ", &((*labirinto)[i][j]));
    }
}
void printMatriz(int **labirinto, int linha, int coluna)
{
    for (int i = 0; i < linha; i++)
    {

        for (int j = 0; j < coluna; j++)
            printf("%d ", labirinto[i][j]);
        printf("\n");
    }
}

/**
 * @brief Esta função de back tracking verifica se o "vizinho" é 0 ou 1, se for 0 pode avançar, se nao for 0
 * testa outra casa, tanto na horizontal, tanto na vertical,voltando ou avançando, e sempre respeitando os limites da matriz
 * "Avance se o vizinho horizontal for 0, se nao for, avance na vertical, se nao for, retorne uma casa na horizontal
 * se nao for, retorna uma casa na vertical, e se nao achou uma saida, volte o valor anterior na casa"
 */
int lab(int linha, int coluna, int i, int j, int **labirinto)
{
    labirinto[i][j] = 2;

    if (i == linha - 1 && j == coluna - 1)
        return 1; // achou a saída

    // anda em todas as direções
    if (j + 1 < coluna && labirinto[i][j + 1] == 0 && lab(linha, coluna, i, j + 1, labirinto))
        return 1;
    if (i + 1 < linha && labirinto[i + 1][j] == 0 && lab(linha, coluna, i + 1, j, labirinto))
        return 1;
    if (j - 1 >= 0 && labirinto[i][j - 1] == 0 && lab(linha, coluna, i, j - 1, labirinto))
        return 1;
    if (i - 1 >= 0 && labirinto[i - 1][j] == 0 && lab(linha, coluna, i - 1, j, labirinto))
        return 1;

    // se nao achar a saída, desfaz (backtrack)
    labirinto[i][j] = 0;

    return 0;
}
