#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
typedef struct
{
    char nome[50];
    float *notas;
    float mediaAlunos;
    int num_notas;
} Aluno;
int arquivos = 0, contChamadas = 0;
double media[5][14], mediadoQuick[5][14], mediadoMerge[5][14];
int alocAluno(FILE *fp)
{
    char buffer[256];
    int tmp = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        tmp++;
    }
    return tmp;
}

void BubbleSort(Aluno ***alunos, int quantAlunos)
{
    float aux;
    for (int i = 1; i < quantAlunos; i++)
    {
        for (int j = 0; j < quantAlunos - i; j++)
        {
            if ((*alunos)[j]->mediaAlunos < (*alunos)[j + 1]->mediaAlunos)
            {
                aux = (*alunos)[j]->mediaAlunos;
                (*alunos)[j]->mediaAlunos = (*alunos)[j + 1]->mediaAlunos;
                (*alunos)[j + 1]->mediaAlunos = aux;
                Sleep(0.4);
            }
        }
    }
}

/**
 * @brief Esta função é chamada no TempodeProcessamento, que é chamado com novos parametros a cada interação la no main
 * ou seja, ela ficara alterando os valores,
 */
void leituraLinhasCsv(FILE *ArqsCsv, Aluno ***vetorAlunos, int quantAlunos)
{
    char linha[256], linha2[256];
    rewind(ArqsCsv);
    int i = 0;
    // Tenta ler uma linha do arquivo. Se for bem-sucedido...
    while (fgets(linha, sizeof(linha), ArqsCsv) != NULL)
    {
        strcpy(linha2, linha);
        char *token;
        // Primeiro, tokeniza a linha usando a vírgula como delimitador
        token = strtok(linha, ",");
        if (token != NULL)
            strcpy((*vetorAlunos)[i]->nome, token); // Copia o 1 token, no caso o nome para o campo nome da struct do aluno

        int notas = 0;
        float res = 0.0;
        char *temp = strtok(NULL, ","); // Pega a primeira nota, 2 token
        while (temp != NULL)            // Caso houver uma nota, != NULL
        {
            notas++;                  // computa a nota
            temp = strtok(NULL, ","); // Pega o proximo token, nota
        }
        (*vetorAlunos)[i]->notas = (float *)malloc(notas * sizeof(float));
        (*vetorAlunos)[i]->num_notas = notas;
        // Pega o proximo token
        strtok(linha2, ",");
        for (int j = 0; j < notas; j++)
        {
            token = strtok(NULL, ",");
            (*vetorAlunos)[i]->notas[j] = atof(token);
            res += (*vetorAlunos)[i]->notas[j];
        }
        (*vetorAlunos)[i]->mediaAlunos = res / (*vetorAlunos)[i]->num_notas;
        i++;
    }
    for (int i = 0; i < quantAlunos; i++)
        free((*vetorAlunos)[i]->notas);
}

void QuickSort(Aluno ***alunos, int inicio, int fim)
{
    int pivo = (inicio + fim) / 2, esquerda = inicio, direita = fim;
    float aux;
    while (esquerda <= direita)
    {
        while ((*alunos)[esquerda]->mediaAlunos > (*alunos)[pivo]->mediaAlunos)
            esquerda++;
        while ((*alunos)[direita]->mediaAlunos < (*alunos)[pivo]->mediaAlunos)
            direita--;
        if (esquerda <= direita)
        {
            aux = (*alunos)[esquerda]->mediaAlunos;
            (*alunos)[esquerda]->mediaAlunos = (*alunos)[direita]->mediaAlunos;
            (*alunos)[direita]->mediaAlunos = aux;
            Sleep(0.4);
            esquerda++;
            direita--;
        }
    }
    // SubVetor 1
    if (esquerda < fim)
        QuickSort(alunos, esquerda, fim);

    // SubVetor2
    if (inicio < direita)
        QuickSort(alunos, inicio, direita);
}

