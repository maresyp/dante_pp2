#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "int_operations.h"

int main() {
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
    printf("%d", (*get_function(op))(a, b));
}