#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "file_struct_utils.h"

struct point_t {
    int x;
    int y;
};

int dante_check(char *filename) {
    FILE *f; f = fopen(filename, "r");
    if (f == NULL) return 1;
    fclose(f);
    return 0;
}

int main(){
    char file_name[31];

    srand(time(NULL));
    struct point_t p1;
    int x = rand() % 50;
    int y = rand() % 50;

    set(&p1, x, y);
    printf("x = %d; y = %d\n", p1.x, p1.y);
    printf("file path:\n");
    scanf("%30s", file_name);
    int mode;
    char *dot = strrchr(file_name, '.');
    if (dot && !strcmp(dot, ".bin")) {
        mode = 0;
        int err = save_point_b(file_name, &p1);
        if (err == 2 || err == 3) {
            printf("Couldn't create file");
            return 5;
        }
    } else if (dot && !strcmp(dot, ".txt")) {
        mode = 1;
        int err = save_point_t(file_name, &p1);
        if (err == 2 || err == 3) {
            printf("Couldn't create file");
            return 5;
        }
    } else {
        printf("Unsupported file format");
        return 7;
    }
    if (dante_check(file_name)) {
        printf("Couldn't open file");
        return 5;
    }
    printf("File saved\n");

    if (dante_check(file_name)) {
        printf("Couldn't open file");
        return 5;
    }
    printf("Do you want to read the file (Y/N)? ");
    char ch;
    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
    scanf("%1ch", &ch);
    if (ch == 'n' || ch == 'N') {
        return 0;
    } else if (ch == 'y' || ch == 'Y') {
        int err;
        if (mode == 1) {
            err = load_point_t(file_name, &p1);
        } else {
            err = load_point_b(file_name, &p1);
        }
        if (err == 3) {
            printf("File corrupted");
            return 6;
        }
        if (err == 2) {
            printf("Couldn't open file");
            return 4;
        }

        printf("x = %d; y = %d\n", p1.x, p1.y);
    } else {
        printf("incorrect input");
        return 1;
    }

    return 0;
}
