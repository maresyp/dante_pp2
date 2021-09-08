#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "for_loop.h"

int main() {
    printf("Zapodaj start step stop");
    double start, step, end;
    if (scanf("%lf %lf %lf", &start, &step, &end) != 3) {
        printf("Incorrect input");
        return 1;
    }
    if (step == 0) {
        printf("Incorrect input data");
        return 2;
    }
    if (step < 0 && end > 0 || step > 0 && end < 0) {
        printf("Incorrect input data");
        return 2;
    }
    printf("Zapodaj operacje: ");
    int operation;
    if (scanf("%d", &operation) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (operation < 0 || operation > 3) {
        printf("Incorrect input data");
        return 2;
    }
    void (*funcs[])(double ) = {print_value, print_accumulated, print_square, print_abs};
    for_loop(start, step,end, *(funcs + operation));
}