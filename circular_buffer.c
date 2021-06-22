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
    a->begin = 0;
    a->end = 0;
    a->full = 0;
    return 0;
}
void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL) return;
    free(a->ptr);
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N <= 0) return 1;
    struct circular_buffer_t *circularBuffer = malloc(sizeof(struct circular_buffer_t));
    if (circularBuffer == NULL) return 2;

    int res = circular_buffer_create(circularBuffer, N);
    if (res != 0) {
        free(circularBuffer);
        return res;
    }
    *cb = circularBuffer;
    return 0;
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL || *a == NULL) return;
    free((*a)->ptr);
    free(*a);
    *a = NULL;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (cb == NULL || cb->ptr == NULL || cb->capacity <= 0 || cb->end > cb->capacity || cb->begin > cb->capacity || cb->end < 0 || cb->begin < 0) return 1;

    // if buffer is not full
    if (circular_buffer_full(cb) == 0) {
        *(cb->ptr + cb->end) = value;
        cb->end++;
        if (cb->end >= cb->capacity) {
            cb->end = 0;
        }
        if (cb->end == cb->begin) {
            cb->full = 1;
        }
    } else {
//        // buffer is already full
//        if (cb->end >= cb->capacity) cb->end = 0;
//        if (cb->begin >= cb->capacity) cb->begin = 0;

        *(cb->ptr + cb->end) = value;
        cb->begin++;
        if (cb->begin >= cb->capacity) {
            cb->begin = 0;
        }
        cb->end = cb->begin;
    }
    return 0;
}
int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (err_code != NULL) *err_code = 0;
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity || a->end < 0 || a->begin < 0) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }
    if (circular_buffer_empty(a) == 1) {
        if (err_code != NULL) *err_code = 2;
        return -1;
    }
    if (err_code != NULL)
        if (*err_code != 0)
            return -1;

    int value = *(a->ptr + a->begin);
    a->begin++;
    if (a->begin >= a->capacity) a->begin = 0;
    if (a->full == 1) a->full = 0;
    return value;
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    // return end - 1 element
    if (err_code != NULL) *err_code = 0;
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity || a->end < 0 || a->begin < 0) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return -1;
    }
    if (circular_buffer_empty(a) == 1) {
        if (err_code != NULL) *err_code = 2;
        return -1;
    }
    if (err_code != NULL)
        if (*err_code != 0)
            return -1;

    if (a->full == 1) a->full = 0;
    if (a->end <= 0) {
        a->end = a->capacity - 1;
        return *(a->ptr + a->capacity - 1);
    }
    a->end--;
    return *(a->ptr + a->end);
}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity || a->end < 0 || a->begin < 0) return -1;
    if (a->end == a->begin && circular_buffer_full(a) == 0) return 1;
    return 0;
}
int circular_buffer_full(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end > a->capacity || a->begin > a->capacity || a->end < 0 || a->begin < 0) return -1;
    if (a->full == 1) return 1;
    return 0;
}
void circular_buffer_display(const struct circular_buffer_t *a) {
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->end >= a->capacity || a->begin >= a->capacity || a->end < 0 || a->begin < 0 || circular_buffer_empty(a)) return;
    int start = a->begin;
    if (a->full == 1) printf("%d ", *(a->ptr + start++));
    if (start >= a->capacity) start = 0;
    while (start != a->end) {
        printf("%d ", *(a->ptr + start));
        start++;
        if (start >= a->capacity) start = 0;
    }
}
