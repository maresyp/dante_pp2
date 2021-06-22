#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comparators.h"

int main() {
    printf("enter data type: ");
    int data_type;
    if (scanf("%d", &data_type) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (data_type < 0 || data_type > 2) {
        printf("Incorrect input data");
        return 2;
    }
    printf("enter array size");
    int array_size;
    if (scanf("%d", &array_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (array_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    if (data_type == 0) {
        int * tab = malloc(sizeof(int) * array_size);
        if (tab == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("zapodaj int ");
        for (int i = 0; i < array_size; ++i) {
            if (scanf("%d", (tab + i)) != 1) {
                printf("Incorrect input");
                free(tab);
                return 1;
            }
        }
        sort(tab, array_size, sizeof(int ), comp_int);
        for (int i = 0; i < array_size; ++i) {
            printf("%d ", *(tab + i));
        }
        free(tab);
    } else if (data_type == 1) {
        double * tab = malloc(sizeof(double ) * array_size);
        if (tab == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("zapodaj double: ");
        for (int i = 0; i < array_size; ++i) {
            if (scanf("%lf", (tab + i)) != 1) {
                printf("Incorrect input");
                free(tab);
                return 1;
            }
        }
        sort(tab, array_size, sizeof(double ), comp_double);
        for (int i = 0; i < array_size; ++i) {
            printf("%f ", *(tab + i));
        }
        free(tab);

    } else if (data_type == 2) {
        struct point_t * points = malloc(sizeof(struct point_t) * array_size);
        if (points == NULL) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("zapodaj pointy");
        for (int i = 0; i < array_size; ++i) {
            if (scanf("%lf %lf", &(points + i)->x, &(points + i)->y) != 2) {
                printf("Incorrect input");
                free(points);
                return 1;
            }
        }
        sort(points, array_size, sizeof(struct point_t ), comp_point);
        for (int i = 0; i < array_size; ++i) {
            printf("%f %f\n", (points + i)->x, (points + i)->y);
        }
        free(points);
    }
    return 0;

}