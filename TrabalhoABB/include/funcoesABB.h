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

    if (dado.idade >= raiz->dado.idade)
        raiz->dir = inserirABB(raiz->dir, dado); // Insiro na direita caso a idade da pessoa seja maior

    return raiz; // Crucial para a função comecaArvore
}
void comecaArvore(ABB *tree, Pessoa dado)
{
    tree->raiz = inserirABB(tree->raiz, dado); // Recebe sempre o novo nó inserido, garantindo a estrutura da ABB
}
void LeArquivo(FILE *fp, Pessoa *p, ABB *tree)
{
    char ler[100], recebe[20];
    int k = 0;
    while (fgets(ler, sizeof(ler), fp) != NULL)
    {
        int count = 0, i = 0;
        while (ler[count] != ',')
        {
            p->nome[count] = ler[count];
            count++;
        }
        p->nome[count] = '\0';
        count++;
        while (ler[count] != ',')
        {
            recebe[i] = ler[count];
            count++;
            i++;
        }
        recebe[i] = '\0';
        p->altura = atof(recebe);
        count++;
        for (int i = 0; i < 2; i++)
        {
            recebe[i] = ler[count];
            count++;
        }
        i = 2;
        recebe[i] = '\0';
        p->idade = atoi(recebe);
        k++;
        comecaArvore(tree, *p); // Passo o conteudo de p
    }
}
No *buscaABB(No *raiz, int dado)
{
    // Casos base da minha recursao

    if (raiz->dado.idade == dado)
        return raiz;
    if (raiz == NULL)
        return NULL;

    if (dado < raiz->dado.idade) // Caso a idade da pessoa que busco seja menor do que a idade da pessoa que estou
        return buscaABB(raiz->esq, dado);

    if (dado > raiz->dado.idade) // Caso a idade da pessoa que busco seja maior do que a idade da pessoa que estou
        return buscaABB(raiz->dir, dado);
}

No *menorElemento(No *raiz)
{
    No *aux = raiz->dir; // Encontrar o menor a direita
    while (aux->esq != NULL)
        aux = aux->esq;
    return aux;
}

No *burcarPai(No *raiz, No *pessoa)
{
    // Casos base
    if (raiz == NULL || pessoa == raiz)
        return NULL; // Raiz não tem pai

    if (raiz->dir == pessoa || raiz->esq == pessoa)
        return raiz;

    // Casos de recursao
    if (raiz->dado.idade > pessoa->dado.idade)
        return buscarPai(raiz->esq, pessoa);

    if (raiz->dado.idade < pessoa->dado.idade)
        return buscarPai(raiz->dir, pessoa);

    return NULL;
}
void remover(No *raiz, No *pessoa)
{
    No *neto, *pai = buscarPai(raiz, pessoa);
    // Casos base,folhas, nós com apenas um filho ou nós com 2 filhos
    if (pessoa->dir == NULL && pessoa->esq == NULL) // Caso seja um folha da minha arvore
    {
        if (pai->esq == pessoa)
            pai->esq = NULL;
        else
            pai->dir = NULL;

        free(pessoa);
        return;
    }

    if (pessoa->dir == NULL) // Caso o no que desejo remover tenha apenas um filho a esquerda
        neto = pessoa->esq;
    else
        neto = pessoa->dir; // Caso o nó que desejo remover tenha apenas um filho a direita
    if (pai->esq == pessoa)
    {
        pai->esq = neto;    //Redireciono o neto para ser novo filho de pai
        free(pessoa);
        return;
    } 
    else
    {
        pai->dir = neto;
        free(pessoa);
        return;
    }
    
}