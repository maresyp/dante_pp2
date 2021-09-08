#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

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

char * concatenate(int num, ...) {
    if (num <= 0) return NULL;
    va_list vaList;
    va_start(vaList, num);
    char * result = NULL;
    char * backup = NULL;
    char * tmp_str = NULL;
    size_t str_len = 0;
    for (int i = 0; i < num; ++i) {
        tmp_str = va_arg(vaList, char *);
        str_len += strlen(tmp_str);
        if (i != num - 1) str_len++;

        if (i != num - 1) backup = realloc(result, str_len + 2);
        else backup = realloc(result, str_len + 1);

        if (backup == NULL) {
            if (result != NULL) free(result);
            return NULL;
        } else {
            result = backup;
        }
        if (i == 0) {
            strcpy(result, tmp_str);
            strcat(result, " ");
        } else {
            strcat(result, tmp_str);
            if (i != num - 1) {
                strcat(result, " ");
            }
        }
    }
    va_end(vaList);
    return result;
}
int main() {
    char ** texts = create_str_arr(4, 1001);
    if (texts == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    int amount;
    printf("Zapodaj liczbe tekstow: ");
    if (scanf("%d", &amount) != 1) {
        delete_str_arr(texts, 4);
        printf("Incorrect input");
        return 1;
    }
    if (amount < 2 || amount > 4) {
        printf("Incorrect input data");
        delete_str_arr(texts, 4);
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
    char * result;
    if (amount == 2) {
        result = concatenate(amount, *(texts + 0), *(texts + 1));
    }
    if (amount == 3) {
        result = concatenate(amount, *(texts + 0), *(texts + 1), *(texts + 2));
    }
    if (amount == 4) {
        result = concatenate(amount, *(texts + 0), *(texts + 1), *(texts + 2), *(texts + 3));
    }
    if (result == NULL) {
        printf("Failed to allocate memory");
        delete_str_arr(texts, 4);
        return 8;
    }
    printf("%s", result);
    free(result);
    delete_str_arr(texts, 4);
    return 0;
}