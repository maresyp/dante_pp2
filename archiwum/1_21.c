#include <stdio.h>
#include <string.h>
#include "../file_utils.h"
#include <ctype.h>

int main(){
    int tmp;
    char ch;

    printf("Podaj sciezke do pliku:\n");
    char file_name[31];
    scanf("%30s", file_name);

    FILE *f_index; f_index = fopen(file_name, "r");
    if (f_index == NULL) {
        printf("Couldn't open file");
        return 4;
    }
    if (fscanf(f_index, "%d", &tmp) <= 0) {
        printf("File corrupted");
        fclose(f_index);
        return 6;
    }
    fseek(f_index, 0, SEEK_SET);
    int min = tmp, max = tmp;
    while (fscanf(f_index, "%d", &tmp) > 0) {
        if (max < tmp) max = tmp;
        if (min > tmp) min = tmp;
    }

    /*

    printf("min          -> %d\n", min);
    printf("max          -> %d\n", max);
    printf("file_size    -> %d\n", file_size_from_file(f_index));
    printf("file_pointer -> %ld\n", ftell(f_index));

    */

    if (ftell(f_index) > min || max > file_size_from_file(f_index) - 1) {
        printf("File corrupted");
        fclose(f_index);
        return 6;
    }
    fseek(f_index, 0, SEEK_SET);

    while((ch = fgetc(f_index)) != '\n') {
        if (isalpha(ch)) {
            printf("File corrupted");
            fclose(f_index);
            return 6;
        }
    }

    fseek(f_index, 0, SEEK_SET);
    FILE *fp_letter; fp_letter = fopen(file_name, "r");

    while (fscanf(f_index, "%d", &tmp) > 0) {
        fseek(fp_letter, tmp, SEEK_SET);
        fscanf(fp_letter, "%c", &ch);
        printf("%c", ch);
    }
    fclose(f_index); fclose(fp_letter);
    return 0;
}
