#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comparators.h"

int main() {
    typedef int (*comparator)(int, int);
    comparator * comparators = malloc(sizeof(comparator) * 4);
    if (comparators == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    *(comparators + 0) = &comp_int;
    *(comparators + 1) = &comp_int_abs;
    *(comparators + 2) = &comp_int_length;
    *(comparators + 3) = &comp_int_digits_sum;
    printf("zapodaj dlugosc tablicy: ");
    int amount;
    if (scanf("%d", &amount) != 1) {
        printf("Incorrect input");
        free(comparators);
        return 1;
    }
    if (amount <= 0) {
        printf("Incorrect input data");
        free(comparators);
        return 2;
    }
    int * tab = malloc(sizeof(int) * amount);
    if (tab == NULL) {
        printf("Failed to allocate memory");
        free(comparators);
        return 8;
    }
    printf("Zapodaj elementy");
    for (int i = 0; i < amount; ++i) {
        if (scanf("%d", (tab + i)) != 1) {
            printf("Incorrect input");
            free(comparators);
            free(tab);
            return 1;
        }
    }
    printf("zapodaj typ sortowania: ");
    int operation;
    if (scanf("%d", &operation) != 1) {
        printf("Incorrect input");
        free(comparators);
        free(tab);
        return 1;
    }
    if (operation < 0 || operation > 3) {
        printf("Incorrect input data");
        free(comparators);
        free(tab);
        return 2;
    }
    sort_int(tab, amount, *(comparators + operation));
    for (int i = 0; i < amount; ++i) {
        printf("%d ", *(tab + i));
    }
    free(tab);
    free(comparators);
    return 0;
}