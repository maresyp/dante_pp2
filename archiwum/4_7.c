#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image_utils.h"

int main() {
    char *filename = malloc(sizeof(char) * 40);
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Zapodaj nazwe pliku: ");
    scanf("%39s", filename);

    int err_code;
    struct image_t *image = load_image_t(filename, &err_code);
    if (err_code == 2) {
        free(filename);
        printf("Couldn't open file");
        return 4;
    }
    if (err_code == 4) {
        free(filename);
        printf("Failed to allocate memory");
        return 8;
    }
    if (err_code == 3) {
        printf("File corrupted");
        free(filename);
        return 6;
    }
    struct image_t *mirror_h_ = image_flip_horizontal(image);
    if (mirror_h_ == NULL) {
        destroy_image(&image);
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }
    struct image_t *mirror_v_ = image_flip_vertical(image);
    if (mirror_v_ == NULL) {
        destroy_image(&image);
        destroy_image(&mirror_h_);
        free(filename);
        printf("Failed to allocate memory");
        return 8;
    }
    struct image_t *invert_ = image_negate(image);
    if (invert_ == NULL) {
        destroy_image(&image);
        destroy_image(&mirror_h_);
        destroy_image(&mirror_v_);
        free(filename);
        printf("Failed to allocate memory");
        return 8;
    }
    char *str_h = malloc(strlen("mirror_h_\0") + strlen(filename) + 1);
    if (str_h == NULL) {
        destroy_image(&image);
        destroy_image(&mirror_h_);
        destroy_image(&mirror_v_);
        destroy_image(&invert_);
        free(filename);
        printf("Failed to allocate memory");
        return 8;
    }
    strcpy(str_h, "mirror_h_\0");
    strcat(str_h, filename);
    err_code = save_image_t(str_h, mirror_h_);
    if (err_code == 2) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    char *str_v = malloc(strlen("mirror_v_\0") + strlen(filename) + 1);
    if (str_v == NULL) {
        destroy_image(&image);
        destroy_image(&mirror_h_);
        destroy_image(&mirror_v_);
        destroy_image(&invert_);
        free(filename);
        free(str_h);
        printf("Failed to allocate memory");
        return 8;
    }
    strcpy(str_v, "mirror_v_\0");
    strcat(str_v, filename);
    err_code = save_image_t(str_v, mirror_v_);
    if (err_code == 2) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    char *str_n = malloc(sizeof("invert_\0") + strlen(filename) + 1);
    if (str_n == NULL) {
        destroy_image(&image);
        destroy_image(&mirror_h_);
        destroy_image(&mirror_v_);
        destroy_image(&invert_);
        free(filename);
        free(str_h);
        free(str_v);
        printf("Failed to allocate memory");
        return 8;
    }
    strcpy(str_n, "invert_\0");
    strcat(str_n, filename);
    err_code = save_image_t(str_n, invert_);
    if (err_code == 2) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    destroy_image(&image);
    destroy_image(&mirror_h_);
    destroy_image(&mirror_v_);
    destroy_image(&invert_);
    free(filename);
    free(str_h);
    free(str_v);
    free(str_n);
    return 0;
}