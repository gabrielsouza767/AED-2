#include <stdio.h>
#include <stdlib.h>
#define N 100
#define MAX_INT 1000000
// ============================================================================
// ESTRUTURAS DE DADOS
// ============================================================================

typedef struct
{
    int **adj; // Matriz N x N
    int num_vertices;
    // Removido o campo 'num_arestas' para forçar o calculo
} GrafoMatriz;

typedef struct No
{
    int vertice;
    int custo;
    int pred;
    int peso;
    struct No *proximo;
} No;

typedef struct
{
    No **adj; // Vetor de ponteiros
    int num_vertices;
    // Removido o campo 'num_arestas' para forçar o calculo
} GrafoLista;

typedef struct heap
{
    No **vetor;     // Vetor dos ponteiros dos Nós
    int tamanho;    // Quantos elementos tenho na Heap
    int capacidade; // Tamanho maximo da Heap
} Heap;
Heap *criandoHeap(int capacidade)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));
    if (h == NULL)
        return NULL;
    h->tamanho = 0;
    h->capacidade = capacidade;                          // Capacidade da minha Heap
    h->vetor = (No **)malloc(capacidade * sizeof(No *)); // Meu vetor dos Nós do meu grafo
    if (h->vetor == NULL)
    {
        free(h);
        return NULL;
    }
    for (int i = 0; i < capacidade; i++)
        h->vetor[i] = NULL; // Faço cada indice do meu vetor apontar para NULL

    return h;
}
/**
 * @param vertice é o vértice que sera inserido na heap
 * @param h é a minha binary Heap em si
 * @brief Esta  função é responsável por inserir o vértice na minha Heap, primeiro eu digo que meu indice é o tamanho da minha Heap antes de atualiza-la
 * pois é onde o vértice será inserido, dps se minha Heap estiver vazia, sei que o primeiro elemento é a raiz da minha binary tree, entao ja coloco o meu
 * vértice como raiz e aumento o tamanho da heap.
 * Quando eu inserir o proximo vértice, irei inseri-lo no ultimo elemento da minha Heap, pois ficara mais fácil de ajusta-lo e aumento o tamanho novamente.
 * Calculo o pai de  acordo com o i, pois é onde o novo vértice inserido realmente esta em meu vetor, se eu usasse o h->tamanho, estaria acessando uma posição null
 * Calculo o heapfyUp, pois se o vertice tiver um custo menor que o pai, ele tem que subir na minha Heap, ja que estou em uma min-heap
 * Enquanto o custo do novo vértice for menor que o pai, eu faço o swap entre eles, recalculando claro, o devido pai correto a cada interação
 */
Heap *inserirHeap(No *vertice, Heap *h)
{
    int pai, i = h->tamanho;
    if (h->vetor[0] == NULL || h->tamanho == 0) // Se a minha Heap estiver vazia
    {
        h->vetor[0] = vertice; // Aloco a raiz na minha binary Heap
        h->tamanho++;
        return h;
    }
    h->vetor[h->tamanho] = vertice; // Insiro o novo vertice na ultima posição da minha heap
    h->tamanho++;                   // Agr minha heap cresceu
    pai = (i - 1) / 2;              // Calculo o pai de acordo com a heap antes do tamanho da heap aumentar, pois é aonde esta o elemento inserido
    // HeapfyUp, no momento inicial do Dijkstra ele nn muda nada, pois os nós tem custo infinito, mas deixo aqui pq vai q precisa
    while (i > 0 && h->vetor[i]->custo < h->vetor[pai]->custo) // Enquanto o custo dele for menor que o do pai, ele tem que subir
    {
        // Swap dos nós
        No *aux = h->vetor[pai];
        h->vetor[pai] = h->vetor[i];
        h->vetor[i] = aux;
        i = pai;           // atualizo indice
        pai = (i - 1) / 2; // Recalculo o pai
    }
    return h;
}

/**
 * @param vertice é o nó que eu devo encontrar na minha heap e fazer o heapfyUp nele
 * @param h é a minha heap em si e com os vertices do meu grafo
 * @brief Esta função encontra o vertice que teve o valor de custo alterado pelo dijkstra, e com isso consigo encontrar o pai do nó tbm,
 * com isso, consigo fazer heapfyUp nele ate ele chegar na minha raiz, com isso a heap se tornou a fila com prioridade
 */
