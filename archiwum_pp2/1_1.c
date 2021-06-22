#include <stdio.h>
#include <string.h>

int main() {
    printf("Podaj sciezke do pliku\n");
    char ch, file_name[31];
    fgets(file_name, 31, stdin);
    strtok(file_name, "\n"); // remove '\n' from the end of text

    FILE *fp; fp = fopen(file_name, "r");

    if (fp == NULL) { // check if file opened successfully
        printf("Couldn't open file");
        return 4;
    } else {
        fseek(fp, 0, SEEK_END); // check if file is 0 bytes long
        unsigned long len = (unsigned long)ftell(fp);
        if (len == 0) {
            printf("nothing to show");
        } else {
            rewind(fp); // !! return to the beginning of file
            while((ch = fgetc(fp)) != EOF)
                printf("%c", ch);
        }
    }
    fclose(fp);
    return 0;
}
