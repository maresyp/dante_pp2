#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct entry_t {
    char name[20];
    char last_name[40];
    int number;
};
void display(const struct entry_t* p) {
    if (p == NULL) return;
    printf("Name: %s\nLast Name: %s\nPhone number: %d", p->name, p->last_name, p->number);
}
int load_phonebook_t(const char *filename, struct entry_t* p, int size) {
    if (filename == NULL || p == NULL || size <= 0) return -1;
    FILE *fp; fp = fopen(filename, "r");
    if (fp == NULL) return -2;
    int records = 0;
    while (1) {
        fscanf(fp, "%[^|]19s %[^|]39s %d", (p + records)->name, (p + records)->last_name, &(p + records)->number);
        if (feof(fp) != 0) break;
        records++;
    }
    fclose(fp);
    return records;
}
const struct entry_t* find_by_last_name(const struct entry_t* p, int size, const char *last_name) {
    return p;
}

int main() {
    struct entry_t str[4];
    int res = load_phonebook_t("../file.txt", str, 4);
    return 0;
}