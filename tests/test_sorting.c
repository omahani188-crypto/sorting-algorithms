#include <stdio.h>
#include <stdlib.h>
#include "../src/sorting.h"
#include "../src/utils.h"

static int test_algorithm(const SortAlgorithm *algorithm, const int *source, size_t size)
{
    int *copy = create_array(size);
    int passed;
    if (copy == NULL) return 0;
    copy_array(copy, source, size);
    passed = algorithm->function(copy, size) == 0 && is_sorted(copy, size);
    free(copy);
    return passed;
}

int main(void)
{
    const int values[] = {5, -2, 8, 1, 1, 0, 9, -7};
    const int reverse[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int index;
    int failed = 0;
    for (index = 0; index < ALGORITHM_COUNT; index++) {
        int first = test_algorithm(&algorithms[index], values, sizeof(values) / sizeof(values[0]));
        int second = test_algorithm(&algorithms[index], reverse, sizeof(reverse) / sizeof(reverse[0]));
        printf("%s: %s\n", algorithms[index].name, first && second ? "passed" : "failed");
        if (!first || !second) failed++;
    }
    return failed == 0 ? 0 : 1;
}
