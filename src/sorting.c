#include <stdlib.h>
#include "sorting.h"

static void swap(int *first, int *second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

int bubble_sort(int *array, size_t size)
{
    size_t pass;

    for (pass = 0; pass + 1 < size; pass++) {
        size_t index;
        int swapped = 0;

        for (index = 0; index + 1 < size - pass; index++) {
            if (array[index] > array[index + 1]) {
                swap(&array[index], &array[index + 1]);
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
    return 0;
}

int selection_sort(int *array, size_t size)
{
    size_t index;

    for (index = 0; index + 1 < size; index++) {
        size_t minimum = index;
        size_t next;

        for (next = index + 1; next < size; next++) {
            if (array[next] < array[minimum]) {
                minimum = next;
            }
        }
        if (minimum != index) {
            swap(&array[index], &array[minimum]);
        }
    }
    return 0;
}

int insertion_sort(int *array, size_t size)
{
    size_t index;

    for (index = 1; index < size; index++) {
        int value = array[index];
        size_t position = index;

        while (position > 0 && array[position - 1] > value) {
            array[position] = array[position - 1];
            position--;
        }
        array[position] = value;
    }
    return 0;
}

static void merge_parts(int *array, int *temporary, size_t left,
                        size_t middle, size_t right)
{
    size_t first = left;
    size_t second = middle;
    size_t target = left;

    while (first < middle && second < right) {
        if (array[first] <= array[second]) {
            temporary[target++] = array[first++];
        } else {
            temporary[target++] = array[second++];
        }
    }
    while (first < middle) {
        temporary[target++] = array[first++];
    }
    while (second < right) {
        temporary[target++] = array[second++];
    }
    while (left < right) {
        array[left] = temporary[left];
        left++;
    }
}

static void merge_sort_recursive(int *array, int *temporary,
                                 size_t left, size_t right)
{
    size_t middle;

    if (right - left < 2) {
        return;
    }
    middle = left + (right - left) / 2;
    merge_sort_recursive(array, temporary, left, middle);
    merge_sort_recursive(array, temporary, middle, right);
    merge_parts(array, temporary, left, middle, right);
}

int merge_sort(int *array, size_t size)
{
    int *temporary;

    if (size < 2) {
        return 0;
    }
    temporary = malloc(size * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }
    merge_sort_recursive(array, temporary, 0, size);
    free(temporary);
    return 0;
}

static int median_of_three(int *array, long low, long high)
{
    long middle = low + (high - low) / 2;

    if (array[middle] < array[low]) swap(&array[middle], &array[low]);
    if (array[high] < array[low]) swap(&array[high], &array[low]);
    if (array[high] < array[middle]) swap(&array[high], &array[middle]);
    return array[middle];
}

static void quick_sort_range(int *array, long low, long high)
{
    while (low < high) {
        int pivot = median_of_three(array, low, high);
        long left = low;
        long right = high;

        while (left <= right) {
            while (array[left] < pivot) left++;
            while (array[right] > pivot) right--;
            if (left <= right) {
                swap(&array[left], &array[right]);
                left++;
                right--;
            }
        }
        if (right - low < high - left) {
            if (low < right) quick_sort_range(array, low, right);
            low = left;
        } else {
            if (left < high) quick_sort_range(array, left, high);
            high = right;
        }
    }
}

int quick_sort(int *array, size_t size)
{
    if (size > 1) {
        quick_sort_range(array, 0, (long)size - 1);
    }
    return 0;
}

const SortAlgorithm algorithms[ALGORITHM_COUNT] = {
    { "Bubble Sort", bubble_sort, 1 },
    { "Selection Sort", selection_sort, 1 },
    { "Insertion Sort", insertion_sort, 1 },
    { "Merge Sort", merge_sort, 0 },
    { "Quick Sort", quick_sort, 0 }
};
