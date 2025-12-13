#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABELA 100

typedef struct no
{
    char nome[20];
    struct no *prox;
} No;

/**
 * @param nome é o nome
 * @brief Transformando minha chave (nome) em meu indice do vetor
 */
unsigned int funcaoHash(char nome[])
{
    int indice = 0;
    for (int i = 0; nome[i] != '\0'; i++)
        indice += (int)nome[i];
    indice = indice % TAM_TABELA;
    return indice;
}
/**
 * @param tabela é minha Hash table, um vetor de ponteiros
 * @param nome é o nome que vou inserir na minha hash table, minha chave
 * @brief Esta função eu aloco um nó para minha chave, e coloco esse no em minha hash table, e verifico se o proximo elemento caiu em um lugar 
 * preenchido, criando uma lista encadeada, para que mesmo que com colisao, eu armazene todas as chaves
*/
void tratamentoColisao(No *tabela[], char *nome)
{
    int indice = funcaoHash(nome);
    No *elemento = (No*)malloc(sizeof(No)); //Faço isso para mim poder lidar com a colisao tambem, armazeno o nome do carro
    strcpy(elemento->nome,nome);
    tabela[indice] = elemento;
    if (tabela[indice] != NULL) //Colisao
    {
        elemento->prox = tabela[indice];    //Trato como inseercao em uma lista
        tabela[indice] = elemento;
    }
}