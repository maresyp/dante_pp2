#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void cls(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

struct char_b { const char c[8];};

int encode(const char *input, char *txt, const char *output) {
    if (input == NULL || txt == NULL || output == NULL) return 1;
    FILE *in; in = fopen(input, "r");
    if (in == NULL) return 2;
    FILE *out; out = fopen(output, "w");
    if (out == NULL) { fclose(in); return 4;}

    int space_needed = (int)strlen(txt) * 8; // - 8
    int space_aval = 0;
    int err_code, tmp;
    while (1) {
        err_code = fscanf(in, "%d", &tmp);
        if (err_code == EOF) break;
        if (err_code != 1) {
            fclose(in);
            fclose(out);
            return 3;
        }
        space_aval++;
    }
    rewind(in);
    if (space_aval < space_needed) {fclose(in); fclose(out); return 3; }
    int num; unsigned int lsb; int c;
    int s_len = strlen(txt);

    for (int i = 0; i < s_len; ++i) { // iterate over every char
        // change char to its binary representation
        for (int j = 7; j >= 0; --j) {
            lsb = (*(txt + i) & (1u << j)) != 0;
            fscanf(in, "%d" , &num);
            if (lsb == 1){
                num = num | 1;
            }
            else{
                num = num & ~1;
            } // encode next bit of char
            fprintf(out, "%d", num);

            c = fgetc(in);
            while (isdigit(c) == 0 && c != EOF) {
                fprintf(out, "%c", (char)c);
                c = fgetc(in);
            }
            if (isdigit(c) != 0){
                ungetc(c, in);
            }
        }
    }

    for (int i = 0; i < space_aval - space_needed; ++i){
        fscanf(in, "%d" , &num);
        if (num & 1){
            num = num ^ 1;
        }
        else{
            num = num & ~1;
        }
        num = num & ~1;
        fprintf(out, "%d", num);
        c = fgetc(in);
        while (isdigit(c) == 0 && c != EOF) {
            fprintf(out, "%c", (char)c);
            c = fgetc(in);
        }
        if (isdigit(c) != 0){
            ungetc(c, in);
        }
        if(c == EOF){
            break;
        }
    }

    fclose(in); fclose(out);
    return 0;
}
int decode(const char * filename, char *txt, int size) {
    if (filename == NULL || txt == NULL || size <= 0) return 1;
    FILE *fp; fp = fopen(filename, "r");
    if (fp == NULL) return 2;
    int tmp, err_code;
    // TODO: check if file is valid
    int space_needed = (size * 8) - 8;
    int space_aval = 0;
    while (1) {
        err_code = fscanf(fp, "%d", &tmp);
        if (err_code == EOF) break;
        if (err_code != 1) {
            fclose(fp);
            return 3;
        }
        space_aval++;
    }
    if (space_aval < space_needed) {fclose(fp); return 3; }
    fseek(fp, 0, SEEK_SET);

    FILE *buffer = tmpfile();
    buffer = fopen("b_file", "w");
    int amount = 0, amount_needed = (size * 8) - 8;
    while ((fscanf(fp, "%d", &tmp) != EOF) && (amount++ < amount_needed)) {
        fprintf(buffer, "%d", (tmp & 1));
    }
    buffer = freopen("b_file", "r", buffer);
    struct char_b ch; char *tm;
    for (int i = 0; i < size - 1; ++i) {
        fread(&ch, sizeof(struct char_b), 1, buffer);
        *(txt + i) = strtol(ch.c, &tm, 2);
    }
    *(txt + (size - 1)) = '\0';
    fclose(fp); fclose(buffer);
    return 0;
}
int main(){
    //char esz[1000];
    //encode("../dane2.txt", "Information technology and business are becoming inextricably interwoven. I don't think anybody can talk meaningfully about one without the talking about the other. - Bill Gates", "../out.txt");
    //decode("../exp.txt", esz, 1000);
    //printf("%s", esz);
    //return 0;

    char in_file[30];
    char out_file[30];
    char txt[1001];
    char c;
    int err_code;

    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    if (scanf("%c", &c) != 1) {
        printf("Incorrect input");
        return 1;
    }

    cls();
    if (c == 'E' || c == 'e') {
        printf("Enter a message to be encoded: ");
        scanf("%1000[^\n]s", txt);
        cls();
        printf("Enter input file name: ");
        if(scanf("%30s", in_file) != 1){
            printf("Incorrect input");
            return 1;
        }
        cls();
        printf("Enter output file name: ");
        if(scanf("%30s", out_file) != 1){
            printf("Incorrect input");
            return 1;
        }

        err_code = encode(in_file, txt, out_file);
        if(err_code == 4){
            printf("Couldn't create file");
            return 5;
        }
        else if(err_code == 2){
            printf("Couldn't open file");
            return 4;
        }
        else if(err_code == 3 || err_code == 1){
            printf("File corrupted");
            return 6;
        }
        else if(err_code == 0){
            printf("File saved");
        }
    } else if (c == 'D' || c == 'd') {
        printf("Enter input file name: ");
        if(scanf("%30s", in_file) != 1){
            printf("Incorrect input");
            return 1;
        }

        err_code = decode(in_file, txt, 1001);
        if(err_code == 2){
            printf("Couldn't open file");
            return 4;
        }
        else if(err_code == 3 || err_code == 1){
            printf("File corrupted");
            return 6;
        }
        else if(err_code == 0){
            printf("%s", txt);
        }
    } else {
        printf("Incorrect input data");
        return 1;
    }

    return 0;
}
