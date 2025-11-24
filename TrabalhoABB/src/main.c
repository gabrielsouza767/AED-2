#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/funcoesABB.h"
int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int quantidade = QuantPessoas(fp) , idade;
    ABB tree;
    tree.raiz = NULL;
    Pessoa p;
    No *pessoaEncontrada= NULL;
    LeArquivo(fp, &p, &tree);
    printf("Digite a idade de quem desejas buscar: ");
    scanf("%d", &idade);
    pessoaEncontrada = buscaABB(tree.raiz, idade);
    if (pessoaEncontrada != NULL)
    {
       printf("----------------------------------------\n");
       printf("Pessoa encontrada! \n");
       printf("----------------------------------------\n");
       printf("Nome: %s \n",  pessoaEncontrada->dado.nome);
       printf("Idade: %d \n",  pessoaEncontrada->dado.idade);
       printf("Altura: %.2f \n",  pessoaEncontrada->dado.altura);
    }
    else
        printf("Pessoa não encontrada! \n");
    fclose(fp);
    return 0;
}
