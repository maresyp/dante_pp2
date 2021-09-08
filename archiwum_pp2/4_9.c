#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "image_utils.h"

int main() {
    struct image_t *src;
    char *filename = malloc(sizeof(char) * 40);
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Zapodaj nazwe pliku: ");
    scanf("%30s", filename);
    int err;
    struct image_t *image = load_image_t(filename, &err);
    if (err == 2) {
        printf("Couldn't open file");
        free(filename);
        return 4;
    }
    if (err == 4) {
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }
    if (err == 3) {
        printf("File corrupted");
        free(filename);
        return 6;
    }
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

    int amount;
    printf("Zapodaj ile obrazów: ");
    if (scanf("%d", &amount) != 1) {
        printf("Incorrect input");
        free(filename);
        destroy_image(&image);
        return 1;
    }
    if (amount <= 0) {
        printf("Incorrect input data");
        free(filename);
        destroy_image(&image);
        return 2;
    }
    char *name;
    int x, y;
    for (int i = 0; i < amount; ++i) {
        name = malloc(sizeof(char ) * 40);
        if (name == NULL) {
            printf("Failed to allocate memory");
            free(filename);
            destroy_image(&image);
            return 8;
        }
        printf("zapodaj subimage: ");
        scanf("%39s", name);
        src = load_image_t(name, &err);

        if (err == 4) {
            printf("Failed to allocate memory");
            free(filename);
            destroy_image(&image);
            free(name);
            return 8;
        }
        if (err == 3) {
            printf("File corrupted\n");
        } else if (err == 2) {
            printf("Couldn't open file\n");
        } else {
            printf("Zapodaj x y: ");
            if (scanf("%d %d", &x, &y) != 2) {
                printf("Incorrect input");
                free(filename);
                free(name);
                destroy_image(&image);
                destroy_image(&src);
                return 1;
            }
            int res = draw_image(image, src, x, y);
            if (res != 0) {
                printf("Incorrect input data\n");
            }
        }
        free(name);
        destroy_image(&src);
    }
    char *output_name = malloc(strlen("_modified") + strlen(filename) + 1);
    if (output_name == NULL) {
        printf("Failed to allocate memory");
        free(filename);
        destroy_image(&image);
        destroy_image(&src);
        return 8;
    }
    /*
    char *tokens = strtok(filename, ".");
    strcpy(output_name, tokens);
    strcat(output_name, "_modified");
    tokens = strtok(NULL, ".");
    while (tokens != NULL) {
        strcat(output_name, ".");
        strcat(output_name, tokens);
        tokens = strtok(NULL, ".");
    }
     */
    int file_len = strlen(filename);
    int file_last_dot = 0;
    for (int i = 0; i < file_len; ++i) {
        if (*(filename + i) == '.') {
            file_last_dot = i;
        }
    }
    if (file_last_dot == 0) {
        strcpy(output_name, filename);
        strcat(output_name, "_modified");
    } else {
        strncpy(output_name, filename, file_last_dot);
        *(output_name + file_last_dot) = '\0';
        strcat(output_name, "_modified.");
        strcat(output_name, filename + file_last_dot + 1);
    }
    err = save_image_t(output_name, image);
    if (err != 0) {
        printf("Couldn't create file");
        free(filename);
        destroy_image(&image);
        destroy_image(&src);
        free(output_name);
        return 5;
    }
    free(filename);
    destroy_image(&image);
    destroy_image(&src);
    free(output_name);
    printf("File saved");
    return 0;
}