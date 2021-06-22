#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../functions.h"

int main() {
    unsigned long x = 18446744073709551615ULL;
    DISPLAY_BITS(x)
    printf("\n");
    REVERSE_BITS(&x);
    DISPLAY_BITS(x)
    printf("\n%lu\n", x);
    printf("enter data type: ");
    int data;
    if (scanf("%d", &data) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (data < 0 || data > 2) {
        printf("Incorrect input data");
        return 2;
    }
    printf("enter number: ");
    if (data == 0) {
        unsigned int number;
        if (scanf("%u", &number) != 1) {
            printf("Incorrect input");
            return 1;
        }
        int set, not;
        COUNT_BITS(number, &set, &not)
        printf("%d\n%d\n", set, not);
        DISPLAY_BITS(number)
        printf("\n");
        REVERSE_BITS(&number)
        DISPLAY_BITS(number)
    }
    if (data == 1) {
        unsigned short number;
        if (scanf("%hu", &number) != 1) {
            printf("Incorrect input");
            return 1;
        }
        int set, not;
        COUNT_BITS(number, &set, &not)
        printf("%d\n%d\n", set, not);
        DISPLAY_BITS(number)
        printf("\n");
        REVERSE_BITS(&number)
        DISPLAY_BITS(number)
    }
    if (data == 2) {
        unsigned long number;
        if (scanf("%lu", &number) != 1) {
            printf("Incorrect input");
            return 1;
        }
        int set, not;
        COUNT_BITS(number, &set, &not)
        printf("%d\n%d\n", set, not);
        DISPLAY_BITS(number)
        printf("\n");
        REVERSE_BITS(&number)
        DISPLAY_BITS(number)
    }

    return 0;
}