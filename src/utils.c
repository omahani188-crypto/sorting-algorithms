#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int *create_array(size_t size)
{
    if (size > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    return malloc((size == 0 ? 1 : size) * sizeof(int));
}

void copy_array(int *destination, const int *source, size_t size)
{
    memcpy(destination, source, size * sizeof(int));
}

static int random_value(int limit)
{
    unsigned long value = ((unsigned long)rand() << 15) ^ (unsigned long)rand();
    return (int)(value % (unsigned long)limit);
}

void generate_array(int *array, size_t size, DataType type)
{
    size_t index;

    srand(RANDOM_SEED);
    for (index = 0; index < size; index++) {
        if (type == SORTED_DATA) {
            array[index] = (int)index;
        } else if (type == REVERSE_DATA) {
            array[index] = (int)(size - index);
        } else if (type == DUPLICATE_DATA) {
            array[index] = random_value(100);
        } else {
            array[index] = random_value(1000000);
        }
    }
}

int is_sorted(const int *array, size_t size)
{
    size_t index;
    for (index = 1; index < size; index++) {
        if (array[index - 1] > array[index]) {
            return 0;
        }
    }
    return 1;
}

const char *data_type_name(DataType type)
{
    if (type == RANDOM_DATA) return "Random";
    if (type == SORTED_DATA) return "Already sorted";
    if (type == REVERSE_DATA) return "Reverse sorted";
    return "Many duplicates";
}

int read_number(const char *prompt, long minimum, long maximum, long *value)
{
    char line[64];
    char *end;
    long number;

    for (;;) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            return -1;
        }
        errno = 0;
        number = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\n') {
            end++;
        }
        if (end != line && *end == '\0' && errno != ERANGE &&
            number >= minimum && number <= maximum) {
            *value = number;
            return 0;
        }
        printf("Invalid input. Enter a number from %ld to %ld.\n", minimum, maximum);
    }
}
