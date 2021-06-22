//
// Created by Mateusz Pysera on 04/05/2021.
//

#include "image_utils.h"
#include "matrix_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct image_t* load_image_t(const char *filename, int *err_code) {
    if (err_code != NULL) *err_code = 0;
    if (filename == NULL) {
        if (err_code != NULL) *err_code = 1;
        return NULL;
    }
    FILE *fp; fp = fopen(filename, "r");
    if (fp == NULL) {
        if (err_code != NULL) *err_code = 2;
        return NULL;
    }
    struct image_t *image = malloc(sizeof(struct image_t));
    if (image == NULL) {
        if (err_code != NULL) *err_code = 4;
        fclose(fp);
        return NULL;
    }
    fscanf(fp, "%2s", image->type);
    if (ferror(fp) != 0 || feof(fp) != 0) {
        if (err_code != NULL) *err_code = 3;
        fclose(fp);
        free(image);
        return NULL;
    }
    if (strcmp("P2", image->type) != 0) {
        if (err_code != NULL) *err_code = 3;
        fclose(fp);
        free(image);
        return NULL;
    }
    int c = fgetc(fp);
    if (c != '\n') {
        if (err_code != NULL) *err_code = 3;
        fclose(fp);
        free(image);
        return NULL;
    } else {
        ungetc(c, fp);
    }
    // read width, height, max
    int tmp;
    fscanf(fp, "%d %d\n%d", &image->width, &image->height, &tmp);
    if (ferror(fp) != 0 || feof(fp) != 0) {
        if (err_code != NULL) *err_code = 3;
        fclose(fp);
        free(image);
        return NULL;
    }
    if (image->height <= 0 || image->width <= 0) {
        if (err_code != NULL) *err_code = 3;
        fclose(fp);
        free(image);
        return NULL;
    }
    // create matrix
    image->ptr = create_array_2d(image->width, image->height);
    if (image->ptr == NULL) {
        if (err_code != NULL) *err_code = 4;
        fclose(fp);
        free(image);
        return NULL;
    }
    // read from file to array
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fscanf(fp, "%d", &tmp);
            if (ferror(fp) != 0 || feof(fp) || tmp < 0 != 0) {
                if (err_code != NULL) *err_code = 3;
                fclose(fp);
                destroy_array_2d(image->ptr, image->height);
                free(image);
                return NULL;
            }
            *(*(image->ptr + i) + j) = tmp;
        }
    }
    fclose(fp);
    return image;
}

int save_image_t(const char * filename, const struct image_t *m1) {
    if (filename == NULL || m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <= 0) return 1;
    FILE *fp; fp = fopen(filename, "w");
    if (fp == NULL) return 2;

    fprintf(fp, "P2\n%d %d\n255\n", m1->width, m1->height);
    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++)
            fprintf(fp, "%d ", *(*(m1->ptr + i) + j));
        fprintf(fp, "\n");
        if (ferror(fp) != 0) {
            fclose(fp);
            return 3;
        }
    }
    fclose(fp);
    return 0;
}
void destroy_image(struct image_t **m) {
    if (m == NULL || *m == NULL) return;
    if ((*m)->ptr == NULL) {
        free(*m);
    } else {
        destroy_array_2d((*m)->ptr, (*m)->height);
        free(*m);
    }
    *m = NULL;
}
struct image_t* image_flip_horizontal(const struct image_t *m1) {
    if (m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <= 0) return NULL;
    struct image_t *image = malloc(sizeof(struct image_t));
    if (image == NULL) return NULL;
    image->ptr = create_array_2d(m1->width, m1->height);
    if (image->ptr == NULL) {
        free(image);
        return NULL;
    }
    strcpy(image->type, "P2\0");
    image->height = m1->height;
    image->width = m1->width;
    int end = m1->height - 1;
    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++) {
            *(*(image->ptr + i) + j) = (*(*(m1->ptr + end) + j));
        }
        end--;
    }
    return image;
}
struct image_t* image_flip_vertical(const struct image_t *m1) {
    if (m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <= 0) return NULL;
    struct image_t *image = malloc(sizeof(struct image_t));
    if (image == NULL) return NULL;
    image->ptr = create_array_2d(m1->width, m1->height);
    if (image->ptr == NULL) {
        free(image);
        return NULL;
    }
    strcpy(image->type, "P2\0");
    image->height = m1->height;
    image->width = m1->width;

    for (int i = 0; i < m1->height; i++) {
        int end = m1->width - 1;
        for (int j = 0; j < m1->width; j++) {
            *(*(image->ptr + i) + j) = (*(*(m1->ptr + i) + end));
            end--;
        }
    }
    return image;
}

struct image_t* image_negate(const struct image_t *m1) {
    if (m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <= 0) return NULL;
    struct image_t *image = malloc(sizeof(struct image_t));
    if (image == NULL) return NULL;
    image->ptr = create_array_2d(m1->width, m1->height);
    if (image->ptr == NULL) {
        free(image);
        return NULL;
    }
    strcpy(image->type, "P2\0");
    image->height = m1->height;
    image->width = m1->width;
    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++)
            *(*(image->ptr + i) + j) = (*(*(m1->ptr + i) + j) - 255) * (-1);
    }
    return image;
}

const int* image_get_pixel(const struct image_t *img, int x, int y) {
    if (img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || x < 0 || y < 0) return NULL;
    if (x >= img->width || y >= img->height) return NULL;
    return ((*(img->ptr + y)) + x);
}

int* image_set_pixel(struct image_t *img, int x, int y) {
    if (img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || x < 0 || y < 0) return NULL;
    if (x >= img->width || y >= img->height) return NULL;
    return ((*(img->ptr + y)) + x);
}

int image_draw_rectangle(struct image_t *img, const struct rectangle_t *rect, int value) {
    if (img == NULL || img->ptr == NULL || img->height <= 0 || img->width <= 0 || rect == NULL || rect->p.x < 0 || rect->p.y < 0 || rect->width <= 0 || rect->height <= 0 || value < 0 || value > 255) return 1;
    if (rect->p.x + rect->width > img->width) return 1;
    if (rect->p.y + rect->height > img->height) return 1;
    // draw top, bottom
    for (int i = 0; i < rect->width; ++i) {
        *(*(img->ptr + rect->p.y) + i + rect->p.x) = value;
        *(*(img->ptr + (rect->p.y + rect->height - 1)) + i + rect->p.x) = value;
    }
    // draw left, right
    for (int i = 0; i < rect->height; ++i) {
        *(*( img->ptr + (rect->p.y + i) ) + rect->p.x ) = value;
        *(*( img->ptr + (rect->p.y + i) ) + (rect->p.x + rect->width - 1) ) = value;
    }
    return 0;
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty) {
    if (img == NULL || img->ptr == NULL || src == NULL || src->ptr == NULL) return 1;
    if (img->height <= 0 || img->width <= 0 || src->width <= 0 || src->height <= 0) return 1;
    if (destx < 0 || desty < 0) return 1;
    if (src->width + destx > img->width) return 1;
    if (src->height + desty > img->height) return 1;

    for (int i = 0; i < src->height; i++) {
        for (int j = 0; j < src->width; j++)
            *(*(img->ptr + (i + desty)) + (j + destx)) = *(*(src->ptr + i) + j);
    }
    return 0;
}

