#include <stdio.h>
#include <stdint.h>
#include "tested_declarations.h"
#include "rdebug.h"

int is_sparse(uint64_t value) {
    if (value & (value >> 1)) return 0;
    return 1;
}
int main() {
    printf("Podaj liczbe: ");
    uint64_t number;
    if (scanf("%lu", &number) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("Liczba: %016lx, Wynik: %d", number, is_sparse(number));
    return 0;
}
