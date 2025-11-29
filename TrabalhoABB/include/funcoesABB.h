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
/**
 * @param Raiz é o Nó a ser encontrado na recursao para fazer e remoção
 * @param pessoa é o Nó em que esta a pessoa que desejo remover
 * @brief A função de remover é recursiva pois preciso chegar ao nó que desejo remover, e ao retornar, já retorno ao pai o neto por exemplo,
 *  ou NULL se for uma folha, sem precisar fazer uma função de buscar o pai do nó que removerei.
 */
No *remover(No *raiz, No *pessoa)
{
    // Casos base
    if (raiz == NULL)
        return NULL; // Raiz não tem pai
    // Casos de recursao
    if (raiz->dado.idade > pessoa->dado.idade) // Se o nó onde estou é maior do q o o nó que quero remover, sei que tenho que ir para a esquerda
        raiz->esq = remover(raiz->esq, pessoa);

    else if (raiz->dado.idade < pessoa->dado.idade) // Se o nó onde estou é menor do q o nó que quero remover, vou para a direita
        raiz->dir = remover(raiz->dir, pessoa);
    else // Se for igual
    {
        // Casos base,folhas, nós com apenas um filho ou nós com 2 filhos
        /**
         * Este caso já serve para as folhas e unico filho, pois se for uma folha, irá satisfazer a condição de pessoa->dir == NULL, e por ser uma folha
         * já ira retornar o pessoa->esq que é NULL tambem.
         * E por ser uma recursao, já retorna ao pai do nó que desejo remover, o filho ou se for uma folha, NULL.
         */

        if (raiz->dir == NULL) // Caso o no que desejo remover tenha apenas um filho a esquerda
        {
            No *aux = raiz->esq;
            free(raiz);
            return aux;
        }
        else if (raiz->esq == NULL) // Caso o nó que desejo remover tenha apenas um filho a direita
        {
            No *aux = raiz->dir;
            free(raiz);
            return aux;
        }
        else
        {
            No *menorElem = menorElemento(raiz->dir);
            raiz->dado = menorElem->dado;
            raiz->dir = remover(raiz->dir, menorElem);
        }
    }
    return raiz;
}

No *imprimir(No *raiz)
{
    // Caso base
    if (raiz == NULL)
        return NULL;
    imprimir(raiz->dir);
    printf("----------------------------------------\n");
    printf("Nome: %s \n", raiz->dado.nome);
    printf("Idade: %d \n", raiz->dado.idade);
    printf("Altura: %.2f \n", raiz->dado.altura);
    printf("----------------------------------------\n");
    imprimir(raiz->esq);
}