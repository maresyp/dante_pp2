#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../format_type.h"

void display(int **ptr) {
    if (ptr == NULL || *ptr == NULL) return;
    int i = 0;
    while (*(ptr + i) != NULL) {
        int j = 0;
        while (*(*(ptr + i) + j) != -1) {
            printf("%d ", *(*(ptr + i) + j));
            j++;
        }
        printf("\n");
        i++;
    }
}
struct statistic_t
{
    int min;
    int max;
    float avg;
    float standard_deviation;
    int range;
};

int save(const char *filename, int **ptr, enum save_format_t format) {
    if (filename == NULL || ptr == NULL) return 1;
    if (format != fmt_binary && format != fmt_text) return 1;
    if (format == fmt_binary) {
        FILE *fp = fopen(filename, "wb");
        if (fp == NULL) return 2;
        int i = 0;
        int one = -1;
        while (*(ptr + i) != NULL) {
            int j = 0;
            while (*(*(ptr + i) + j) != -1) {
                fwrite((*(ptr + i) + j), sizeof(int ), 1, fp);
                j++;
            }
            fwrite(&one, sizeof(int ), 1, fp);
            i++;
        }
        fclose(fp);
    } else {
        FILE *fp = fopen(filename, "w");
        if (fp == NULL) return 2;
        int i = 0;
        while (*(ptr + i) != NULL) {
            int j = 0;
            while (*(*(ptr + i) + j) != -1) {
                fprintf(fp, "%d ", *(*(ptr + i) + j));
                j++;
            }
            fprintf(fp, "-1\n");
            i++;
        }
        fclose(fp);
    }
    return 0;
}
int statistics(int **ptr, struct statistic_t **stats) {
    if (ptr == NULL || stats == NULL) return 1;
    struct statistic_t *pStatistic = malloc(sizeof(struct statistic_t));
    if (pStatistic == NULL) return 2;

    int elements = 0;
    int sum = 0;
    int i = 0;
    if (*ptr == NULL) {
        free(pStatistic);
        return 3;
    }
    pStatistic->min = *(*(ptr + 0) + 0);
    pStatistic->max = *(*(ptr + 0) + 0);
    while (*(ptr + i) != NULL) {
        int j = 0;
        while (*(*(ptr + i) + j) != -1) {
            //
            elements++;
            sum += *(*(ptr + i) + j);
            if (pStatistic->min > *(*(ptr + i) + j)) pStatistic->min = *(*(ptr + i) + j);
            if (pStatistic->max < *(*(ptr + i) + j)) pStatistic->max = *(*(ptr + i) + j);
            //
            j++;
        }
        i++;
    }
    if (elements == 0) {
        free(pStatistic);
        return 3;
    }
    pStatistic->avg = (float) sum / (float) elements;
    i = 0;
    float SD = 0.0;
    while (*(ptr + i) != NULL) {
        int j = 0;
        while (*(*(ptr + i) + j) != -1) {
            // standard_deviation
            SD += pow( (float) *(*(ptr + i) + j) - pStatistic->avg, 2);
            j++;
        }
        i++;
    }
    pStatistic->standard_deviation = sqrtf(SD / (float) elements);
    pStatistic->range = pStatistic->max - pStatistic->min;
    *stats = pStatistic;
    return 0;
}

int main() {
    int A[] = {10, 20, 30, 40, 50, 60, 70, -1};
    int B[] = {100, 200, 300, 400, 500, 600, 700, 800, -1};
    int C[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, -1};
    int* D[] = {A, B, C, NULL};
    display(D);
    char *filename = malloc(sizeof(char) * 40);
    if (filename == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Zapodaj nazwe pliku: ");
    scanf("%39s", filename);

    char *f_name_txt = malloc(sizeof(char ) * strlen(filename) + strlen(".txt") + 1);
    if (f_name_txt == NULL) {
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }
    strcpy(f_name_txt, filename);
    strcat(f_name_txt, ".txt");
    char *f_name_bin = malloc(sizeof(char ) * strlen(filename) + strlen(".bin") + 1);
    if (f_name_bin == NULL) {
        printf("Failed to allocate memory");
        free(filename);
        free(f_name_txt);
        return 8;
    }
    strcpy(f_name_bin, filename);
    strcat(f_name_bin, ".bin");
    int res = save(f_name_txt, D, fmt_text);
    if (res != 0) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    res = save(f_name_bin, D, fmt_binary);
    if (res != 0) {
        printf("Couldn't create file\n");
    } else {
        printf("File saved\n");
    }
    struct statistic_t *statistic;
    statistics(D, &statistic);
    printf("%d\n", statistic->min);
    printf("%d\n", statistic->max);
    printf("%d\n", statistic->range);
    printf("%f\n", statistic->avg);
    printf("%f\n", statistic->standard_deviation);
    free(statistic);
    free(filename);
    free(f_name_txt);
    free(f_name_bin);
    return 0;
}