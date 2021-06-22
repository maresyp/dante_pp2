//
// Created by Mateusz Pysera on 02/05/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix_utils.h"

void swapor(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

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
    ptr = NULL;
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
    m = NULL;
}

struct matrix_t* matrix_create_struct(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    struct matrix_t *matrix = malloc(sizeof(struct matrix_t));
    if (matrix == NULL) return NULL;
    int res = matrix_create(matrix, width, height);
    if (res == 2) {
        free(matrix);
        return NULL;
    }
    return matrix;
}

void matrix_destroy_struct(struct matrix_t **m) {
    if (m == NULL) return;
    destroy_array_2d((*m)->ptr, (*m)->height);
    free(*m);
    *m = NULL;
}

struct matrix_t* matrix_transpose(const struct matrix_t *m) {
    if (m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL) return NULL;
    struct matrix_t *transpose = malloc(sizeof(struct matrix_t));
    if (transpose == NULL) return NULL;
    int res = matrix_create(transpose, m->height, m->width);
    if (res == 2) {
        free(transpose);
        return NULL;
    }
    for (int i = 0; i < m->height; ++i) {
        for (int j = 0; j < m->width; ++j) {
            *(*(transpose->ptr +j) + i) = *(*(m->ptr + i) + j);
        }
    }
    return transpose;
}

int matrix_save_b(const struct matrix_t *m, const char *filename) {
    if (filename == NULL || m == NULL || m->width <= 0 || m->height <= 0 || m->ptr == NULL) return 1;
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) return 2;
    if (fwrite(&m->width, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return 2;
    }
    if (fwrite(&m->height, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return 2;
    }

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++)
            fwrite(&(*(*(m->ptr + i) + j)), sizeof(int), 1, fp);
        if (ferror(fp) != 0) {
            fclose(fp);
            return 3;
        }
    }
    fclose(fp);
    return 0;
}
int matrix_save_t(const struct matrix_t *m, const char *filename) {
    if (filename == NULL || m == NULL || m->width <= 0 || m->height <= 0 || m->ptr == NULL) return 1;
    FILE *fp; fp = fopen(filename, "w");
    if (fp == NULL) return 2;
    fprintf(fp, "%d %d\n", m->width, m->height);
    if (ferror(fp) != 0) {
        fclose(fp);
        return 3;
    }

    for (int i = 0; i < m->height; i++) {
        for (int j = 0; j < m->width; j++)
            fprintf(fp, "%d ", *(*(m->ptr + i) + j));
        fprintf(fp, "\n");
        if (ferror(fp) != 0) {
            fclose(fp);
            return 3;
        }
    }
    fclose(fp);
    return 0;
}

