#include <stdio.h>
#include <stdlib.h>
#include "../include/funcoesABB.h"
int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int quantidade = QuantPessoas(fp);
    ABB *tree;
    Pessoa *p = (Pessoa *)malloc(quantidade * sizeof(Pessoa));
    LeArquivo(fp, p);
    for (int i = 0; i < quantidade; i++)
    {
        printf("%s \n", p[i].nome);
        printf("%.2f\n ", p[i].altura);
        printf("%.d\n ", p[i].idade);
    }
    comecaArvore(tree,p[0]);
    for (int i = 1; i < quantidade; i++)
        inserirABB()
    
    fclose(fp);
    free(p);
    return 0;
}
