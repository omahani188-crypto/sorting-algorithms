#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include "benchmark.h"
#include "utils.h"

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#include <time.h>
#endif

static double current_time_ms(void)
{
#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1000.0 / (double)frequency.QuadPart;
#else
    struct timespec time_value;
    clock_gettime(CLOCK_MONOTONIC, &time_value);
    return (double)time_value.tv_sec * 1000.0 + (double)time_value.tv_nsec / 1000000.0;
#endif
}

static double peak_memory_kb(void)
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS counters;
    counters.cb = sizeof(counters);
    if (!GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters))) {
        return 0.0;
    }
    return (double)counters.PeakWorkingSetSize / 1024.0;
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) != 0) {
        return 0.0;
    }
#ifdef __APPLE__
    return (double)usage.ru_maxrss / 1024.0;
#else
    return (double)usage.ru_maxrss;
#endif
#endif
}

int benchmark_algorithm(const SortAlgorithm *algorithm, const int *input,
                        size_t size, BenchmarkResult *result)
{
    int *copy = create_array(size);
    double total_time = 0.0;
    double largest_memory = 0.0;
    int run;

    if (copy == NULL) {
        return -1;
    }
    for (run = 0; run < MEASUREMENT_RUNS; run++) {
        double start;
        double end;
        double memory;

        copy_array(copy, input, size);
        start = current_time_ms();
        if (algorithm->function(copy, size) != 0 || !is_sorted(copy, size)) {
            free(copy);
            return -1;
        }
        end = current_time_ms();
        memory = peak_memory_kb();
        total_time += end - start;
        if (memory > largest_memory) {
            largest_memory = memory;
        }
    }
    free(copy);
    result->name = algorithm->name;
    result->size = size;
    result->average_time_ms = total_time / MEASUREMENT_RUNS;
    result->peak_memory_kb = largest_memory;
    result->completed = 1;
    result->rank = 0;
    return 0;
}
