//
// Created by Mateusz Pysera on 03/04/2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N <= 0) return 1;
    a->ptr = malloc(sizeof(int) * N);
    if (a->ptr == NULL) return 2;

    a->capacity = N;
    a->begin = -1;
    a->end = 0;
    a->full = 0;
    return 0;
}
void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL) return;
    free(a);
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N <= 0) return 1;
    cb = malloc(sizeof(struct circular_buffer_t));
    if (cb == NULL) return 2;
    int res = circular_buffer_create((struct circular_buffer_t *) cb, N);
    if (res == 2) {
        circular_buffer_destroy((struct circular_buffer_t *) cb);
        return 2;
    }
    return 0;
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    return;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    return 0;
}
int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    return 0;
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    return 0;
}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    return 0;
}
int circular_buffer_full(const struct circular_buffer_t *a) {
    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    return;
}