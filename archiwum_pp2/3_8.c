#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "array.h"

int main() {
    printf("Zapodaj pojemnosc tablicy: ");
    int tab_size;
    if (scanf("%d", &tab_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (tab_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }

    struct array_t *array;
    int res = array_create_struct(&array, tab_size);
    if (res == 2) {
        printf("Failed to allocate memory");
        array_destroy_struct(&array);
        return 8;
    }
    int operation;
    do {
        printf("Co chcesz zrobić ");
        if (scanf("%d", &operation) != 1) {
            printf("Incorrect input");
            array_destroy_struct(&array);
            return 1;
        }
        if (operation > 2 || operation < 0) {
            printf("Incorrect input data\n");
            continue;
        }
        if (operation == 1) {
            int value;
            printf("Zapodaj liczby: ");
            do {
                if (scanf("%d", &value) != 1) {
                    printf("Incorrect input");
                    array_destroy_struct(&array);
                    return 1;
                } else {
                    if (value == 0) break;
                }
                res = array_push_back(array, value);
            } while (res != 2);
            if (res == 2) {
                printf("Buffer is full\n");
            }
            if (array->size == 0) {
                printf("Buffer is empty\n");
            } else {
                array_display(array);
                printf("\n");
            }
        }
        if (operation == 2) {
            printf("Podaj kolejne liczby, które mają zostać usuniete z tablicy: ");
            int val;
            char tmp;
            do {
                if (scanf("%d%c", &val, &tmp) != 2) {
                    printf("Incorrect input");
                    array_destroy_struct(&array);
                    return 1;
                }
                array_remove_item(array, val);
            } while (tmp != '\n');

            if (array->size == 0) {
                printf("Buffer is empty\n");
            } else {
                array_display(array);
                printf("\n");
            }
        }

    } while (operation != 0);
    array_destroy_struct(&array);
    return 0;
}