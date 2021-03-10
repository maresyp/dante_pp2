#include <stdio.h>
#include <string.h>
#include "file_utils.h"

void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(){
    printf("Podaj sciezke do pliku:\n");
    char file_name[31];
    scanf("%30s", file_name);
    clean_stdin();
    FILE *fp; fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Couldn't open file");
        return 4;
    }
    printf("Podaj sciezke do pliku wyjsciowego:\n");
    scanf("%30s", file_name);
    clean_stdin();

    FILE *f_res; f_res = fopen(file_name, "w");
    if (f_res == NULL) {
        printf("Couldn't create file");
        fclose(fp);
        return 5;
    }
    int file_len = file_size_from_file(fp);
    for (int filePos = file_len - 1; filePos >= 0; filePos--) {
        fseek(fp, filePos, SEEK_SET);
        fputc(fgetc(fp), f_res);
    }

    fclose(f_res);
    fclose(fp);
    printf("File copied");
    return 0;
}
