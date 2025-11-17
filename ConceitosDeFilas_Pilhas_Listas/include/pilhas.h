#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    int dado; // O tipo do dado vai variar dependendo da aplicação da pilha
    struct no *prox;   // Aponta para o proximo dado, logo tem que ser mesmo tipo da struct, para apontar para um futuro prox dado
} No;

typedef struct pilha
{
    int tamPilha;
    struct no *topo;
    // Last in, first out, ou seja, ultimo a chegar sempre será o primeiro a sair.
} Pilha;

void push(Pilha *p, int dado)
{
    No *elemento = (No *)malloc(sizeof(No));
    elemento->dado = dado;    // Inseri o dado no elemento da minha pilha
    elemento->prox = p->topo; // proximo recebe o endereço de topo, (proximo passa a ser o antigo topo)
    p->topo = elemento;       // Meu topo passa a ser meu elemento (topo agr é o novo elemento que chegou)
    p->tamPilha++;
}
/* O primeiro elemento da pilha aponta para um void, ja que so existe ele na pilha
mas a partir do momento em que inserimos mais um elemento na pilha, esse novo elemento deve apontar pro antigo elemento, vulgo
(antigo topo da pilha), assim nn perdemos referencia da onde estao cada dado da pilha.
E para isso funcionar, precisamos fazer com que o topo da pilha sempre atualize recebendo o endereço do novo elemento que chegou, garantindo que
o novo elemento seja sempre o topo da pilha, e com isso fazendo com q o elemento novo aponte para o antigo topo.
*/
int pop(Pilha *p, int dado)
{
    dado = p->topo->dado;   //Last in, first out, sempre retirar o ultimo elemento da pilha, o topo
    No *aux= p->topo;
    p->topo = aux->prox;
    free(aux);
    p->tamPilha--;
    return dado;
}
/*
    Guardo o dado que quero remover da minha pilha caso eu precise dele, crio uma aux para nn perder o endereço do topo, e faço com que
    o topo aponte para o antigo topo. Ou seja, removo o topo da pilha, e faço com q o elemento anterior a ele vire o novo topo
*/