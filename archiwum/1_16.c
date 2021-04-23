#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
    char file_name[31];
    printf("zapodaj:");
    scanf("%30s", file_name);
    FILE *fp; fp = fopen(file_name, "r");
    if (fp == NULL) {
        fp = fopen(file_name, "w");
        if (fp == NULL) {
            printf("Couldn't create file");
            return 5;
        } else {
            fclose(fp);
        }
        printf("File created");
    } else {
        fclose(fp);
        printf("File already exists!");
    }
    return 0;
}
