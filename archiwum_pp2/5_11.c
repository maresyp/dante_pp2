#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define MAX_ALLOC 50

//int read_char(char * txt, size_t * max_size) {
//    if (txt == NULL || *max_size < MAX_ALLOC) return 1;
//    if (strlen(txt) + 2 > *max_size) { // try to alloc more memory
//        char * tmp = realloc(txt, *max_size + MAX_ALLOC);
//        if (tmp == NULL) { return 2; }
//        else {
//            txt = tmp;
//            *max_size = *max_size + MAX_ALLOC;
//        }
//    }
//    char c = getc(stdin); if (c == '\n') return 3;
//    strncat(txt, &c, 1);
//    return 0;
//}
int main() {
    char * text = realloc(NULL, MAX_ALLOC);
    size_t size = MAX_ALLOC;
    if (text == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj tekst: ");
    while (1) {
        if (strlen(text) + 2 > size) { // try to alloc more memory
            char * tmp = realloc(text, size + MAX_ALLOC);
            if (tmp == NULL) { break; }
            else {
                text = tmp;
                size = size + MAX_ALLOC;
            }
        }
        char c = getc(stdin); if (c == '\n') break;
        strncat(text, &c, 1);
    }
    printf("%s", text);
    free(text);
    return 0;
}