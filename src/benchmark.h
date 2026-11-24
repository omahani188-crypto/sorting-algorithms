#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h>
#include "sorting.h"

#define MEASUREMENT_RUNS 5

typedef struct {
    const char *name;
    size_t size;
    double average_time_ms;
    double peak_memory_kb;
    int completed;
    int rank;
} BenchmarkResult;

int benchmark_algorithm(const SortAlgorithm *algorithm, const int *input,
                        size_t size, BenchmarkResult *result);

#endif
