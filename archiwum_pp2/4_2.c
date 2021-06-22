#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int main(){
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
    int **arr = create_array_2d(width, height);
    if (arr == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj liczby: ");
    int res = write_to_array_2d(arr, width, height);
    if (res == 2) {
        printf("Incorrect input");
        destroy_array_2d(arr, height);
        return 1;
    }
    display_array_2d(arr, width, height);
    destroy_array_2d(arr, height);
    return 0;
}