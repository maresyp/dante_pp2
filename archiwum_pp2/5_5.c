#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "big_numbers.h"
#include "tested_declarations.h"
#include "rdebug.h"

void cls(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(){
    struct big_numbers_t * bigNumbers;
    int res = create_big_numbers(&bigNumbers, 10);
    if (res == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    char * buffer = malloc(201);
    if (buffer == NULL) {
        printf("Failed to allocate memory");
        destroy_big_numbers(&bigNumbers);
        return 8;
    }
    printf("Podaj liczby: ");
    while (1) {
        fgets(buffer, 201, stdin);

        if (*(buffer) == '\n') break;
        for (int i = 0; i < (int)strlen(buffer); ++i) {
            if (*(buffer + i) == '\n') { *(buffer + i) = '\0'; break; }
        }
        if (strlen(buffer) == 200) cls();
        res = add_big_number(bigNumbers, buffer);
        if (res == 1) {
            printf("Incorrect input\n");
        }
        if (res == 2) {
            printf("Failed to allocate memory\n");
            break;
        }
        if (res == 3) {
            printf("Buffer is full\n");
            break;
        }
    }
    if (bigNumbers->size == 0) {
        printf("Buffer is empty");
    } else {
        display(bigNumbers);
    }
    free(buffer);
    destroy_big_numbers(&bigNumbers);
    return 0;
}
