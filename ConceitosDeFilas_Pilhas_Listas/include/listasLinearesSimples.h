#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int dado;
    struct no *prox;
}No;

typedef struct lista{
    struct no *inicio;
    int tam;
}Lista;

void criaLista(Lista *l)
{
    l->inicio = NULL;
    l->tam= 0;
}

int ListaVazia(Lista *l)
{
    l->inicio == NULL ? 1 : 0;
}
int insereComeco(Lista *l, int dado){
    No *aux = (No*)malloc(sizeof(No));
    if (ListaVazia(l))
    {
        aux->dado = dado;
        l->inicio = aux;
        aux->prox= NULL;
        l->tam++;
        return 1;
    }
    aux->dado = dado;
    aux->prox = l->inicio;      //Prox aponta para o antigo inicio 
    l->inicio = aux;            //Inicio passa a ser o novo elemento
    l->tam++;
    return 1;
}
/**
 * Sempre inserimos no inicio da fila, entao o inicio é o elemento q chega e se estiver vazia, este elemento aponta para NULL
 * Caso nao esteja vazia, primeiro fazemos com que o proximo desse elemento que chegou aponte para o antigo inicio, e ai atualizamos o inicio
 * (inicio recebe o novo elemento)
*/
int dequeue(Lista *l, int *dado)
{
    No *aux = l->inicio;
    *dado = aux->dado;
    l->inicio = l->inicio->prox;
    free(aux);
    return 1;
}

int buscaLista(Lista *l, int dado){
    No *aux = l->inicio;
    while (l->tam >0)
    {
        if (aux->dado == dado)
            return l->tam;
        aux=aux->prox;
        l->tam--;
    }
    return -1;
}