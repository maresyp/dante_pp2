#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

int stats(int *sum, float *avg, int num, ...) {
    if (sum == NULL || avg == NULL || num <= 0) return 1;
    va_list vaList;
    va_start(vaList, num);
    *sum = 0;
    for (int i = 0; i < num; ++i) {
        *sum += va_arg(vaList, int );
    }
    *avg = (float) *sum / (float) num;
    va_end(vaList);
    return 0;
}

int main() {
    printf("Zapodaj liczbe elemetow: ");
    int elem;
    if (scanf("%d", &elem) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (elem < 1 || elem > 3) {
        printf("Incorrect input data");
        return 2;
    }
    printf("Zapodaj liczby: ");
    int tab[3];
    for (int i = 0; i < elem; ++i) {
        if (scanf("%d", &tab[i]) != 1) {
            printf("Incorrect input");
            return 1;
        }
    }
    int sum; float avg;
    if (elem == 1) {
        stats(&sum, &avg, elem, tab[0]);
    }
    if (elem == 2) {
        stats(&sum, &avg, elem, tab[0], tab[1]);
    }
    if (elem == 3) {
        stats(&sum, &avg, elem, tab[0], tab[1], tab[2]);
    }
    printf("%d %f",sum, avg);
}