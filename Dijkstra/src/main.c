#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/grafos-alunos.h"
int main()
{
    int linhas = 10;
    int colunas = 10;

    GrafoLista *g = criar_grafo_lista(N);
    GrafoMatriz *gm = criar_grafo_matriz(N);

    srand(time(NULL));

    // =============================================================
    // GERAÇÃO PROCEDURAL DA CIDADE (GRAPH CITY) - lista + matriz
    // =============================================================
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            int id = i * colunas + j;

            // --------------------
            // CONEXÃO À DIREITA
            // --------------------
            if (j + 1 < colunas)
            {
                int vizinho = id + 1;
                int peso;

                // AVENIDA RÁPIDA NAS LINHAS 2 E 7 (horizontal)
                if (i == 2 || i == 7)
                    peso = 1;
                else
                    peso = (rand() % 10) + 1; // 1 a 10

                // insere na lista (bidirecional) com peso
                inserir_aresta_lista(g, id, vizinho, peso);

                // preenche a matriz com o peso (simétrica)
                gm->adj[id][vizinho] = peso;
                gm->adj[vizinho][id] = peso;
            }

            // --------------------
            // CONEXÃO PARA BAIXO
            // --------------------
            if (i + 1 < linhas)
            {
                int vizinho = id + colunas;
                int peso;

                // ZONA DE CONGESTIONAMENTO NAS COLUNAS 4 e 5 (vertical)
                if (j == 4 || j == 5)
                    peso = 20;
                else
                    peso = (rand() % 10) + 1;

                inserir_aresta_lista(g, id, vizinho, peso);

                gm->adj[id][vizinho] = peso;
                gm->adj[vizinho][id] = peso;
            }
        }
    }

    // =============================================================
    // IMPRIMIR MATRIZ E CONTAR ARESTAS (com pesos)
    // =============================================================
    printf("\n=== GRAPH CITY (MATRIZ 10x10) ===\n");
    imprimir_matriz(gm);

    // contar arestas a partir da matriz (qualquer entrada > 0 é aresta)
    printf("Total de arestas (matriz): %d (Esperado: 180)\n", contar_arestas_matriz(gm));

    // =============================================================
    // IMPRIMIR LISTA E CONTAR ARESTAS
    // =============================================================
    printf("\n=== GRAPH CITY (LISTA 10x10) ===\n");
    imprimir_lista(g);
    printf("Total de arestas (lista): %d (Esperado: 230)\n", contar_arestas_lista(g));

    // =============================================================
    // DIJKSTRA
    // =============================================================
    int origem = 0; // cruzamento (0,0)
    No *s = g->adj[origem];

    printf("\n=== DIJKSTRA A PARTIR DO VERTICE %d ===\n", origem);

    Dijkstra(g, s, N);
    // Imprimir resultados do Dijkstra
    for (int v = 0; v < N; v++)
    {
        printf("Vertice %d: custo = %d, predecessor = %d\n",
               v, g->adj[v]->custo, g->adj[v]->pred);
    }

    // cleanup
    destruir_grafo_matriz(gm);
    destruir_grafo_lista(g);
    return 0;
}
