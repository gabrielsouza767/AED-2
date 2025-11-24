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
    LeArquivo(fp, &p, &tree);
    printf("Digite a idade de quem desejas buscar: ");
    scanf("%d", &idade);
    No *pessoaEncontrada = buscaABB(tree.raiz, idade);
    printf(" Nome da pessoa: %s , idade: %d e altura: %.2f", pessoaEncontrada->dado.nome, pessoaEncontrada->dado.idade, pessoaEncontrada->dado.altura);
    fclose(fp);
    return 0;
}
