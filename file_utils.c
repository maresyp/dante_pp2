//
// Created by Mateusz Pysera on 08/03/2021.
//

#include <stdio.h>
#include <string.h>

void cleaning(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int file_size_from_path(const char *path) {
    if (path == NULL) { return -2; }
    FILE *fp; fp = fopen(path, "r");
    if (fp == NULL) { return -1; }
    fseek(fp, 0, SEEK_END);
    int len = (int)ftell(fp);
    rewind(fp);
    fclose(fp);
    return len;
}
/*
int file_size_from_file(FILE *f) {
    if (f == NULL) { return -2; }
    int start_pos = (int)ftell(f);
    fseek(f, 0, SEEK_END);
    int len = (int)ftell(f);
    fseek(f, start_pos, SEEK_SET);
    return len;
}
*/
int read_file(const char *filename) {
    if (filename == NULL) return -1;
    int value = 0;
    FILE *fp; fp = fopen(filename, "r");
    if (fp != NULL) {
        value = 1;
        char file_name[31];
        while (fscanf(fp, "%s", file_name) != EOF) {
            printf("%s\n", file_name);
            value += read_file(file_name);
        }
        fclose(fp);
    }
    return value;
}