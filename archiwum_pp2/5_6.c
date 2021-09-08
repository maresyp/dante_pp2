#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "big_numbers.h"

int main(){
    char * filename = malloc(31);
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("zapodaj: ");
    scanf("%30s", filename);
    struct big_numbers_t * bigNumbers;
    int res = load_big_numbers_b(&bigNumbers, filename);
    if (res == 2) {
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }
    if (res == 3) {
        printf("Couldn't open file");
        free(filename);
        return 4;
    }
    if (res == 4) {
        printf("File corrupted");
        free(filename);
        return 7;
    }
    sort_big_numbers_asc(bigNumbers);
    char * new_name = malloc(strlen(filename) + strlen("_sorted") + 1);
    if (new_name == NULL) {
        printf("Failed to allocate memory");
        free(filename);
        destroy_big_numbers(&bigNumbers);
        return 8;
    }
    int file_len = strlen(filename);
    int file_last_dot = 0;
    for (int i = 0; i < file_len; ++i) {
        if (*(filename + i) == '.') {
            file_last_dot = i;
        }
    }
    if (file_last_dot == 0) {
        strcpy(new_name, filename);
        strcat(new_name, "_sorted");
    } else {
        strncpy(new_name, filename, file_last_dot);
        *(new_name + file_last_dot) = '\0';
        strcat(new_name, "_sorted.");
        strcat(new_name, filename + file_last_dot + 1);
    }
    res = save_big_numbers_b(bigNumbers, new_name);
    if (res == 2) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    int err;
    char * sum = total_sum_big_numbers(bigNumbers, &err);
    if (err != 0) printf("Error");
    else printf("%s", sum);
    free(sum);
    free(new_name);
    destroy_big_numbers(&bigNumbers);
    free(filename);
    return 0;
}