Heap *decrease_Key(No *vertice, Heap *h)
{
    int pai, i = -1; // Para caso eu nn encontre o nó
    for (int j = 0; j < h->tamanho; j++)
    {
        if (h->vetor[j]->vertice == vertice->vertice) // Achei o vertice
        {
            pai = (j - 1) / 2; // Achei o pai dele
            i = j;             // Guardo o indice do vertice
            break;
        }
    }

    // HeapfyUp
    while (i > 0 && h->vetor[i]->custo < h->vetor[pai]->custo) // Enquanto o custo dele for menor que o do pai, ele tem que subir
    {
        // Swap dos nós
        No *aux = h->vetor[pai];
        h->vetor[pai] = h->vetor[i];
        h->vetor[i] = aux;
        i = pai;           // atualizo o indice
        pai = (i - 1) / 2; // Recalculo o pai
    }
    return h;
}

/**
 * @param h é a minha heap em si normal
 * @brief Esta função remove o menor elemento da minha Heap, no caso a raiz, e substitue ela pelo o ultimo elemento, mas agr temos q reestruturar a Heap,
 * usando o HeapfyDown nós conseguimos fazer essa reestruturação, descendo os nós que tem maior grau até a folha, se tiver apenas um filho ou dois, mas reestruturamos
 * a heap.
 * Colocamos o ultimo elemento pois sabemos q ele tem um grau maior que os outros nos, e vamos descendo ele ate seu respectivo lugar, porem dando o swap entre os nos
 * deixando os nós em seus devidos lugares na heap.
 * Sempre verificando o custo do pai com seu respectivo filho, seja ele na esquerda ou caso tenha 2 filhos, o filho com menor custo
 */
No *popmin(Heap *h)
{
    int i, filhoEsq, filhoDir;
    No *raiz = h->vetor[0], *aux = NULL;
    h->vetor[0] = h->vetor[h->tamanho - 1]; // Minha raiz passa a ser o ultimo elemento
    h->tamanho--;
    i = 0;
    while (1)
    {
        filhoEsq = (2 * i) + 1;
        filhoDir = (2 * i) + 2;

        // não tem filho -> chegou numa folha
        //Pois pela conta filhoesq=(2*i)+1 e flhodir=(2*i)+2, se o esquerdo ja passou do tamanho da Heap, impossivel ter um filho a direita
        if (filhoEsq >= h->tamanho)
            break;

        // só tem filho esquerdo
        if (filhoDir >= h->tamanho)
        {
            if (h->vetor[i]->custo > h->vetor[filhoEsq]->custo) // Se o pai tem um custo maior q o filho, desce o pai (HeapfyDown)
            {
                // Swap dos nós
                aux = h->vetor[i];
                h->vetor[i] = h->vetor[filhoEsq];
                h->vetor[filhoEsq] = aux;
                i = filhoEsq; // Atualizo meu indice para calcular o filho corretamente se tiver que descer d nv
            }
            break; // Se encontrou e nn precisou mais descer
        }

        // tem os dois filhos
        int menor = filhoEsq;

        if (h->vetor[filhoDir]->custo < h->vetor[filhoEsq]->custo) // caso o menor filho seja o da direita
            menor = filhoDir;

        if (h->vetor[i]->custo > h->vetor[menor]->custo) // Caso eu tenha que descer o pai novamente, mas dessa vez o do menor filho
        {
            // Swap dos nós
            aux = h->vetor[i];
            h->vetor[i] = h->vetor[menor]; // O pai passa a ser o menor filho agr, mantendo minha min-Heap
            h->vetor[menor] = aux;         // O filho passa a ser o pai
            i = menor;
        }
        else
            break;
    }

    return raiz; // Retorno a nova raiz da minha Heap
}

