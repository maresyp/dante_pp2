#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_struct_utils.h"

struct file_t {
    FILE *f;
    int size;
};

int main(){
    printf("Zapodaj:\n");
    char filename[31];
    int files_opened = 0;
    struct file_t files[5];
    while (1) {
        char c; int count = 0;
        do {
            c = getchar();
            *(filename + count) = c;
            if (c == '\n') break;
            count++;
        } while (c != EOF);
        if (*filename == '\n') break;
        *(filename + count) = '\0';
        if (files_opened < 5) {
            int res = open_file((files + files_opened), filename);
            if (res == 0) files_opened++;
        }
    }
    if (files_opened == 0) {
        printf("Couldn't open file");
        return 4;
    }
    printf("Zapodaj: \n");
    char txt[999];
    while (1) {
        char c; int count = 0;
        do {
            c = getchar();
            *(txt + count) = c;
            if (c == '\n') break;
            count++;
        } while (c != EOF && count < 998);
        if (*txt == '\n') break;
        *(txt + (++count)) = '\0';

        struct file_t *smallest = find_min(files, files_opened);
        fprintf(smallest->f, "%s", txt);
        smallest->size = file_size_from_file(smallest->f);
    }

    for (int i = 0; i < files_opened; ++i) {
        close_file((files + i));
    }

    printf("Files saved");
    return 0;
}
