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

int create_array_2d_2(int ***ptr, int width, int height) {
    if (ptr == NULL || height <= 0 || width <= 0) return 1;
    int **res = create_array_2d(width, height);
    if (res == NULL) return 2;
    *ptr = res;
    return 0;
}

void destroy_array_2d(int ***ptr, int height) {
    if (ptr == NULL || *ptr == NULL || height <= 0) return;
    for (int i = 0; i < height; ++i) {
        free(*(*ptr + i));
    }
    free(*ptr);
    *ptr = NULL;
}
int sum_row(int *ptr, int width) {
    if (ptr == NULL || width <= 0) return -1;
    int sum = 0;
    for (int i = 0; i < width; ++i) {
        sum += *(ptr + i);
    }
    return sum;
}
int sum_array_2d(int **ptr, int width, int height) {
    if (ptr == NULL || width <= 0 || height <= 0) return -1;
    int sum = 0;
    for (int i = 0; i < height; ++i) {
        sum += sum_row(*(ptr + i) ,width);
    }
    return sum;
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
        // destroy_array
        for (int i = 0; i < height; ++i) {
            free(*(arr + i));
        }
        free(arr);
        // destroy_array
        return 1;
    }
    display_array_2d(arr, width, height);

    for (int i = 0; i < height; ++i) {
        printf("%d\n", sum_row(*(arr + i) , width));
    }

    printf("%d", sum_array_2d(arr, width, height));
    // destroy_array
    for (int i = 0; i < height; ++i) {
        free(*(arr + i));
    }
    free(arr);
    // destroy_array
    return 0;
}