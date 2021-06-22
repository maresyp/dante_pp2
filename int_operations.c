//
// Created by Mateusz Pysera on 26/05/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "int_operations.h"

int add_int(int a, int b) {
    return a + b;
}
int sub_int(int a, int b) {
    return a - b;
}
int div_int(int a, int b) {
    if(b == 0) return 0;
    return (int)(a / b);
}
int mul_int(int a, int b) {
    return a * b;
}

int calculate(int first, int second, int (*func)(int first, int second)) {
    return (*func)(first, second);
}
calc get_function(enum operations_t operation) {
    switch (operation) {
        case 0:
            return add_int;
        case 1:
            return sub_int;
        case 2:
            return div_int;
        case 3:
            return mul_int;
    }
    return NULL;
}
