#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "benchmark.h"
#include "sorting.h"
#include "utils.h"

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

#define QUADRATIC_LIMIT 10000
#define RESULT_COUNT 25

static const size_t comparison_sizes[] = {1000, 5000, 10000, 50000, 100000};

static void print_menu(void)
{
    printf("\n=========== SORTING ALGORITHMS ===========\n");
    printf("1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n");
    printf("4. Merge Sort\n5. Quick Sort\n6. Compare all algorithms\n0. Exit\n");
}

static int choose_data_type(DataType *type)
{
    long choice;
    printf("\nInput type:\n1. Random\n2. Already sorted\n3. Reverse sorted\n4. Many duplicates\n");
    if (read_number("Your choice: ", 1, 4, &choice) != 0) {
        return -1;
    }
    *type = (DataType)choice;
    return 0;
}

static void assign_ranks(BenchmarkResult *results, int count)
{
    int first;
    for (first = 0; first < count; first++) {
        int second;
        if (!results[first].completed) continue;
        results[first].rank = 1;
        for (second = 0; second < count; second++) {
            if (results[second].completed &&
                results[second].average_time_ms < results[first].average_time_ms) {
                results[first].rank++;
            }
        }
    }
}

static void print_results(const BenchmarkResult *results, int count)
{
    int index;
    printf("\n%-16s | %-10s | %-17s | %-16s | %s\n",
           "Algorithm", "Array size", "Average time (ms)", "Peak memory (KB)", "Rank");
    printf("-----------------+------------+-------------------+------------------+------\n");
    for (index = 0; index < count; index++) {
        if (results[index].completed) {
            printf("%-16s | %-10lu | %-17.3f | %-16.0f | %d\n", results[index].name,
                   (unsigned long)results[index].size, results[index].average_time_ms,
                   results[index].peak_memory_kb, results[index].rank);
        } else {
            printf("%-16s | %-10lu | %-17s | %-16s | -\n", results[index].name,
                   (unsigned long)results[index].size, "Skipped", "Skipped");
        }
    }
}

static void create_results_folder(void)
{
#ifdef _WIN32
    _mkdir("results");
#else
    mkdir("results", 0755);
#endif
}

static void save_csv(const BenchmarkResult *results, int count)
{
    FILE *file;
    int index;

    create_results_folder();
    file = fopen("results/benchmark_results.csv", "w");
    if (file == NULL) {
        printf("Could not create results/benchmark_results.csv\n");
        return;
    }
    fprintf(file, "Algorithm,Array Size,Average Time (ms),Peak Memory (KB),Rank\n");
    for (index = 0; index < count; index++) {
        if (results[index].completed) {
            fprintf(file, "%s,%lu,%.3f,%.0f,%d\n", results[index].name,
                    (unsigned long)results[index].size, results[index].average_time_ms,
                    results[index].peak_memory_kb, results[index].rank);
        } else {
            fprintf(file, "%s,%lu,Skipped,Skipped,-\n", results[index].name,
                    (unsigned long)results[index].size);
        }
    }
    fclose(file);
    printf("\nResults saved in results/benchmark_results.csv\n");
}

static void run_one_algorithm(int algorithm_index)
{
    long size_choice;
    size_t size;
    DataType type;
    int *input;
    BenchmarkResult result;

    printf("\n1. 1000\n2. 5000\n3. 10000\n4. 100000\n");
    if (read_number("Array size: ", 1, 4, &size_choice) != 0 ||
        choose_data_type(&type) != 0) return;
    size = size_choice == 1 ? 1000 : size_choice == 2 ? 5000 :
           size_choice == 3 ? 10000 : 100000;
    if (algorithms[algorithm_index].is_quadratic && size > QUADRATIC_LIMIT) {
        printf("This O(n^2) algorithm is limited to 10000 elements.\n");
        size = QUADRATIC_LIMIT;
    }
    input = create_array(size);
    if (input == NULL) {
        printf("Not enough memory.\n");
        return;
    }
    generate_array(input, size, type);
    if (benchmark_algorithm(&algorithms[algorithm_index], input, size, &result) == 0) {
        printf("\n%s: %.3f ms, peak memory %.0f KB (average of %d runs)\n",
               result.name, result.average_time_ms, result.peak_memory_kb, MEASUREMENT_RUNS);
    } else {
        printf("The test could not be completed.\n");
    }
    free(input);
}

static void compare_all(void)
{
    BenchmarkResult results[RESULT_COUNT];
    DataType type;
    int count = 0;
    size_t size_index;

    if (choose_data_type(&type) != 0) return;
    printf("\nEach measurement is repeated %d times.\n", MEASUREMENT_RUNS);
    for (size_index = 0; size_index < sizeof(comparison_sizes) / sizeof(comparison_sizes[0]); size_index++) {
        size_t size = comparison_sizes[size_index];
        int *input = create_array(size);
        int algorithm_index;
        if (input == NULL) {
            printf("Not enough memory for %lu elements.\n", (unsigned long)size);
            return;
        }
        generate_array(input, size, type);
        printf("Testing %lu elements...\n", (unsigned long)size);
        for (algorithm_index = 0; algorithm_index < ALGORITHM_COUNT; algorithm_index++) {
            BenchmarkResult *result = &results[count++];
            memset(result, 0, sizeof(*result));
            result->name = algorithms[algorithm_index].name;
            result->size = size;
            if (algorithms[algorithm_index].is_quadratic && size > QUADRATIC_LIMIT) {
                continue;
            }
            if (benchmark_algorithm(&algorithms[algorithm_index], input, size, result) != 0) {
                result->completed = 0;
            }
        }
        assign_ranks(&results[count - ALGORITHM_COUNT], ALGORITHM_COUNT);
        free(input);
    }
    printf("\nInput: %s data. Seed: %u.\n", data_type_name(type), RANDOM_SEED);
    print_results(results, count);
    save_csv(results, count);
}

int main(void)
{
    long choice;
    for (;;) {
        print_menu();
        if (read_number("Your choice: ", 0, 6, &choice) != 0 || choice == 0) {
            break;
        }
        if (choice >= 1 && choice <= 5) run_one_algorithm((int)choice - 1);
        else compare_all();
    }
    return 0;
}
