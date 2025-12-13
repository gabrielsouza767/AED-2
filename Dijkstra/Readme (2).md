# 📊 Grafos, Heap e Algoritmo de Dijkstra em C

Este repositório contém a implementação **do zero**, em linguagem **C**, de estruturas fundamentais de **Grafos** e de uma **Min-Heap (Fila de Prioridade)**, culminando na aplicação completa do **Algoritmo de Dijkstra** para cálculo de caminhos mínimos em grafos ponderados e não direcionados.

O projeto foi desenvolvido com **foco didático**, priorizando clareza conceitual, comentários detalhados e separação lógica das estruturas.

---

## 🧠 Conceitos Abordados

- Representação de grafos por:
  - **Matriz de Adjacência**
  - **Lista de Adjacência (listas encadeadas)**
- Estrutura de dados **Min-Heap (Heap Binária)**
- Operações fundamentais de Heap:
  - Inserção (`insert`)
  - Remoção do mínimo (`popmin`)
  - Atualização de prioridade (`decrease_key`)
  - Verificação de propriedade de Min-Heap
- Algoritmo de **Dijkstra** utilizando Heap como fila de prioridade
- Uso intensivo de **ponteiros**, **alocação dinâmica** e **structs**

---

## 🗂️ Estruturas de Dados

### 🔹 Grafo (Matriz de Adjacência)
```c
typedef struct {
    int **adj;
    int num_vertices;
} GrafoMatriz;
```
- Matriz `N x N`
- Grafos não direcionados
- Contagem de arestas calculada dinamicamente

---

### 🔹 Grafo (Lista de Adjacência)
```c
typedef struct No {
    int vertice;
    int custo;
    int pred;
    int peso;
    struct No *proximo;
} No;

typedef struct {
    No **adj;
    int num_vertices;
} GrafoLista;
```
- Cada vértice possui um **nó principal**
- A lista de adjacência começa em `vertice->proximo`
- Permite armazenar **pesos das arestas**

---

### 🔹 Heap Binária (Min-Heap)
```c
typedef struct heap {
    No **vetor;
    int tamanho;
    int capacidade;
} Heap;
```
Utilizada como **fila de prioridade** no algoritmo de Dijkstra.

#### Operações implementadas:
- `criandoHeap`
- `inserirHeap` (Heapify-Up)
- `decrease_Key`
- `popmin` (Heapify-Down)
- `isMinHeap` (verificação de integridade)

---

## 🚀 Algoritmo de Dijkstra

A implementação do Dijkstra segue rigorosamente o modelo teórico:

1. Inicializa todos os vértices com custo infinito
2. Insere todos os vértices na Min-Heap
3. Define o vértice de origem com custo `0`
4. Aplica `decrease_key`
5. Enquanto a Heap não estiver vazia:
   - Remove o vértice de menor custo (`popmin`)
   - Relaxa todas as arestas adjacentes
   - Atualiza custos e predecessores

```c
void Dijkstra(GrafoLista *g, No *s, int capacidade);
```

Ao final:
- Cada vértice contém:
  - `custo`: menor distância até a origem
  - `pred`: vértice predecessor no caminho mínimo

---

## 🧪 Validações e Segurança

- Verificação de índices válidos
- Controle manual de memória (`malloc` / `free`)
- Função auxiliar para validar a Heap após operações críticas

---

## 🛠️ Compilação

Compile utilizando **GCC**:

```bash
gcc main.c -o grafo
```

Execute:

```bash
./grafo
```

---

## 🎯 Objetivo do Projeto

Este projeto foi desenvolvido com o objetivo de:

- Consolidar fundamentos de **Algoritmos e Estruturas de Dados**
- Praticar implementação manual de **estruturas complexas em C**
- Compreender profundamente o funcionamento interno do **Dijkstra**
- Treinar raciocínio com **ponteiros e memória dinâmica**

---

## 📚 Próximos Passos (Ideias)

- Reconstrução explícita do caminho mínimo
- Suporte a grafos direcionados
- Implementação de Bellman-Ford
- Modularização em arquivos `.h` e `.c`
- Testes automatizados

---

## 👨‍💻 Autor

**Gabriel Souza**  
Estudante de Ciência da Computação  
Foco em Algoritmos, Estruturas de Dados e Sistemas de Baixo Nível

---

⭐ Se este projeto te ajudou a entender Grafos, Heap ou Dijkstra, considere deixar uma estrela!

