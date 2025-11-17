# A2 - Ordenação e Análise de Desempenho em C

Este projeto implementa e compara o desempenho de três algoritmos de ordenação em C (Bubble, Insertion e Quick Sort), conforme especificado na atividade A2.

- **Aluna:** Clara Geovana Caldeira da Silva
- **RGM:** 46008896

---

Descrição e Métodos Implementados

O objetivo foi medir `passos` (soma de comparações e trocas/movimentações) e `tempo_ms` (tempo de CPU em milissegundos) ao ordenar os dígitos do RGM (N=8) e vetores aleatórios de N=100, 1000 e 10000.

Os 3 métodos escolhidos foram:

1.  **Bubble Sort:** Algoritmo de complexidade `O(n²)`, escolhido como base de comparação para os métodos ineficientes.
2.  **Insertion Sort:** Algoritmo `O(n²)` (caso médio), mas que possui um "melhor caso" de `O(n)` para dados "quase ordenados".
3.  **Quick Sort:** Algoritmo de complexidade `O(n log n)` (caso médio). Foi escolhido para demonstrar a enorme diferença de escalabilidade em relação aos métodos `O(n²)`. Foi usada a partição de **Lomuto**.

Como Compilar e Rodar

O projeto segue a estrutura de arquivos (`src/` e `README.md`) sugerida.

**Comando de compilação (usando GCC):**
```bash
# Compila todos os arquivos .c da pasta src, com otimização -O1
gcc -O1 -std=c11 src/*.c -o ordena

----------------------------
**Comando de execução:**
# O programa imprime o CSV formatado na saída padrão (terminal)
./ordena

----------------------------
Metodologia de Métricas

Contagem de Passos: A métrica "passos" (reportada no CSV) segue a política de ser a soma das médias de steps_cmp (comparações) e steps_swap (movimentações/trocas), após 5 execuções.

Medição de Tempo: O tempo de CPU foi medido em milissegundos usando clock() da <time.h>.

Resultados: Os valores na tabela são a média de 5 execuções (N_RUNS = 5) para cada cenário, garantindo maior estabilidade.

----------------------------
Discussão Crítica e Conclusão

Computabilidade e Correção: Todos os três métodos funcionaram e ordenaram corretamente o RGM "46008896" para "00466889", além de todas as amostras aleatórias testadas.

Escalabilidade (Teoria vs. Prática):

O(n²): A teoria O(n²) foi comprovada pelos dados. Quando o N aumentou 10x (de 1000 para 10000), o tempo do Bubble Sort aumentou 83 vezes (de 2.3ms para 193.5ms). O Insertion Sort aumentou 102 vezes (de 0.7ms para 74.8ms). Isso mostra que o custo cresce de forma quadrática, exatamente como a teoria prevê.

O(n log n): O Quick Sort provou sua eficiência. Quando o N aumentou 10x (de 1000 para 10000), seu tempo aumentou apenas 12.6 vezes (de 0.1ms para 1.3ms). Isso comprova na prática como o O(n log n) é muito mais escalável.

Sensibilidade ao Caso (RGM vs. Aleatório):

No caso rgm (N=8), todos os métodos foram quase instantâneos (abaixo de 0.001ms).

O Quick Sort foi o que usou menos passos (26) para ordenar o RGM. O Insertion Sort (34 passos) e o Bubble Sort (35 passos) ficaram muito próximos. Isso indica que o RGM "46008896" não estava "quase ordenado", e por isso o Insertion Sort não teve sua vantagem de "melhor caso" (O(n)) e rodou no seu caso médio (O(n²)), assim como o Bubble.

Conclusão (O "Melhor" Método):

Os dados mostram que não existe um "melhor" método, mas sim o "mais adequado" para cada cenário.

Para vetores pequenos (como o RGM N=8), a diferença de tempo é irrelevante, mas o Quick Sort já se mostrou ligeiramente mais eficiente em passos.

Para vetores grandes e aleatórios (N=10000), o Quick Sort é o vencedor indiscutível. Ele foi 57 vezes mais rápido que o Insertion Sort (1.3ms contra 74.8ms) e 148 vezes mais rápido que o Bubble Sort (1.3ms contra 193.5ms).

O Bubble Sort se mostrou o menos eficiente em todos os cenários de benchmark.
