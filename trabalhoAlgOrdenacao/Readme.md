# 🧮 Análise de Desempenho de Algoritmos de Ordenação

Projeto desenvolvido para a disciplina **Algoritmos e Estruturas de Dados II (AED-II)**, com o objetivo de **comparar o desempenho entre diferentes algoritmos de ordenação** aplicados sobre vetores dinâmicos de dados reais (nomes e notas de alunos).

---

## 📘 Descrição do Projeto

O programa realiza a leitura de **14 entradas de dados**, cada uma contendo nomes e notas de alunos.  
A partir dessas informações, o sistema:

1. Calcula a **média** de cada aluno.  
2. Armazena os alunos em **vetores dinâmicos**, cujo tamanho dobra a cada nova entrada (até chegar a **32.000 alunos**).  
3. Ordena esses vetores utilizando **três algoritmos de ordenação clássicos**:
   - 🫧 **BubbleSort**
   - ⚡ **QuickSort**
   - 🔀 **MergeSort**

Durante a execução, é medido o **tempo de ordenação** de cada algoritmo em cada entrada de dados, utilizando a biblioteca `time.h` e a função `clock()`.

---

## ⏱️ Metodologia de Teste

Para garantir uma análise confiável, cada conjunto de dados é ordenado **cinco vezes** por cada algoritmo.  
Os tempos são armazenados e, posteriormente, é calculada a **média dos tempos** de execução de cada algoritmo para cada tamanho de entrada.

Com esses dados, o programa gera:

- **5 relatórios individuais** (um para cada execução);  
- **1 relatório final** contendo a média dos tempos de ordenação;  
- **Gráficos comparativos** entre os algoritmos, mostrando o tempo em função do tamanho da entrada.

---

## 📊 Resultados Esperados

O experimento demonstra claramente as diferenças de complexidade entre os algoritmos:

| Algoritmo   | Complexidade Média | Observação |
|--------------|--------------------|-------------|
| **BubbleSort** | O(n²) | Crescimento quadrático, extremamente lento para grandes entradas. |
| **QuickSort**  | O(n log n) | Muito mais eficiente, especialmente em entradas médias e grandes. |
| **MergeSort**  | O(n log n) | Desempenho consistente e estável, mesmo em casos desfavoráveis. |

Assim, é possível **comprovar empiricamente** que o **BubbleSort**, por ter comportamento **quadrático**, apresenta tempos de execução muito superiores em relação aos algoritmos **QuickSort** e **MergeSort**.

---

## 🧠 Conceitos Utilizados

- Alocação dinâmica de memória (`malloc`, `realloc`, `free`);
- Ponteiros e manipulação de vetores de structs;
- Estruturas (`struct`) para armazenar dados dos alunos;
- Modularização do código em múltiplos arquivos (`.h` e `.c`);
- Funções genéricas de ordenação;
- Medição de tempo com `clock()` (biblioteca `<time.h>`);
- Escrita e leitura de arquivos de texto (`.txt`);
- Geração e análise de relatórios.

---

## ⚙️ Execução

1. Compile o projeto (exemplo usando **Code::Blocks** ou terminal):
   ```bash
   gcc main.c bubbleSort.c quickSort.c mergeSort.c relatorios.c -o analise -Wall
