//
// Created by Mateusz Pysera on 28/05/2021.
//
#include <stdlib.h>
#ifndef DANTE_P2_BIG_NUMBERS_H
#define DANTE_P2_BIG_NUMBERS_H

int validate(const char *number);
int compare(const char* number1, const char* number2);
int subtract(const char* number1, const char* number2, char** result);
int add(const char* number1, const char* number2, char** result);

int char_push_back(char value, char * str, size_t space);

struct big_numbers_t {
    int size;
    int capacity;
    char **big_number;
};

int create(struct big_numbers_t *bn, int capacity);
int create_big_numbers(struct big_numbers_t **bn, int capacity);

void destroy(struct big_numbers_t *bn);
void destroy_big_numbers(struct big_numbers_t **bn);

int add_big_number(struct big_numbers_t *bn, const char *big_number);

void display(const struct big_numbers_t *bn);

int save_big_numbers_b(const struct big_numbers_t *bn, const char *filename);
int load_big_numbers_b(struct big_numbers_t **bn, const char *filename);
int sort_big_numbers_asc(struct big_numbers_t *bn);
char* total_sum_big_numbers(const struct big_numbers_t *bn, int *err_code);

int multiply(const char* number1, const char* number2, char** result);
int validate_expression(const char *expr);
int calculate(const char* expr, char **result);

#endif //DANTE_P2_BIG_NUMBERS_H
