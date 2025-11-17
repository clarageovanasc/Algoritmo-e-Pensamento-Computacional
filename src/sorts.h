#ifndef SORTS_H
#define SORTS_H

#include <stddef.h> 

typedef struct {
    long long steps_cmp;  
    long long steps_swap;
} Metrics;

void reset_metrics(Metrics *m);

void bubble_sort(int *v, size_t n, Metrics *m);

void insertion_sort(int *v, size_t n, Metrics *m);

void quick_sort(int *v, size_t n, Metrics *m);

#endif // SORTS_H
