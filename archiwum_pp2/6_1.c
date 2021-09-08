#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "int_operations.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main() {
    int (*funcs[])(int, int) = {add_int, sub_int, div_int, mul_int};
    printf("Zapodaj numery");
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("Incorrect input");
        return 1;
    }
    printf("Zapodaj operacje");
    int op;
    if (scanf("%d", &op) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (op < 0 || op > 3) {
        printf("Incorrect input data");
        return 2;
    }
    printf("%d", calculate(a, b, *(funcs + op)));
}
