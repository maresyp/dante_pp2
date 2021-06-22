#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct message_t
{
    char a;
    double b;
    int c;
};
/*
int check_for_elements(const char *filename) {
    if (filename == NULL) return -1;
    FILE *fp; fp = fopen(filename, "rb");
    if (fp == NULL) return -2;
    unsigned int amount_of_data;
    int elements_read = 0;

    while (1) {
        fread(&amount_of_data, sizeof(unsigned int), 1, fp);
        amount_of_data *= 8;
        if (amount_of_data % 24 != 0 || amount_of_data < 24) {
            fclose(fp);
            return -3;
        }

        for (int j = 0; j < (int) (amount_of_data / 24); ++j) {
            struct message_t message;
            if (fread(&message, sizeof(struct message_t), 1, fp) != 1) {
                fclose(fp);
                rewind(fp);
                return elements_read;
            } else {
                elements_read++;
            }
        }
    }
}

 */
int load_data(struct message_t *cp, int size, const char *filename) {
    if (size <= 0 || cp == NULL || filename == NULL) return -1;
    FILE *fp; fp = fopen(filename, "rb");
    if (fp == NULL) return -2;

    unsigned int amount_of_data;
    int elements_read = 0;

    for (int i = 0; i < size; ++i) {
        fread(&amount_of_data, sizeof(unsigned int), 1, fp);
        amount_of_data *= 8;
        if (amount_of_data % 24 != 0 || amount_of_data < 24) {
            fclose(fp);
            return -3;
        }
        for (int j = 0; j < (int)(amount_of_data / 24); ++j) {
            if (elements_read >= size) break;
            if (fread((cp + i++), sizeof(struct message_t), 1, fp) != 1) {
                if (feof(fp) != 0) {
                    fclose(fp);
                    return elements_read;
                }
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

    for (int i = 0; i < size; ++i) {
        unsigned char bytes[24];
        memcpy(bytes, (cp + i), 24);

        for (int j = 1; j <= 7; ++j) {
            if (text_size <= 1) {
                *msg = '\0';
                return 0;
            }
            *msg++ = (char) *(bytes + j);
            text_size--;

        }
        for (int j = 20; j <= 23; ++j) {
            if (text_size <= 1) {
                *msg = '\0';
                return 0;
            }
            *msg++ = (char) *(bytes + j);
            text_size--;

        }
    }
    return 0;
}

int main() {
    struct message_t message[100];
    printf("Zapodaj: ");
    char filename[31];
    scanf("%30s", filename);
    // TODO: Calculate how many elements to read
    //int res = check_for_elements(filename);

    int res = load_data(message, 100, filename);
    if (res == -2) {
        printf("Couldn't open file");
        return 4;
    }
    if (res == -3) {
        printf("File corrupted");
        return 6;
    }
    char mess[1101];
    decode_message(message, res, mess, 1101);
    printf("%s", mess);
    return 0;

}