int isMinHeap(Heap *h)
{
    int filhoEsq, filhoDir;
    for (int i = 0; i < h->tamanho-1; i++)    //Percorrer minha Heap
    {
        filhoEsq = (2 * i) + 1, filhoDir = (2 * i) + 2;
        if (filhoEsq < h->tamanho)      //Se existe um filho a esquerda
        {
            if (h->vetor[i]->custo > h->vetor[filhoEsq]->custo) //Se o pai do filho a esquerda é maior que ele,logo a Heap esta errada
            {
                printf("Heap inválida!...\n");
                return -1;
            }
        }
        if (filhoDir < h->tamanho)      //Se existe um filho a direita
        {
            if (h->vetor[i]->custo > h->vetor[filhoDir]->custo)     //Se o pai do filho a direita é maoior que ele, logo a Heap esta errada
            {
                printf("Heap inválida!...\n");
                return -1;
            }
        }
    }
    return 1;   //Heap esta correta
}

// ============================================================================
// PARTE 1: MATRIZ DE ADJACÊNCIA
// ============================================================================

GrafoMatriz *criar_grafo_matriz(int n)
{
    GrafoMatriz *g = (GrafoMatriz *)malloc(sizeof(GrafoMatriz));
    g->num_vertices = n;
    g->adj = (int **)malloc(g->num_vertices * sizeof(int *));
    for (int i = 0; i < n; i++)
        g->adj[i] = (int *)calloc(n, sizeof(int));
    return g;
}

void inserir_aresta_matriz(GrafoMatriz *g, int u, int v)
{
    // TODO: Validação se os vértices são válidos
    if (0 <= u && u < g->num_vertices) // Se u existe no num_vertices
        g->adj[u][v] = 1;              // Marco ele como 1
    if (0 <= v && v < g->num_vertices) // Se v existe no num_vertices
        g->adj[v][u] = 1;              // Marco ele como 1
    // TODO: Marcar g->adj[u][v] e g->adj[v][u] como 1
}

int contar_arestas_matriz(GrafoMatriz *g)
{
    int soma_total = 0;
    for (int i = 0; i < g->num_vertices; i++)
    {
        for (int j = 0; j < g->num_vertices; j++)
        {
            if (g->adj[i][j] > 0)
                soma_total++;
        }
    }
    // TODO: Percorrer toda a matriz contando quantos 1s existem.
    // Lembre-se: Como o grafo é não direcionado, a soma total dos 1s será o dobro das arestas.
    // Retorne (soma_total / 2).
    return soma_total / 2;
}

