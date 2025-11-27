#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sorts.h" //arquivo .h

#define N_RUNS 5              // Rodar 5x para tirar a média

// Tamanhos dos vetores aleatórios 
const size_t SIZES[] = {100, 1000, 10000};
const int N_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

// --- Funções Auxiliares ---

size_t rgm_to_array(const char* rgm_str, int **out_array) {
    size_t n = strlen(rgm_str);
    *out_array = (int*)malloc(n * sizeof(int));
    if (*out_array == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para o RGM\n");
        exit(1);
    }
    for (size_t i = 0; i < n; i++) {
        (*out_array)[i] = rgm_str[i] - '0'; // Converte char '9' para int 9
    }
    return n;
}

// Gera um vetor aleatório de tamanho 'n'.

int* create_random_array(size_t n) {
    int* v = (int*)malloc(n * sizeof(int));
    if (v == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para vetor aleatorio\n");
        exit(1);
    }
    for (size_t i = 0; i < n; i++) {
        v[i] = rand() % (n * 10); // Números aleatórios de 0 a 10*N
    }
    return v;
}

// Cria uma cópia de um vetor, pois a ordenação destrói o original.

int* copy_array(int* v, size_t n) {
    int* c = (int*)malloc(n * sizeof(int));
    if (c == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para copia\n");
        exit(1);
    }
    memcpy(c, v, n * sizeof(int));
    return c;
}

// --- Estruturas para rodar os testes ---

// Ponteiro para uma função de ordenação (ex: bubble_sort, quick_sort)
typedef void (*SortFunction)(int*, size_t, Metrics*);

// Estrutura para guardar o nome e a função de cada algoritmo
typedef struct {
    SortFunction fn;
    const char* name;
} SortAlgorithm;

double run_sort(SortFunction fn, int *v, size_t n, Metrics *m) {
    reset_metrics(m);
    clock_t t0 = clock();
    fn(v, n, m); // Executa a ordenação (e destrói 'v')
    clock_t t1 = clock();
    return 1000.0 * (t1 - t0) / CLOCKS_PER_SEC;
}


// --- Função Principal ---
int main() {
    // --- Variável para guardar o RGM ---
    char rgm_input_string[50]; // Um buffer para 50 chars (seguro)

    // --- Pedir o RGM ao usuário ---
    printf("Digite o seu RGM (apenas digitos): ");
    scanf("%49s", rgm_input_string); // Lê a string (limite de 49 p/ segurança)

    // Define os 3 algoritmos para testar
    SortAlgorithm algos[] = {
        {bubble_sort, "bubble"},
        {insertion_sort, "insertion"},
        {quick_sort, "quick"}
    };
    int n_algos = sizeof(algos) / sizeof(algos[0]);

    // Inicializa o gerador aleatório
    srand(time(NULL));

    // Imprime o cabeçalho do CSV 
    // "passos" será a SOMA de 'steps_cmp' e 'steps_swap'
    printf("metodo,N,caso,passos,tempo_ms\n");

    // --- Teste do RGM ---
    int* rgm_original_array = NULL;
    size_t rgm_n = rgm_to_array(rgm_input_string, &rgm_original_array);
    
    for (int t = 0; t < n_algos; t++) {
        double total_time_ms = 0;
        long long total_cmp = 0;
        long long total_swap = 0;
        
        // Roda N_RUNS (5) vezes para tirar a média
        for (int i = 0; i < N_RUNS; i++) {
            // Cria uma cópia, pois o RGM original não pode ser modificado
            int *v_copy = copy_array(rgm_original_array, rgm_n);
            Metrics m;
            total_time_ms += run_sort(algos[t].fn, v_copy, rgm_n, &m);
            total_cmp += m.steps_cmp;
            total_swap += m.steps_swap;
            free(v_copy); // Libera a cópia
        }
        
        // Calcula as médias
        double avg_time_ms = total_time_ms / N_RUNS;
        long long avg_passos = (total_cmp / N_RUNS) + (total_swap / N_RUNS);
        
        printf("%s,%zu,rgm,%lld,%.4f\n",
               algos[t].name, rgm_n, avg_passos, avg_time_ms);
    }
    
    // --- Testes de Benchmark (Aleatório) ---
    for (int s = 0; s < N_SIZES; s++) {
        size_t N = SIZES[s];
        
        for (int t = 0; t < n_algos; t++) {
            double total_time_ms = 0;
            long long total_cmp = 0;
            long long total_swap = 0;
            
            // Roda N_RUNS (5) vezes para tirar a média
            for (int i = 0; i < N_RUNS; i++) {
                // Gera um NOVO vetor aleatório a CADA execução
                int* v_rand = create_random_array(N);
                Metrics m;
                total_time_ms += run_sort(algos[t].fn, v_rand, N, &m);
                total_cmp += m.steps_cmp;
                total_swap += m.steps_swap;
                free(v_rand); // Libera o vetor (que foi ordenado/destruído)
            }
            
            // Calcula as médias
            double avg_time_ms = total_time_ms / N_RUNS;
            long long avg_passos = (total_cmp / N_RUNS) + (total_swap / N_RUNS);

            printf("%s,%zu,aleatorio,%lld,%.4f\n",
                   algos[t].name, N, avg_passos, avg_time_ms);
        }
    }
    
    free(rgm_original_array); // Libera o RGM original no final
    return 0;
}
