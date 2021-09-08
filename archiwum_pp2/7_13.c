#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

int* count_words(const char *filename, int *err_code, int N, ...) {
    if (err_code != NULL) *err_code = 0;
    if (filename == NULL || N <= 0) {
        if (err_code != NULL) *err_code = 1;
        return NULL;
    }
    FILE *fp; fp = fopen(filename, "r");
    if (fp == NULL) {
        if (err_code != NULL) *err_code = 2;
        return NULL;
    }
    int * result = malloc(sizeof(int ) * N);
    if (result == NULL) {
        if (err_code != NULL) *err_code = 3;
        fclose(fp);
        return NULL;
    }
    for (int i = 0; i < N; ++i) {
        *(result + i) = 0;
    }
    va_list vaList;
    va_start(vaList, N);
    char * tmp_str;

    for (int i = 0; i < N; ++i) {
        tmp_str = va_arg(vaList, char *);
        int tmp_len = strlen(tmp_str);
        int comparations = 0;
        char file_char;
        while (feof(fp) == 0) {
            file_char = (char) fgetc(fp);
            if (comparations < tmp_len) {
                if (comparations == 0 && file_char == '"') continue;
                if (comparations == 0 && file_char == '\n') continue;
                if (comparations == 0 && file_char == '-') continue;
                if (comparations == 0 && file_char == 91) continue;
                if (comparations == 0 && file_char == '(') continue;
                if (file_char != *(tmp_str + comparations)) {
                    // not equal -> go to next word
                    if (file_char != ' ' && file_char != '\n') {
                        while (file_char != ' ' && file_char != '\n' && feof(fp) == 0) {
                            file_char = (char) fgetc(fp);
                        }
                    } // else -> already at next word
                    comparations = 0;
                } else {
                    comparations++;
                }
            } else {
                comparations = 0;
                if (file_char == ' ' || file_char == '\n' || file_char == '.' || file_char == ',' || file_char == '\'' || feof(fp) != 0) *(result + i) = *(result + i) + 1;
                if (file_char != ' ' && file_char != '\n') {
                    while (file_char != ' ' && file_char != '\n' && feof(fp) == 0) {
                        file_char = (char) fgetc(fp);
                    }
                }
            }
        }
        rewind(fp);
    }
    va_end(vaList);
    fclose(fp);
    return result;
}
int main(int argc, char **argv) {
    int err;
    int * result;
    if (argc - 2 <= 0) {
        printf("Not enough arguments");
        return 9;
    }
    for (int i = 0; i < argc - 2; ++i) {
        result = count_words(*(argv + 1), &err, 1, *(argv + i + 2));
        if (err == 2) {
            printf("Couldn't open file");
            return 4;
        }
        if (err == 3) {
            printf("Failed to allocate memory");
            return 8;
        }
        printf("%d\n", *result);
        free(result);
    }
    return 0;
}