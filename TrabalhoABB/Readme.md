# 📄 **Trabalho de Estrutura de Dados — ABB com Vetor Dinâmico e Leitura de CSV**

Este projeto implementa um sistema simples de gerenciamento de pessoas utilizando:

- **Leitura de dados a partir de um arquivo CSV**
- **Inserção dos dados em uma Árvore Binária de Busca (ABB)**
- **Busca eficiente dentro da árvore**
- **Remoção opcional de um elemento encontrado**

O objetivo do trabalho é praticar conceitos fundamentais de **manipulação de arquivos**, **estruturas encadeadas**, **recursão** e **árvores binárias de busca**.

---

## 🧠 **Conceitos Aplicados no Projeto**

### ✔ 1. Leitura de Arquivo CSV  
O programa lê um arquivo `.csv` contendo informações estruturadas de pessoas.  
Cada linha do arquivo representa:

```
nome,altura,idade
```

Esses dados são lidos e separados manualmente (via parsing de linha), convertidos para os tipos adequados e enviados para a Árvore Binária de Busca (ABB).


---

### ✔ 2. Estrutura de Dados — ABB  
Após a leitura do arquivo, cada elemento é inserido em uma **Árvore Binária de Busca**, utilizando como chave:

```
idade
```

Operações implementadas:

- Inserção recursiva
- Navegação pela árvore
- Armazenamento ordenado por idade

---

### ✔ 3. Busca e Remoção  
O usuário informa a **idade** ou o **nome** para procurar uma pessoa na ABB.

Ao encontrar:

- os dados completos são exibidos  
- o usuário decide se deseja **remover** a pessoa da árvore  

A remoção segue os casos clássicos de uma ABB:

1. Nó folha  
2. Nó com 1 filho  
3. Nó com 2 filhos (substituição pelo sucessor)

---

## 🗂 **Arquitetura Geral**

```
CSV -> ABB -> Busca -> Remoção (opcional)
```

Fluxo do programa:

1. Ler arquivo CSV linha por linha  
2. Converter cada linha em uma struct `Pessoa`  
3. Inserir cada pessoa na ABB  
4. Permitir busca eficiente  
5. Perguntar ao usuário se deseja remover o registro  

---

## 🛠 **Tecnologias e Linguagem**

- **C (padrão ANSI C)**
- Manipulação manual de memória
- `malloc`, `free`
- Ponteiros, structs e recursão
- Leitura de arquivos com `fgets`
- Árvores binárias de busca implementadas “na mão”

---

## 📌 **Estruturas Principais**

### `Pessoa`
```c
typedef struct {
    char nome[50];
    float altura;
    int idade;
} Pessoa;
```

### `No (nó da ABB)`
```c
typedef struct no {
    Pessoa dado;
    struct no *esq;
    struct no *dir;
} No;
```

### `ABB`
```c
typedef struct {
    No *raiz;
} ABB;
```

---

## 🔍 **Demonstração da Busca**

Ao procurar por uma pessoa:

```
Digite a idade da pessoa que deseja buscar:
```

Se encontrada:

```
Pessoa encontrada!
Nome: ...
Altura: ...
Idade: ...

Deseja remover esta pessoa da árvore? (s/n)
```

---

## 🧹 **Remoção**

A remoção segue o padrão clássico:

- reorganiza a árvore
- mantém suas propriedades de ordenação
- libera memória corretamente

---

## 📦 **Como Executar**

1. Coloque o arquivo CSV na mesma pasta do projeto
2. Compile:

```
gcc main.c -o programa
```

3. Execute:

```
./programa
```

---

## 📁 **Estrutura Sugerida do Repositório**

```
📦 trabalhoABB
 ┣ 📄 README.md
 ┣ 📄 main.c
 ┣ 📄 funcoesABB.h
 ┗ 📄 dadosPessoas.csv
```

---

## 🧩 **Possíveis Extensões Futuras**

- Transformar a ABB em AVL (balanceada)
- Permitir cadastro manual de novas pessoas
- Exportar novamente o CSV após remoções

---

## 🚀 **Objetivo Acadêmico**

Este projeto foi desenvolvido como forma de:

- fortalecer domínio em manipulação de ponteiros  
- treinar parsing de strings e arquivos  
- implementar com clareza uma ABB completa  
- exercitar organização modular de código  

Ideal para portfólio e para demonstrar domínio de estruturas fundamentais em C.

