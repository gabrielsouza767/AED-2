#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int dado;
    struct no *prox;
} No;
typedef struct lista
{
    struct no *cabeca;
    int tam;
} Lista;

int ListaVazia(Lista *l)
{
    l->cabeca == NULL ? 1 : 0;
}

/**
 * A cabeça da lista nunca é alterada, quando inserimos um novo elemento na lista, esse novo elemento aponta
 * para onde a cabeça da lista apontava, no caso (cabeça->prox) e ai atualizamos para quem a cabeça da lista aponta agora,
 * no caso, ela vai apontar para o novo elemento que acabou de chegar, (cabeça->prox = elemento)
 */
int insere(Lista *l, int dado)
{
    No *elemento = (No *)malloc(sizeof(No));
    if (elemento == NULL)
        return 0; // Deu errado a alocação dinamica
    elemento->dado = dado;
    if (ListaVazia(l))
    {
        elemento->prox = elemento;
        l->cabeca = elemento;
        return 1;
    }
    elemento->prox = l->cabeca->prox;
    l->cabeca->prox = elemento;
    return 1;
}

int busca(Lista *l, int dado)
{
    No *aux = l->cabeca;
    if (aux->dado == dado) // Caso o dado que queremos remover esteja na cabeça da nossa lista
    {
        if (aux->prox == aux) // Caso a lista seja de 1 unico elemento
        {
            l->cabeca = NULL;
            free(aux);
            return 1;
        }
        l->cabeca = l->cabeca->prox; // Para deixar mais intuitivo o conceito de "a cabeça vai ser o proximo dela", mas poderia ser aux->prox
        free(aux);
        return 1;
    }
    while (aux->prox != l->cabeca)      //Percorre a lista circular 1 vez so
    {
        if (aux->dado == dado)
        {
            No *aux2 = aux->prox;   //recebe o elemento que esta o dado
            aux->prox = aux->prox->prox;    //o nosso aux é um elemento para tras, o nosso dado esta no proximo dele, 
            //por isso aux->prox, e como vamos deletalo da memoria, fazemos com que o nosso aux -> aponte para onde o nosso dado estava apontando
            free(aux2);
            return 1;
        }
        aux=aux->prox;      //Atualizando o aux
    }
    return -1;      //Caso o dado nao exista
}
