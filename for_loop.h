//
// Created by Mateusz Pysera on 26/05/2021.
//

#ifndef DANTE_P2_FOR_LOOP_H
#define DANTE_P2_FOR_LOOP_H

void for_loop(double start, double step, double stop, void (*func)(double value));
void print_value(double value);
void print_accumulated(double value);
void print_square(double value);
void print_abs(double value);

#endif //DANTE_P2_FOR_LOOP_H
