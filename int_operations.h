//
// Created by Mateusz Pysera on 26/05/2021.
//

#ifndef DANTE_PP2_INT_OPERATIONS_H
#define DANTE_PP2_INT_OPERATIONS_H

enum operations_t {
    op_add = 0,
    op_sub = 1,
    op_div = 2,
    op_mul = 3
};
int add_int(int a, int b);
int sub_int(int a, int b);
int div_int(int a, int b);
int mul_int(int a, int b);

typedef int (*calc)(int, int);
int calculate(int first, int second, int (*func)(int first, int second));
calc get_function(enum operations_t operation);

#endif //DANTE_PP2_INT_OPERATIONS_H