void imprimir_matriz(GrafoMatriz *g)
{
    printf("\n--- Matriz de Adjacencia ---\n");
    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%d: ", i);
        for (int j = 0; j < g->num_vertices; j++)
        {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

void destruir_grafo_matriz(GrafoMatriz *g)
{
    for (int i = 0; i < g->num_vertices; i++)
        free(g->adj[i]);
    free(g->adj);
    free(g);
}

// ============================================================================
// PARTE 2: LISTA DE ADJACÊNCIA
// ============================================================================

GrafoLista *criar_grafo_lista(int n)
{
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->adj = (No **)malloc(g->num_vertices * sizeof(No *)); // Deixei como num_vertices pois fica mais facil de ver q aloco 1 lista para cada vertice do meu grafo
    for (int i = 0; i < n; i++)
    {
        g->adj[i] = (No*)malloc(sizeof(No));    //Aloquei um nó para carregar consigo as informações do vertice, e o vertice ->prox é onde começa sua lista de adj
        g->adj[i]->vertice = i;
        g->adj[i]->custo= 0;
        g->adj[i]->peso = 0;
        g->adj[i]->pred =-1;
        g->adj[i]->proximo =NULL;
    }
    return g;
}
/**
 * @brief faço o lista->proximo receber o novo elemento pois, na minha lista, o indice dela em si é o meu vertice, ent onde realmente se inicia
 * a lista de adj do vertice seria o vertice->proximo, ou (*lista)->prox
*/
void inserir_na_lista(No **lista, int vizinho, int peso)
{
    No *elemento = (No *)malloc(sizeof(No));
    if (elemento == NULL)
    {
        printf("Erro na alocacao!\n");
        exit(1);
    }
    elemento->vertice = vizinho;
    elemento->peso = peso;
    elemento->proximo = (*lista)->proximo;  //O proximo do novo elemento é a antiga cabeça da lista de adj do vertice
    (*lista)->proximo = elemento;
    // TODO: Inserir novo nó no início da lista encadeada
}

void inserir_aresta_lista(GrafoLista *g, int u, int v, int peso)
{
    // TODO: Validação se os vértices são válidos
    // Aqui verifico se 'u' existe dentro do grafo.
    if (0 <= u && u < g->num_vertices)
        inserir_na_lista(&g->adj[u], v, peso); // Se 'u' é válido, inseri o vértice 'v' na lista de adjacência de 'u'. Isso representa uma aresta u -> v.
    if (0 <= v && v < g->num_vertices)
        inserir_na_lista(&g->adj[v], u, peso); // Isso representa a outra direção v -> u, já que este grafo é nao direcionado
    // Ou seja:
    // Se u e v forem válidos, cria-se uma aresta bidirecional entre eles.
    // Inseri v na lista de u e u na lista de v.
    // TODO: Chamar inserir_na_lista para (u, v) e (v, u)
}

int contar_arestas_lista(GrafoLista *g)
{
    int cont = 0;
    for (int i = 0; i < g->num_vertices; i++)
    {
        No *aux = g->adj[i];
        while (aux != NULL)
        {
            cont++;
            aux = aux->proximo;
        }
    }
    // TODO: Percorrer todas as listas encadeadas (de 0 a N-1).
    // Conte quantos nós existem no total.
    // Retorne (total_nos / 2).
    return cont / 2;
}

void imprimir_lista(GrafoLista *g)
{
    printf("\n--- Lista de Adjacencia ---\n");
    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%d -> ", i);
        No *atual = g->adj[i];
        while (atual != NULL)
        {
            printf("%d -> ", atual->vertice);
            atual = atual->proximo;
        }
        printf("NULL\n");
    }
}

void destruir_grafo_lista(GrafoLista *g)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        No *atual = g->adj[i];
        while (atual != NULL)
        {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

void Dijkstra(GrafoLista *g, No *s, int capacidade)
{
    Heap *h = criandoHeap(capacidade); 
    
    // 1. Inicializa todos os nós principais e insere na Heap
    for (int i = 0; i < g->num_vertices; i++)
    {
        g->adj[i]->custo = MAX_INT;     //Custo infinito para todos os vertices
        g->adj[i]->pred = -1;           //o predessessor / pai com o  -1
        inserirHeap(g->adj[i], h);      //Insiro na Heap
    }
    isMinHeap(h);
    // 2. O nó de origem s precisa ter custo 0 e o decrease_Key precisa ser aplicado no NÓ PRINCIPAL
    // O ponteiro 's' DEVE ser um dos nós principais
    s->custo = 0;   //Origem do grafo
    decrease_Key(s, h);
    isMinHeap(h);   //Verifico se minha Heap esta corrreta dps do primeiro decrease 
    while (h->tamanho > 0)
    {
        No *u = popmin(h); // 'u' é o NÓ PRINCIPAL (com custo, pred)
        isMinHeap(h);   //Verifico se minha Heap esta correta dps do popMin
        // elemento recebe o PRIMEIRO vizinho. u->vertice é o índice.
        // elemento_vizinho aponta para o primeiro item da lista de adjacência de 'u'.
        No *elemento_vizinho = u->proximo; 

        while (elemento_vizinho != NULL) //Percorro na lista de adjacencias de 'u'
        {
            // 'v_principal' é o vertice correspondente vizinho de 'u', que está na Heap.
            No *v_principal = g->adj[elemento_vizinho->vertice]; 
            int peso = elemento_vizinho->peso;  //peso da aresta
            
            // Relaxamento
            if (v_principal->custo > u->custo + peso)
            {
                v_principal->custo = u->custo + peso;
                v_principal->pred = u->vertice;
                
                // É essencial usar o 'v_principal' (o nó que está na Heap) para decrease_Key
                decrease_Key(v_principal, h); 
                isMinHeap(h);   //Verifico se minha Heap esta correta dps do decrease
            }
            elemento_vizinho = elemento_vizinho->proximo; 
        }
    }
    // Destruir Heap no final
    free(h->vetor);
    free(h);
}