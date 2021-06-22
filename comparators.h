//
// Created by Mateusz Pysera on 27/05/2021.
//

#ifndef DANTE_P2_COMPARATORS_H
#define DANTE_P2_COMPARATORS_H

#include <stdio.h>
int sort_int(int * tab, int amount, int (*func)(int a, int b));
//int comp_int(int a, int b);
int comp_int_abs(int a, int b);
int comp_int_length(int a, int b);
int comp_int_digits_sum(int a, int b);
int count_digits(int num);
int sum_digits(int num);

struct point_t
{
    double x;
    double y;
};
void swap(char * ptr1, char * ptr2, size_t size);
int sort(void * tab, int amount, size_t size, int (*func)(const void *, const void *));
int comp_int(const void *ptr1, const void *ptr2);
int comp_double(const void *ptr1, const void *ptr2);
int comp_point(const void *ptr1, const void *ptr2);

#endif //DANTE_P2_COMPARATORS_H
