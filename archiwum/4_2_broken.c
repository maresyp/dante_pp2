#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int **create_array_2d(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    int **arr = (int **) malloc(height * sizeof(int *));
    if (arr == NULL) return NULL;
    for (int i = 0; i < width; ++i) {
        *(arr + i) = (int *) malloc(width * sizeof(int));
    }
    return arr;
}
void display_array_2d(int **ptr, int width, int height) {
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
    int **arr = create_array_2d(1, 16);
    destroy_array_2d(arr, 16);
    free(NULL);
    return 0;
}