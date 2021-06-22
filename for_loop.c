//
// Created by Mateusz Pysera on 26/05/2021.
//

#include "for_loop.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static double prev = 0;
void for_loop(double start, double step, double stop, void (*func)(double value)) {
    if (step == 0 || func == NULL) return;
    if ((start >= stop && step > 0) || ( start <= stop && step < 0)) return;
    (*func)(start);
    for_loop(start + step, step, stop, func);
}
void print_value(double value) {
    printf("%f ", value);
}
void print_accumulated(double value) {
    printf("%f ", prev + value);
    prev += value;
}
void print_square(double value) {
    printf("%f ", pow(value, 2));
}
void print_abs(double value) {
    printf("%f ", fabs(value));
}