#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

int longest_series(unsigned int x) {
    int result = 0;
    while (x != 0) {
        x = (x & (x << 1));
        result++;
    }
    return result;
}
int main() {
    printf("Podaj liczbe: ");
    unsigned int liczba;
    if (scanf("%u", &liczba) != 1) {
        printf("Incorrect input");
        return 1;
    }
    printf("Wynik: %d", longest_series(liczba));
    return 0;
}
