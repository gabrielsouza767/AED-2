#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    float *notas;
    int num_notas;
} Aluno;

int alocAluno(FILE *fp)
{
    char buffer[256];
    int tmp = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (buffer[strlen(buffer) - 1] == '\n' || feof(fp))
            tmp++;
    }
    return tmp;
}

void exemplo_leitura_linha(FILE *fp, int tmp)
{
    char linha[256],linha2[256];
    rewind(fp);
    FILE *arquivo = fopen("../../relatorio.txt", "w");
    Aluno **alunos = (Aluno **)malloc(tmp * sizeof(Aluno *));
    for (int i = 0; i < tmp; i++)
        alunos[i] = (Aluno *)malloc(sizeof(Aluno));

    int i = 0;
    // Tenta ler uma linha do arquivo. Se for bem-sucedido...
    while (fgets(linha, sizeof(linha), fp) != NULL)
    {
        strcpy(linha2, linha);
        char *token;
        // Primeiro, tokeniza a linha usando a vírgula como delimitador
        token = strtok(linha, ",");
        if (token !=NULL)
            strcpy(alunos[i]->nome, token); // Copia o 1 token, no caso o nome para o campo nome da struct do aluno
        
        int notas = 0;
        float res = 0.0;
        char *temp = strtok(NULL, ","); // Pega a primeira nota, 2 token
        while (temp != NULL)            // Caso houver uma nota, != NULL
        {
            notas++;                  // computa a nota
            temp = strtok(NULL, ","); // Pega o proximo token, nota
        }
        alunos[i]->notas=(float*)malloc(notas * sizeof(float));
        alunos[i]->num_notas = notas;
        // Pega o proximo token
       strtok(linha2, ",");
        for (int j = 0; j < notas; j++)
        {
            token = strtok(NULL, ",");
            alunos[i]->notas[j] = atof(token);
            res += alunos[i]->notas[j];
        }
        fprintf(arquivo,"Nome do aluno: %s , ",alunos[i]->nome);
        for (int k = 0; k < notas; k++)
            fprintf(arquivo,"nota %d : %.2f ",k +1 ,alunos[i]->notas[k]);
        fprintf(arquivo," e media do aluno: %.2f \n",res / alunos[i]->num_notas);
        
        i++;
    }
    fclose(arquivo);
    for (int i = 0; i < tmp; i++)
    {
        free(alunos[i]->notas);
        free(alunos[i]);
    }
    free(alunos);
}
