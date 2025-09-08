#include <stdio.h>
#include <stdlib.h>
#include "../include/include.h"

int main(int argc, char const *argv[])
{
    int tmp;
    FILE *fp = fopen(argv[1], "r+");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }
    tmp=alocAluno(fp);
    exemplo_leitura_linha(fp,tmp);
    fclose(fp);
    return 0;
}
