#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int dado;
    struct no *prox;
}No;

typedef struct fila{
    struct no *inicio, *fim;
    int tamFila;
}Fila;

int enqueue(Fila *f, int dado)
{
    No *elem= (No*)malloc(sizeof(No));
    if(f->inicio ==NULL)    //Fila esta vazia
    {
        f->inicio = elem;
        f->fim= elem;
        return 1;
    }
    f->fim->prox= elem;
    f->fim= elem;       //Sempre se insere no final da fila, por isso inserimos no fim
    return 1;
}
/**
 * Para inserirmos o elemento na fila, precisamos inserilo no final da fila, dps de verificarmos q a nossa fila nn esta vazia, sabemos que o nosso
 * fim é um elemento ja, e por isso dizemos q o proximo dele receba o novo elemento que acabou de chegar, e depois dizemos que o nosso final da fila seja esse
 * novo elemento
 * o elemento atual da nossa fila aponta para o proximo elemento, e o nosso final da fila passa a ser o novo elemento
*/

/**
 * No conceito de fila, o ultimo elemento entra no final, e o primeiro elemento é o que é retirado primeiro da fila
 * Logo, na hora de retirarmos um elemento da nossa fila, retiramos o primeiro elemento, vulgo inicio, e fazemos com que o elemento que
 * ele aponta, vulgo proximo elemento, vire o novo inicio depois
*/
int dequeue(Fila *f)
{
    int val = f->inicio->dado;
    if (f->inicio == NULL)
        return 0;
    No *aux = f->inicio;
    f->inicio = aux->prox;
    free(aux);
    return val;
}
