#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "circular_buffer.h"

int main(){
    /*
    const int array[] = {-1, 29, -68, 79, 9, -88, -69, -68, 57, 34, 63, -51, 22, -8, -21, 23, 12, -98};
    struct circular_buffer_t ptr = { .begin = 4, .end = 1, .capacity = -6, .full = 0 };
    int res = circular_buffer_create(&ptr, 18);
    for (int i = 0; i < 18; ++i)
    {
        res = circular_buffer_push_back(&ptr, array[i]);
    }
    circular_buffer_display(&ptr);
     */
    printf("Zapodaj rozmiar bufora: ");
    int buf_size;
    if (scanf("%d", &buf_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (buf_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct circular_buffer_t *buffer;
    int res = circular_buffer_create_struct(&buffer, buf_size);
    if (res == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    int user_input = 1;
    int value;
    int err_code;
    while (user_input != 0) {
        printf("Co chcesz zrobic ? ");
        if (scanf("%d", &user_input) != 1) {
            printf("Incorrect input");
            circular_buffer_destroy_struct(&buffer);
            return 1;
        }
        if (user_input < 0 || user_input > 6) {
            printf("Incorrect input data\n");
        }
        if (user_input == 1) {
            printf("Podaj liczbe: ");
            if (scanf("%d", &value) != 1) {
                printf("Incorrect input");
                circular_buffer_destroy_struct(&buffer);
                return 1;
            }
            circular_buffer_push_back(buffer, value);
        }
        if (user_input == 2) {
            res = circular_buffer_pop_back(buffer, &err_code);
            if (err_code == 2) {
                printf("Buffer is empty\n");
            } else {
                printf("%d\n", res);
            }
        }
        if (user_input == 3) {
            res = circular_buffer_pop_front(buffer, &err_code);
            if (err_code == 2) {
                printf("Buffer is empty\n");
            } else {
                printf("%d\n", res);
            }
        }
        if (user_input == 4) {
            if (circular_buffer_empty(buffer) == 1) {
                printf("Buffer is empty\n");
            } else {
                circular_buffer_display(buffer);
                printf("\n");
            }
        }
        if (user_input == 5) {
            if (circular_buffer_empty(buffer) == 1) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
        if (user_input == 6) {
            if (circular_buffer_full(buffer) == 1) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }

    return 0;
}