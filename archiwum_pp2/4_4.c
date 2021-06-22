#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct matrix_t{
    int **ptr;
    int width;
    int height;
};
int **create_array_2d(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    int **arr = (int **) malloc(height * sizeof(int *));
    if (arr == NULL) return NULL;
    for(int i = 0; i < height; i++){
        *(arr + i) = (int *)malloc(width * sizeof(int));
        if (*(arr + i) == NULL) {
            for (int j = i - 1; j >= 0; --j) {
                free(*(arr + j));
            }
            free(arr);
            return NULL;
        }
    }
    return arr;
}
void display_array_2d(int **ptr, int width, int height) {
    if (width <= 0 || height <= 0 || ptr == NULL) return;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            printf("%d ", *(*(ptr + i) + j));
        printf("\n");
    }
}

void destroy_array_2d(int **ptr, int height) {
    if (ptr == NULL || height <= 0) return;
    for (int i = 0; i < height; ++i) {
        free(*(ptr + i));
    }
    free(ptr);
}
int write_to_array_2d(int **ptr, int width, int height) {
    if (width <= 0 || height <= 0 || ptr == NULL) return 1;
    int tmp;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (scanf("%d", &tmp) != 1) return 2;
            *(*(ptr + i) + j) = tmp;
        }
    }
    return 0;
}
int matrix_create(struct matrix_t *m, int width, int height) {
    if (m == NULL || width <= 0 || height <= 0) return 1;
    m->ptr = create_array_2d(width, height);
    if (m->ptr == NULL) return 2;
    m->height = height;
    m->width = width;
    return 0;
}
int matrix_read(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->height <= 0 || m->width <= 0) return 1;
    int res = write_to_array_2d(m->ptr, m->width, m->height);
    if (res == 2) return 2;
    return 0;
}
void matrix_display(const struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->width <= 0 || m->height <= 0) return;
    display_array_2d(m->ptr, m->width, m->height);
}
void matrix_destroy(struct matrix_t *m) {
    if (m == NULL || m->ptr == NULL || m->height <= 0) return;
    destroy_array_2d(m->ptr, m->height);
}

int main() {
    printf("Podaj szerokość i wysokość: ");
    int height, width;
    if (scanf("%d %d", &width, &height) != 2) {
        printf("incorrect input");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct matrix_t matrix;
    int res = matrix_create(&matrix, width, height);
    if (res == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wartości: ");
    res = matrix_read(&matrix);
    if (res == 2) {
        printf("incorrect input");
        matrix_destroy(&matrix);
        return 1;
    }
    matrix_display(&matrix);
    matrix_destroy(&matrix);
    return 0;
}