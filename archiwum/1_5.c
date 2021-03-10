#include <stdio.h>
#include <string.h>

void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(){
    char file_name[31];
    printf("Podaj sciezke do pliku wyjsciowego:\n");
    scanf("%30s", file_name);
    clean_stdin();

    FILE *f_res; f_res = fopen(file_name, "w");
    if (f_res == NULL) {
        printf("Couldn't create file");
        return 5;
    }
    for (int i = 0; i < 101; ++i) {
        fprintf(f_res, "%d\n", i);
    }

    fclose(f_res);
    printf("File saved");
    return 0;
}
