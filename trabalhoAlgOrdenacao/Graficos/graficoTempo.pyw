import matplotlib.pyplot as plt

# Nomes dos algoritmos
nomes = ["Bubble Sort", "Quick Sort", "Merge Sort"]

# Leitura dos blocos de dados
blocos = []
bloco_atual = []

with open("./Graficos/medias.txt", "r") as f:
    for linha in f:
        linha = linha.strip()
        if not linha:
            if bloco_atual:
                blocos.append(bloco_atual)
                bloco_atual = []
        else:
            bloco_atual.append(linha)
    if bloco_atual:
        blocos.append(bloco_atual)

print(f"Encontrei {len(blocos)} blocos.")

# Geração do gráfico
for i, bloco in enumerate(blocos):
    n = []
    tempo = []
    for linha in bloco:
        valores = linha.split()
        n.append(int(valores[0]))
        tempo.append(float(valores[1]))
    plt.plot(n, tempo, marker='o', label=nomes[i])

# Configuração do gráfico
plt.title("Comparação de tempos dos algoritmos de ordenação")
plt.xlabel("Tamanho do vetor (n)")
plt.ylabel("Tempo de execução (s)")
plt.yscale("log")  # 👈 Faz aparecer tempos pequenos
plt.grid(True, which="both", linestyle="--", linewidth=0.5)
plt.legend()

# Mostrar e salvar
plt.savefig("grafico_complexidade.png", dpi=300)
plt.show()
