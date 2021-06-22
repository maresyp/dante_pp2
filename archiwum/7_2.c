#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>


int concatenate(char *buffer, int buffer_size, int texts_count, ...) {
    if (buffer == NULL || buffer_size <= 0 || texts_count <= 0) return 1;
    va_list vaList;
    va_start(vaList, texts_count);
    size_t size_left = buffer_size;
    for (int i = 0; i < texts_count; ++i) {
        char * tmp_str = va_arg(vaList, char *);
        if (size_left < strlen(tmp_str) + 1) {
            va_end(vaList);
            return 2;
        }
        if (i == 0) {
            strcpy(buffer, tmp_str);
            strcat(buffer, " ");
        } else {
            strcat(buffer, tmp_str);
            if (i != texts_count - 1) {
                strcat(buffer, " ");
            }
        }
        size_left -= strlen(tmp_str) + 1;
    }
    va_end(vaList);
    return 0;
}

char ** create_str_arr(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }
    char ** arr = (char **) malloc(rows * sizeof(char *));
    if (arr == NULL) return NULL;
    for (int i = 0; i < rows; ++i) {
        *(arr + i) = malloc(cols * sizeof(char));
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

void delete_str_arr(char ** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(*(arr + i));
    }
    free(arr);
}

int main() {
    char ** texts = create_str_arr(4, 1001);
    if (texts == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    char * result = malloc(sizeof(char ) * 4004);
    if (result == NULL) {
        delete_str_arr(texts, 4);
        printf("Failed to allocate memory");
        return 8;
    }
    int amount;
    printf("Zapodaj liczbe tekstow: ");
    if (scanf("%d", &amount) != 1) {
        delete_str_arr(texts, 4);
        free(result);
        printf("Incorrect input");
        return 1;
    }
    if (amount < 2 || amount > 4) {
        printf("Incorrect input data");
        delete_str_arr(texts, 4);
        free(result);
        return 2;
    }

    printf("Podaj teksty: ");
    for (int i = 0; i < amount; ++i) {
        int c;
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
        scanf("%1000[^\n]s", *(texts + i));
    }
    if (amount == 2) {
        concatenate(result, 4004, amount, *(texts + 0), *(texts + 1));
    }
    if (amount == 3) {
        concatenate(result, 4004, amount, *(texts + 0), *(texts + 1), *(texts + 2));
    }
    if (amount == 4) {
        concatenate(result, 4004, amount, *(texts + 0), *(texts + 1), *(texts + 2), *(texts + 3));
    }
    printf("%s", result);
    free(result);
    delete_str_arr(texts, 4);
    return 0;
}