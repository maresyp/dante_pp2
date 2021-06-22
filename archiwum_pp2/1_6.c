#include <stdio.h>
#include <string.h>

void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int main(){
    int number;
    FILE *fp_0; fp_0 = fopen("0.txt", "w");
    FILE *fp_2; fp_2 = fopen("2.txt", "w");
    FILE *fp_3; fp_3 = fopen("3.txt", "w");
    FILE *fp_5; fp_5 = fopen("5.txt", "w");
    if (fp_0 == NULL) {
        printf("couldn't create file");
        return 5;
    }
    if (fp_2 == NULL) {
        fclose(fp_0);
        printf("couldn't create file");
        return 5;
    }
    if (fp_3 == NULL) {
        fclose(fp_0); fclose(fp_2);
        printf("couldn't create file");
        return 5;
    }
    if (fp_5 == NULL) {
        fclose(fp_0); fclose(fp_2); fclose(fp_3);
        printf("couldn't create file");
        return 5;
    }
    printf("Zapodaj liczby:\n");
    while (scanf("%d", &number ) == 1 && number != 0) {
        if (number % 2 == 0) {
            fprintf(fp_2, "%d\n", number);
        }
        if (number % 3 == 0) {
            fprintf(fp_3, "%d\n", number);
        }
        if (number % 5 == 0) {
            fprintf(fp_5, "%d\n", number);
        }
        if (!(number % 2 == 0 || number % 3 == 0 || number % 5 == 0)) {
            fprintf(fp_0, "%d\n", number);
        }
    }
    fclose(fp_0); fclose(fp_2); fclose(fp_3); fclose(fp_5);
    printf("Files saved");
    return 0;
}
