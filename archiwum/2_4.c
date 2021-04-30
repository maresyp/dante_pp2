#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_struct_utils.h"

int main() {
    printf("zapodaj nazwe pliku: ");
    char filename[100];
    scanf("%99s", filename);
    FILE *fp; fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Couldn't open file");
        return 4;
    }
    // check if file is corrupted
    struct point_t tmp, tmp2;
    int points_count = 0;
    int res = EOF;
    do {
        res = fscanf(fp, "%d %d", &tmp.x, &tmp.y);
        if (res == EOF) break;
        if (res != 2) {
            fclose(fp);
            printf("File corrupted");
            return 6;
        }
        points_count++;
    } while (feof(fp) == 0);
    rewind(fp);
    // handle when there is not enough points
    if (points_count < 2) {
        fclose(fp);
        printf("File corrupted");
        return 6;
    }

    struct point_t first, second;
    float temp;
    int err_code;
    float min_dist = distance(&tmp2, &tmp, &err_code);
    FILE *fp2; fp2 = fopen(filename, "r");
    int element_id = 0;
    int inner_element_id = 0;
    do {
        fscanf(fp, "%d %d", &tmp2.x, &tmp2.y);
        if (feof(fp)) break;
        // compare other points to first
        //printf("%d %d\n" , tmp2.x, tmp2.y);
        inner_element_id = 0;
        do {
            fscanf(fp2, "%d %d", &tmp.x, &tmp.y);
            if (feof(fp2)) break;
            // Calculate distance between points
            if (element_id == inner_element_id) {
                inner_element_id++;
                continue;
            } // don't check point against itself
            temp = distance(&tmp2, &tmp, &err_code);
            // handle when distance is the same as previous
            if (temp <= min_dist) {
                if (temp == min_dist) {
                    if (tmp.x > second.x || tmp2.x > first.x) {
                        inner_element_id++;
                        continue;
                    }
                }
                min_dist = temp;
                second.x = tmp.x; second.y = tmp.y;
                first.x = tmp2.x; first.y = tmp2.y;
            }
            inner_element_id++;
        } while (feof(fp2) == 0);
        rewind(fp2);
        element_id++;
    } while (feof(fp) == 0);
    printf("%d %d %d %d", second.x, second.y, first.x, first.y);

    fclose(fp);
    fclose(fp2);
    return 0;
}