#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int dado;
    struct no *prox, *ant;
}No;

typedef struct lista{
    No *inicio;
}Lista;

int insere(Lista *l, int dado)
{
    No *elem= (No*)malloc(sizeof(No));
    elem->dado = dado;
    if (l->inicio ==NULL)
    {
        l->inicio = elem;
        return 1;
    }
    elem->prox = l->inicio;     // o novo elemento recebe o antigo inicio
    l->inicio->ant = elem;      //o inicio antigo recebe como anterior o novo elemento, ja que inserimos o elemento no inicio da lista smp
    l->inicio = elem;           //atualizamos o novo inicio
    return 1;
}

int remove(Lista *l, int dado)
{
    No *aux = l->inicio;
    if(aux->dado == dado)
    {
        l->inicio = aux->prox;
        l->inicio->ant= NULL;
        free(aux);
        return 1;
    }
    while (aux->prox !=NULL)
    {
        aux = aux->prox;
        if (aux->dado == dado)
        {
            aux->ant->prox = aux->prox;
            aux->prox ->ant = aux->ant;
            free(aux);
            return 1;
        }
        
    }
    if (aux->dado == dado)
    {
        aux->ant->prox=NULL;
        free(aux);
        return 1;
    }
    return -1;
}