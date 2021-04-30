//
// Created by Mateusz Pysera on 25/04/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "array.h"

int array_create(struct array_t *a, int N) {
    if(a == NULL || N <= 0) return 1;
    a->ptr = malloc(sizeof(int ) * N);
    if (a->ptr == NULL) return 2;
    a->size = 0;
    a->capacity = N;
    return 0;
}

int array_push_back(struct array_t *a, int value) {
    if (a == NULL || a->capacity <= 0 || a->size < 0 || a->size > a->capacity) return 1;
    if (a->size >= a->capacity) {
        int *p = realloc(a->ptr, sizeof(int ) * (a->capacity * 2));
        if (p != NULL) {
            a->ptr = p;
            a->capacity *= 2;
        } else {
            return 2;
        }
    }
    *(a->ptr + a->size) = value;
    a->size++;
    return 0;
}

void array_destroy(struct array_t *a) {
    if (a == NULL) return;
    free(a->ptr);
}

void array_display(const struct array_t *a) {
    if (a == NULL || a->size <= 0 || a->capacity <= 0 || a->ptr == NULL || a->size > a->capacity) return;
    for (int i = 0; i < a->size; ++i) {
        printf("%d ", *(a->ptr + i));
    }
}

int array_create_struct(struct array_t **a, int N) {
    if (a == NULL || N <= 0) return 1;

    struct array_t *array_p = malloc(sizeof(struct array_t));
    if (array_p == NULL) return 2;

    int res = array_create(array_p, N);
    if (res != 0) {
        free(array_p);
        return res;
    }

    *a = array_p;
    return 0;
}

void array_destroy_struct(struct array_t **a) {
    if (a == NULL || *a == NULL) return;
    free((*a)->ptr);
    free(*a);
    *a = NULL;
}

int array_remove_item(struct array_t *a, int value) {
    if (a == NULL || a->size < 0 || a->capacity <= 0 || a->ptr == NULL || a->size > a->capacity) return -1;
    int elements_removed = 0;
    for (int i = 0; i < a->size; ++i) {
        if (*(a->ptr + i) == value) {
            for (int j = i; j < a->size; ++j) {
                *(a->ptr + j) = *(a->ptr + j + 1);
            }
            a->size--; i--;
            elements_removed++;
        }
    }
    float percentage;
    percentage = ((float)a->size / (float)a->capacity) * 100;
    if (percentage < 25) {
        if (a->capacity >= 2) {
            int *p = realloc(a->ptr, sizeof(int) * (a->capacity / 2));
            if (p != NULL) {
                a->ptr = p;
                a->capacity /= 2;
            }
        }
    }
    return elements_removed;
}