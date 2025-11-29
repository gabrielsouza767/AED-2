#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/funcoesABB.h"
int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int quantidade = QuantPessoas(fp), idade, flag = 0;
    char escolha;
    ABB tree;
    tree.raiz = NULL;
    Pessoa p;
    No *pessoaEncontrada = NULL;
    LeArquivo(fp, &p, &tree);
    do
    {
        printf("Digite a idade de quem desejas buscar: ");
        scanf("%d", &idade);
        pessoaEncontrada = buscaABB(tree.raiz, idade);
        if (pessoaEncontrada != NULL)
        {
            printf("----------------------------------------\n");
            printf("Pessoa encontrada! \n");
            printf("----------------------------------------\n");
            printf("Nome: %s \n", pessoaEncontrada->dado.nome);
            printf("Idade: %d \n", pessoaEncontrada->dado.idade);
            printf("Altura: %.2f \n", pessoaEncontrada->dado.altura);
            printf("----------------------------------------\n");
            printf("Deseja remove-la? (s/n)");
            scanf(" %c", &escolha);
            if (escolha == 's' || escolha == 'S')
            {
                tree.raiz = remover(tree.raiz, pessoaEncontrada);
                printf("Pessoa removida com sucesso!\n");
                imprimir(tree.raiz);
            }
            else
                printf("Muito obrigado!");
        }
        else
            printf("Pessoa não encontrada! \n");
        printf("Deseja buscar mais alguem? (s/n)");
        scanf(" %c", &escolha);
        if (escolha == 'n' || escolha == 'N')
            flag = 1;

    } while (!flag);
    fclose(fp);
    return 0;
}
