#include "sorts.h"
#include <stdlib.h> 

// Implementação de reset_metrics
void reset_metrics(Metrics *m) {
    if (m) {
        m->steps_cmp = 0;
        m->steps_swap = 0;
    }
}

// --- Bubble Sort ---
void bubble_sort(int *v, size_t n, Metrics *m) {
    if (n < 2) return;

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            
            m->steps_cmp++; // Conta 1 comparação
            if (v[j] > v[j + 1]) {
                
                // 'swap' conta como 1 "troca" 
                m->steps_swap++; 
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// --- Insertion Sort ---
void insertion_sort(int *v, size_t n, Metrics *m) {
    if (n < 2) return;

    for (size_t i = 1; i < n; i++) {
        int key = v[i];
        m->steps_swap++; // Conta como 1 movimentação 
        
        int j = i - 1;

        // Compara e "empurra"
        while (j >= 0) {
            m->steps_cmp++; // Conta a comparação
            if (v[j] > key) {
                v[j + 1] = v[j];
                m->steps_swap++; // Conta 1 movimentação 
                j--;
            } else {
                break; // Achou a posição
            }
        }
        v[j + 1] = key;
        m->steps_swap++; // Conta 1 movimentação 
    }
}

// --- Quick Sort (com funções auxiliares) ---

// Função auxiliar 'swap' que registra a métrica
static void swap(int *a, int *b, Metrics *m) {
    m->steps_swap++; // Conta 1 "troca"
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partição Lomuto 
static int partition_lomuto(int *v, int low, int high, Metrics *m) {
    int pivo = v[high]; // Pivô é o último elemento
    int i = (low - 1);  // Índice do menor elemento

    for (int j = low; j < high; j++) {
        m->steps_cmp++; // Conta a comparação com o pivô
        if (v[j] < pivo) {
            i++;
            swap(&v[i], &v[j], m); // Troca
        }
    }
    swap(&v[i + 1], &v[high], m); // Coloca o pivô no lugar
    return (i + 1);
}

// Função recursiva principal
static void quick_sort_recursive(int *v, int low, int high, Metrics *m) {
    if (low < high) {
        int pi = partition_lomuto(v, low, high, m);
        quick_sort_recursive(v, low, pi - 1, m);
        quick_sort_recursive(v, pi + 1, high, m);
    }
}

// Função "wrapper" (a que o 'main' chama)
void quick_sort(int *v, size_t n, Metrics *m) {
    if (n < 2) return;
    quick_sort_recursive(v, 0, n - 1, m);
}
