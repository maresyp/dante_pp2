#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../matrix_utils.h"

int main() {
    int height, width;
    printf("Podaj szerokość i wysokość: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("incorrect input");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct matrix_t *matrix = matrix_create_struct(width, height);
    if (matrix == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wartości: ");
    int res = matrix_read(matrix);
    if (res == 2) {
        printf("incorrect input");
        matrix_destroy_struct(&matrix);
        free(matrix);
        return 1;
    }
    char *filename = malloc(sizeof(char) * 40);
    if (filename == NULL) {
        printf("Failed to allocate memory");
        matrix_destroy_struct(&matrix);
        free(matrix);
        return 8;
    }
    printf("zapodaj sciezke do pliku: ");
    scanf("%39s", filename);
    int mode;
    char *dot = strrchr(filename, '.');
    if (dot && !strcmp(dot, ".bin")) {
        mode = 0;
    } else if (dot && !strcmp(dot, ".txt")) {
        mode = 1;
    } else {
        printf("Unsupported file format");
        matrix_destroy_struct(&matrix);
        free(filename);
        return 7;
    }
    struct matrix_t *transposed = matrix_transpose(matrix);
    if (transposed == NULL) {
        printf("Failed to allocate memory");
        free(filename);
        matrix_destroy_struct(&matrix);
        return 8;
    }
    if (mode == 0) {
        res = matrix_save_b(transposed, filename);
    } else {
        res = matrix_save_t(transposed, filename);
    }
    if (res == 2) {
        printf("Couldn't create file");
        matrix_destroy_struct(&matrix);
        matrix_destroy_struct(&transposed);
        free(filename);
        return 5;
    }
    printf("File saved");
    matrix_destroy_struct(&matrix);
    matrix_destroy_struct(&transposed);
    free(filename);
    return 0;
}