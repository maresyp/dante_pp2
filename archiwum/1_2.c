#include <stdio.h>
#include <string.h>
#include "file_utils.h"

int main(){
    printf("Podaj sciezke do pliku\n");
    char file_name[31];
    fgets(file_name, 31, stdin);
    strtok(file_name, "\n");

    int len_1 = file_size_from_path(file_name);
    FILE *fp; fp = fopen(file_name, "r");
    int len_2 = file_size_from_file(fp);
    if (len_2 < 0 || len_1 < 0) {
        printf("Couldn't open file");
        return 4;
    }
    fclose(fp);
    if (len_1 == len_2) {
        printf("Rozmiar pliku wynosi %d bajtów", len_1);
    } else {
        printf("error");
        return 0;
    }
    return 0;
}
