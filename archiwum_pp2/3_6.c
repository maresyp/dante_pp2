#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

int main() {
    printf("Zapodaj rozmiar tablicy: ");
    int tab_size;
    if (scanf("%d", &tab_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (tab_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct array_t array;
    int res = array_create(&array, tab_size);
    if (res == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    int value;
    printf("Zapodaj liczby: \n");
    do {
        if (scanf("%d", &value) != 1) {
            printf("Incorrect input");
            array_destroy(&array);
            return 1;
        } else {
            if (value == 0) break;
        }
        res = array_push_back(&array, value);
    } while (res != 2);
    if (res == 2) {
        printf("Buffer is full\n");
    }
    if (array.size == 0) {
        printf("Buffer is empty");
    } else {
        array_display(&array);
    }
    array_destroy(&array);
    return 0;
}