#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

typedef int (*SortFunction)(int *array, size_t size);

typedef struct {
    const char *name;
    SortFunction function;
    int is_quadratic;
} SortAlgorithm;

#define ALGORITHM_COUNT 5

int bubble_sort(int *array, size_t size);
int selection_sort(int *array, size_t size);
int insertion_sort(int *array, size_t size);
int merge_sort(int *array, size_t size);
int quick_sort(int *array, size_t size);

extern const SortAlgorithm algorithms[ALGORITHM_COUNT];

#endif
