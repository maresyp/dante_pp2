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
    printf("Podaj nazwe:");
    scanf("%39s", filename);
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
    int x, y, width, height, value;
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    printf("Podaj wspolrzedne i wymiary prostokata: ");
    if (scanf("%d %d %d %d", &x, &y, &width, &height) != 4) {
        printf("Incorrect input");
        free(filename);
        destroy_image(&image);
        return 1;
    }
    printf("Podaj value: ");
    if (scanf("%d", &value) != 1) {
        printf("Incorrect input");
        free(filename);
        destroy_image(&image);
        return 1;
    }
    int res = image_draw_rectangle(image,&(struct rectangle_t){ .p  = { x, y }, .width = width, .height = height }, value);
    if (res != 0) {
        printf("Incorrect input data");
        free(filename);
        destroy_image(&image);
        return 2;
    }
    res = save_image_t(filename, image);
    if (res == 2) {
        printf("Couldn't create file");
        free(filename);
        destroy_image(&image);
        return 5;
    }
    printf("File saved");
    destroy_image(&image);
    free(filename);
    return 0;
}