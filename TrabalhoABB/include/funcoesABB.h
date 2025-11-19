#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct pessoa
{
    int idade;
    float altura;
    char nome[50];
} Pessoa;

typedef struct no
{
    Pessoa dado;
    struct no *esq, *dir;
} No;

typedef struct abb
{
    struct no *raiz;
} ABB;

int QuantPessoas(FILE *fp)
{
    char letras[100];
    int cont = 0;
    while (fgets(letras, 100, fp) != NULL)
        cont++;
    rewind(fp);
    return cont;
}
void LeArquivo(FILE *fp, Pessoa *p)
{
    char ler[100], recebe[20];
    int k = 0;
    while (fgets(ler, sizeof(ler), fp) != NULL)
    {
        int count = 0, i = 0;
        while (ler[count] != ',')
        {
            recebe[count] = ler[count];
            count++;
        }
        recebe[count] = '\0';
        strcpy(p[k].nome, recebe);
        count++;
        while (ler[count] != ',')
        {
            recebe[i] = ler[count];
            count++;
            i++;
        }
        recebe[i] = '\0';
        p[k].altura = atof(recebe);
        count++;
        for (int i = 0; i < 2; i++)
        {
            recebe[i] = ler[count];
            count++;
        }
        i = 2;
        recebe[i] = '\0';
        p[k].idade = atoi(recebe);
        k++;
    }
}

No *criaNo(Pessoa dado)
{
    No *elemento = (No *)malloc(sizeof(No));
    if (elemento == NULL)
    {
        printf("Deu errado a alocação, encerrando o programa...\n");
        exit(1);
    }
    elemento->dado = dado;
    elemento->dir = NULL;
    elemento->esq = NULL;
    // Inicializo os ponteiros do novo nó com NULL
    return elemento;
}

No *inserirABB(No *raiz, Pessoa dado)
{
    // Caso base
    if (raiz == NULL)
        return criaNo(dado);

    if (dado.idade < raiz->dado.idade)
        raiz->esq = inserirABB(raiz->esq, dado); // Insiro na esquerda caso a idade da pessoa seja menor

    if (dado.idade > raiz->dado.idade)
        raiz->dir = inserirABB(raiz->dir, dado); // Insiro na direita caso a idade da pessoa seja maior

    return raiz;
}
void comecaArvore(ABB *tree, Pessoa dado)
{
    tree->raiz = inserirABB(tree->raiz, dado);
}

No *buscaABB(No *raiz, Pessoa dado)
{
    // Casos base da minha recursao

    if (raiz->dado.idade == dado.idade)
        return raiz;
    if (raiz == NULL)
        return NULL;

    if (dado.idade < raiz->dado.idade) // Caso a idade da pessoa que busco seja menor do que a idade da pessoa que estou
        return buscaABB(raiz->esq, dado);

    if (dado.idade > raiz->dado.idade) // Caso a idade da pessoa que busco seja maior do que a idade da pessoa que estou
        return buscaABB(raiz->dir, dado);
}