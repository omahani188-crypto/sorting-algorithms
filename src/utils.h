#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define RANDOM_SEED 42u

typedef enum {
    RANDOM_DATA = 1,
    SORTED_DATA,
    REVERSE_DATA,
    DUPLICATE_DATA
} DataType;

int *create_array(size_t size);
void copy_array(int *destination, const int *source, size_t size);
void generate_array(int *array, size_t size, DataType type);
int is_sorted(const int *array, size_t size);
const char *data_type_name(DataType type);
int read_number(const char *prompt, long minimum, long maximum, long *value);

#endif
