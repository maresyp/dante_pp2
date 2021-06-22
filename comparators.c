//
// Created by Mateusz Pysera on 27/05/2021.
//

#include "comparators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int sort_int(int * tab, int amount, int (*func)(int a, int b)) {
    if (func == NULL || tab == NULL || amount <= 0) return 1;
    for (int i = 0; i < amount - 1; ++i) {
        for (int j = 0; j < amount - i - 1; ++j) {
            if ((*func)(*(tab + j), *(tab + j + 1)) > 0) {
                int tmp;
                tmp = *(tab + j);
                *(tab + j) = *(tab + j + 1);
                *(tab + j + 1) = tmp;
            }
        }
    }
    return 0;
}
int comp_int_abs(int a, int b) {
    if (abs(a) < abs(b)) return -1;
    if (abs(a) > abs(b)) return 1;
    return 0;
}
int count_digits(int num) {
    int counter = 0;
    while (num != 0) {
        num = num / 10;
        counter++;
    }
    return counter;
}
int comp_int_length(int a, int b) {
    if (count_digits(a) < count_digits(b)) return -1;
    if (count_digits(a) > count_digits(b)) return 1;
    return 0;
}
int sum_digits(int num) {
    int sum = 0;
    while (num > 0) {
        int tmp = num % 10;
        sum += tmp;
        num = num / 10;
    }
    return sum;
}
int comp_int_digits_sum(int a, int b) {
    if (sum_digits(abs(a)) < sum_digits(abs(b))) return -1;
    if (sum_digits(abs(a)) > sum_digits(abs(b))) return 1;
    return 0;
}

void swap(char * a, char * b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        char tmp = *a;
        *a = *b;
        *b = tmp;
        a++;
        b++;
    }
}
int sort(void * tab, int amount, size_t size, int (*func)(const void *, const void *)) {
    if (tab == NULL || amount <= 0 || size <= 0 || func == NULL) return 1;
    for (int i = 0; i < amount - 1; ++i) {
        for (int j = 0; j < amount - i - 1; ++j) {
            if ((*func)(((char *)tab + (size * j)), (char *)tab + (size * (j + 1))) > 0) {
                swap(((char *)tab + (size * j)), ((char *)tab + (size * (j + 1))), size);
            }
        }
    }
    return 0;
}
int comp_int(const void *ptr1, const void *ptr2) {
    if (ptr1 == NULL || ptr2 == NULL) return 0;
    if (*((int *)(ptr1)) < *((int *)(ptr2))) return -1;
    if (*((int *)(ptr1)) > *((int *)(ptr2))) return 1;
    return 0;
}
int comp_double(const void *ptr1, const void *ptr2) {
    if (ptr1 == NULL || ptr2 == NULL) return 0;

    if (*(double *)(ptr1) < *((double *)(ptr2))) return -1;
    if (*(double *)(ptr1) > *((double *)(ptr2))) return 1;
    return 0;
}
int comp_point(const void *ptr1, const void *ptr2) {
    if (ptr1 == NULL || ptr2 == NULL) return 0;
    if (((struct point_t *)(ptr1))->x == ((struct point_t *)(ptr2))->x) {
        if (((struct point_t *)(ptr1))->y > ((struct point_t *)(ptr2))->y) return 1;
        if (((struct point_t *)(ptr1))->y < ((struct point_t *)(ptr2))->y) return -1;
    } else {
        if (((struct point_t *)(ptr1))->x > ((struct point_t *)(ptr2))->x) return 1;
        if (((struct point_t *)(ptr1))->x < ((struct point_t *)(ptr2))->x) return -1;
    }
    return 0;
//    double ans = ((struct point_t *)(ptr1))->x - ((struct point_t *)(ptr2))->x;
//    if (ans == 0) ans = ((struct point_t *)(ptr1))->y - ((struct point_t *)(ptr2))->y;
//    return (int)ans;
}