#include <stdio.h>
#include <string.h>
#include "file_utils.h"
int main(){
    printf("zapodaj:\n");
    char file_name[31];
    scanf("%30s", file_name);

    FILE *f; f = fopen(file_name, "r");
    if (f == NULL) {
        printf("couldn't open file");
        return 4;
    } else {
        fclose(f);
        printf("%d", read_file(file_name));
    }

    return 0;
}
