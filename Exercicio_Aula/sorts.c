#include "sorts.h"
#include <stdlib.h> 

// Implementação de reset_metrics
void reset_metrics(Metrics *m) {
    if (m) {
        m->steps_cmp = 0;
        m->steps_swap = 0;
    }
}

// --- 1. Bubble Sort ---
void bubble_sort(int *v, size_t n, Metrics *m) {
    if (n < 2) return;

    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            
            m->steps_cmp++; // Conta 1 comparação
            if (v[j] > v[j + 1]) {
                
                m->steps_swap++; 
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// --- 2. Insertion Sort ---
void insertion_sort(int *v, size_t n, Metrics *m) {
    if (n < 2) return;

    for (size_t i = 1; i < n; i++) {
        int key = v[i];
        m->steps_swap++; // Conta como 1 movimentação (pegar 'key')
        
        int j = i - 1;

        while (j >= 0) {
            m->steps_cmp++; // Conta a comparação
            if (v[j] > key) {
                v[j + 1] = v[j];
                m->steps_swap++; // Conta 1 movimentação (o "empurrão")
                j--;
            } else {
                break; // Achou a posição
            }
        }
        v[j + 1] = key;
        m->steps_swap++; // Conta 1 movimentação (colocar 'key' no lugar)
    }
}

// --- 3. Quick Sort (com funções auxiliares) ---

static void swap(int *a, int *b, Metrics *m) {
    m->steps_swap++; // Conta 1 "troca"
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition_lomuto(int *v, int low, int high, Metrics *m) {
    int pivo = v[high]; 
    int i = (low - 1);  

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

static void quick_sort_recursive(int *v, int low, int high, Metrics *m) {
    if (low < high) {
        int pi = partition_lomuto(v, low, high, m);
        quick_sort_recursive(v, low, pi - 1, m);
        quick_sort_recursive(v, pi + 1, high, m);
    }
}

void quick_sort(int *v, size_t n, Metrics *m) {
    if (n < 2) return;
    quick_sort_recursive(v, 0, n - 1, m);
}
