#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "big_numbers.h"


int main() {
    char * first = calloc(201, 1);
    if (first == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    char * second = calloc(201, 1);
    if (second == NULL) {
        printf("Failed to allocate memory");
        free(first);
        return 8;
    }
    printf("Podaj pierwsza liczbe: ");
    if (scanf("%200s", first) != 1) {
        printf("Incorrect input");
        free(first);
        free(second);
        return 1;
    }
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    printf("Podaj druga liczbe: ");
    if (scanf("%200s", second) != 1) {
        printf("Incorrect input");
        free(first);
        free(second);
        return 1;
    }
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    char * result = NULL;
    int res = add(first, second, &result);
    if (res == 2) {
        printf("Incorrect input");
        free(first);
        free(second);
        return 1;
    }
    if (res == 3) {
        printf("Failed to allocate memory");
        free(first);
        free(second);
        return 8;
    }
    printf("%s\n", result);
    free(result);
    result = NULL;
    res = subtract(first, second, &result);
    if (res == 2) {
        printf("Incorrect input");
        free(first);
        free(second);
        free(result);
        return 1;
    }
    if (res == 3) {
        printf("Failed to allocate memory");
        free(first);
        free(second);
        free(result);
        return 8;
    }
    printf("%s", result);
    free(first);
    free(second);
    free(result);
    return 0;
}