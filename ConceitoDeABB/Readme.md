# 🌳 Árvore Binária de Busca (ABB) em C

Este repositório apresenta uma implementação completa e didática de uma **Árvore Binária de Busca (ABB)** em linguagem C.  
O objetivo é demonstrar domínio de estruturas de dados fundamentais, incluindo:

- Estruturação de nós  
- Uso de ponteiros  
- Alocação dinâmica  
- Inserção ordenada  
- Busca eficiente  
- Percurso em ordem (in-order)  
- Recursão  

A ABB é uma estrutura muito utilizada em bancos de dados, compiladores, organização de arquivos e diversos algoritmos que dependem de busca rápida.

---

## 📘 O que é uma ABB?

Uma **Árvore Binária de Busca** é uma árvore onde:

- Cada nó possui **um valor**, **um ponteiro para a esquerda** e **um ponteiro para a direita**.
- Valores menores ficam à **esquerda**.
- Valores maiores ficam à **direita**.

Isso garante operações eficientes, com complexidade média:

| Operação  | Complexidade Média |
|----------|--------------------|
| Inserção | O(log n)           |
| Busca    | O(log n)           |
| Impressão| O(n)               |

---

## ✨ Representação visual

Exemplo de uma ABB:

       (8)
     /     \
  (3)       (10)
 /   \         
(1) (6) 
