#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;       //Pode ser qualquer tipo de dado
    struct no *esq, *dir;
}No;

typedef struct ABB{
    struct no *raiz;
}ABB;

No* criaNo(int dado)
{
    No *elemento = (No*)malloc(sizeof(No)); //Alocando dinamicamente um No
    if (elemento == NULL)       //Caso a alocação de errado, falte memoria por exemplo
    {
        printf("Deu errado a alocacao! \n");
        exit(1);
    }
    elemento->dado = dado;
    elemento->dir = NULL;
    elemento->esq = NULL;
    return elemento;
}
void Alocação(ABB *t, int dado)
{
    t->raiz = inserir(t->raiz, dado);
}
No* inserir( No *raiz, int dado)
{
    //Caso base
    if (raiz == NULL)
        return raiz= criaNo(dado);

    if (dado < raiz->dado)                              //Coloco meu dado for menor que o  atual, coloco ele a esquerda
        return raiz->esq = inserir(raiz->esq, dado);
    if (dado > raiz->dado)                              //Caso meu dado seja maior, coloco ele a direita 
        return raiz->dir = inserir(raiz->dir,dado);
    return raiz;
}

No* buscaABB(No *raiz, int dado)
{
    //Caso base 
    if (raiz->dado == dado || raiz == NULL)
        return raiz;            //Encontrei o dado que eu queria e onde ele esta

    //Casos de recursao ate encontrar
    if (dado > raiz->dado)
        return buscaABB(raiz->dir, dado);
    if (dado< raiz->dado)
        return buscaABB(raiz->esq, dado);
    
}

void imprime( No *raiz)
{
    //caso base 
    if(raiz ==NULL)
        return;
    imprime(raiz->esq);
    printf("%d \n",raiz->dado);
    imprime(raiz->dir);
    printf("%d \n", raiz->dado);
}