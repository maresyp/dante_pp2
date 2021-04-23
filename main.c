#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t *cp, int size, const char *filename) {
    if (size <= 0 || cp == NULL || filename == NULL) return -1;
    FILE *fp; fp = fopen(filename, "rb");
    if (fp == NULL) return -2;


    unsigned int amount_of_data;
    int elements_read = 0;

    for (int i = 0; i < size; ++i) {
        fread(&amount_of_data, sizeof(unsigned int), 1, fp);
        amount_of_data *= 8;
        if (amount_of_data % 24 != 0 || amount_of_data < 24) return -3;
        for (int j = 0; j < (int)(amount_of_data / 24); ++j) {
            if (elements_read >= size) break;
            if (fread((cp + i++), sizeof(struct message_t), 1, fp) != 1) {
                fclose(fp);
                return -3;
            } else {
                elements_read++;
            }
        }
    }
    fclose(fp);
    return elements_read;
}

int decode_message(const struct message_t *cp, int size, char *msg, int text_size) {
    if (cp == NULL || size <= 0 || msg == NULL || text_size <= 0) return 1;

    FILE *fp; fp = tmpfile();
    for (int i = 0; i < size; ++i) {
        fwrite((cp + i), sizeof(struct message_t), 1, fp);
        fseek(fp, 12, SEEK_SET);
        fread(msg +(i * 11), 11, 1, fp);
    }
    return 0;
}

int main() {

    return 0;

}