void merge(Aluno ***vetorAlunos, int inicio, int meio, int fim)
{
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Vetores temporários
    float *esq = (float *)malloc(n1 * sizeof(float));
    float *dir = (float *)malloc(n2 * sizeof(float));

    // Copia os elementos para os vetores auxiliares
    for (int i = 0; i < n1; i++)
        esq[i] = (*vetorAlunos)[inicio + i]->mediaAlunos;
    for (int j = 0; j < n2; j++)
        dir[j] = (*vetorAlunos)[meio + 1 + j]->mediaAlunos;

    int i = 0, j = 0, k = inicio;

    // Intercala de volta no vetor original
    while (i < n1 && j < n2)
    {
        if (esq[i] <= dir[j])
        {
            (*vetorAlunos)[k]->mediaAlunos = esq[i];
            i++;
        }
        else
        {
            (*vetorAlunos)[k]->mediaAlunos = dir[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes (se houver)
    while (i < n1)
    {
        (*vetorAlunos)[k]->mediaAlunos = esq[i];
        Sleep(0.4);
        i++;
        k++;
    }

    while (j < n2)
    {
        (*vetorAlunos)[k]->mediaAlunos = dir[j];
        Sleep(0.4);
        j++;
        k++;
    }

    // Libera memória
    free(esq);
    free(dir);
}

// Função recursiva do Merge Sort
void mergeSort(Aluno ***vetorAlunos, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = inicio + (fim - inicio) / 2;

        // Ordena a primeira e segunda metade
        mergeSort(vetorAlunos, inicio, meio);
        mergeSort(vetorAlunos, meio + 1, fim);

        // Intercala as duas metades
        merge(vetorAlunos, inicio, meio, fim);
    }
}

void TempoDeProcessamento(int quantAlunos, float **vetorAux, FILE *criarAruivoCsv, FILE *lerArquivosCsv)
{
    double tempo[3];
    clock_t inicio;
    clock_t fim;
    Aluno **vetorAlunos = (Aluno **)malloc(quantAlunos * sizeof(Aluno *));
    for (int i = 0; i < quantAlunos; i++)
        vetorAlunos[i] = (Aluno *)malloc(sizeof(Aluno));

    leituraLinhasCsv(lerArquivosCsv, &vetorAlunos, quantAlunos); // Leitura das medias

    for (int i = 0; i < quantAlunos; i++)
        (*vetorAux)[i] = vetorAlunos[i]->mediaAlunos;

    // Para desordenar o vetor, para que no proximo arquivo maior,o vetor esteja desordenado

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < quantAlunos; j++)
            vetorAlunos[j]->mediaAlunos = (*vetorAux)[j]; // Desordenar para o proximo alg

        switch (i)
        {
        case 0:
            inicio = clock();

            BubbleSort(&vetorAlunos, quantAlunos);

            fim = clock();

            tempo[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
            media[arquivos][contChamadas] = tempo[i];
            break;
        case 1:
            inicio = clock();

            QuickSort(&vetorAlunos, 0, quantAlunos - 1);

            fim = clock();

            tempo[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
            mediadoQuick[arquivos][contChamadas] = tempo[i];
            break;
        default:
            inicio = clock();

            mergeSort(&vetorAlunos, 0, quantAlunos - 1);
            fim = clock();

            tempo[i] = (double)(fim - inicio) / CLOCKS_PER_SEC;
            mediadoMerge[arquivos][contChamadas] = tempo[i];
            break;
        }
    }
    fprintf(criarAruivoCsv, "Tamanho dos dados: %d , tempo do QuickSort: %.20f , tempo do MergeSort: %.20f , tempo do BubbleSort: %.20f \n",
            quantAlunos, tempo[1], tempo[2], tempo[0]);
    contChamadas++;
    for (int i = 0; i < quantAlunos; i++)
        free(vetorAlunos[i]);
    free(vetorAlunos); // Libera a memoria a cada chamada da função, lendo e escrevendo 1 linha para cada .csv e liberando a memoria
}
/**
 * @brief Transformei os dados dos 5 relatorios cada um com 11 entradas em uma matriz, onde as linhas correspondem a cada relatório, e as colunas
 * as entradas. Somo a entrada de todos os arquivos mantendo o indice da entrada porém mudando o indice de cada arquivo,
 * ou seja, tenho o tempo de cada entrada em cada arquivo somados.
 */
void MediaAlgoritmos()
{
    double mediaFinal[14], mediaFinal2[14], mediaFinal3[14];
    int i = 0, entrada = 2;
    FILE *arquivoGrafico = fopen("../../Graficos/medias.txt", "w");

    for (int i = 0; i < 14; i++)
    {
        mediaFinal[i] = 0;  // Tira o lixo de memoria
        mediaFinal2[i] = 0; // Tira o lixo de memoria
        mediaFinal3[i] = 0; // Tira o lixo de memoria
    }

    for (int j = 0; j < 14; j++)
    {
        while (i < 5)
        {
            mediaFinal[j] += (media[i][j] + media[i + 1][j]);                // Mantenho a entrada, altero o relatorio
            mediaFinal2[j] += (mediadoQuick[i][j] + mediadoQuick[i + 1][j]); // Mantenho a entrada, altero o relatorio
            mediaFinal3[j] += (mediadoMerge[i][j] + mediadoMerge[i + 1][j]); // Mantenho a entrada, altero o relatorio
            i += 2;
        }
        i = 0;
    }
    for (int i = 0; i < 14; i++)
    {
        entrada *= 2;
        mediaFinal[i] /= 5;
        fprintf(arquivoGrafico, "%d %.10f \n", entrada, mediaFinal[i]); // Media de cada entrada do algoritmo no geral
    }
    fprintf(arquivoGrafico, "\n\n");
    entrada = 2;
    for (int i = 0; i < 14; i++)
    {
        entrada *= 2;
        mediaFinal2[i] /= 5;
        fprintf(arquivoGrafico, "%d %.10f \n", entrada, mediaFinal2[i]); // Media de cada entrada do algoritmo no geral
    }
    fprintf(arquivoGrafico, "\n\n");
    entrada = 2;
    for (int i = 0; i < 14; i++)
    {
        entrada *= 2;
        mediaFinal3[i] /= 5;
        fprintf(arquivoGrafico, "%d %.10f \n", entrada, mediaFinal3[i]); // Media de cada entrada do algoritmo no geral
    }

    fclose(arquivoGrafico);
}
