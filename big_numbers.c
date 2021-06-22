//
// Created by Mateusz Pysera on 28/05/2021.
//

#include "big_numbers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validate(const char *number) {
    if (number == NULL) return -1;
    if (strlen(number) <= 0 ) return 2;
    if (*(number) == 48 && strlen(number) > 1) return 2; // in case 0123 -> not valid
    if (*(number) == 45 && strlen(number) == 1) return 2; // in case alone minus sign
    size_t iterator = 0;
    if (*(number) == 45 && *(number + 1) == 48) return 2; // case -0 -> not valid
    if (*(number) == 45) iterator++; // ignore first char as it is minus sign
    for (; iterator < strlen(number); ++iterator) {
        if (isdigit(*(number + iterator)) == 0) return 2;
    }
    return 0;
}
int compare(const char* number1, const char* number2) {
    if (number1 == NULL || number2 == NULL) return 2;
    if (validate(number1) != 0 || validate(number2) != 0) return 3;
    if (*(number1) == '-' && *number2 != '-') return -1;
    if (*(number1) != '-' && *number2 == '-') return 1;
    if (strlen(number1) == strlen(number2)) {
        // len of numbers is the same -> look for first bigger digit
        if (*number1 == '-' && *number2 == '-') { // in case both are negative
            for (size_t i = 0; i < strlen(number1); ++i) {
                if (*(number1 + i) > *(number2 + i)) return -1;
                if (*(number1 + i) < *(number2 + i)) return 1;
            }
        } else {
            for (size_t i = 0; i < strlen(number1); ++i) {
                if (*(number1 + i) > *(number2 + i)) return 1;
                if (*(number1 + i) < *(number2 + i)) return -1;
            }
        }
        return 0;
    }
    else if (*number1 == '-' && *number2 == '-'){
        if (strlen(number1) > strlen(number2)) return -1;
        else return 1;
    }
    else if (strlen(number1) > strlen(number2)) return 1;
    else if (strlen(number1) < strlen(number2)) return -1;
    return 0;
}
void str_rev(char * str) {
    if (str == NULL || strlen(str) == 0) return;
    char * start = str;
    char * end = start + strlen(str) - 1;
    char temp;

    while (end > start) {
        temp = *start;
        *start = *end;
        *end = temp;
        ++start;
        --end;
    }
}
int char_push_back(char value, char * str, size_t space) {
    if (str == NULL || space <= 0) return 1;
    if (strlen(str) + 1 > space) return 2;
    strncat(str, &value, 1);
    return 0;
}
int char_push_front(char value, char * str, size_t space) {
    if (str == NULL || space <= 0) return 1;
    if (strlen(str) + 1 > space) return 2;
    // shift all elements to right
    for (int i = (int) strlen(str); i >= 0; --i) {
        *(str + i + 1) = *(str + i);
    }
    *(str) = value;
    return 0;
}
char digit_to_char(int value) {
    if (value == 0) return '0';
    if (value == 1) return '1';
    if (value == 2) return '2';
    if (value == 3) return '3';
    if (value == 4) return '4';
    if (value == 5) return '5';
    if (value == 6) return '6';
    if (value == 7) return '7';
    if (value == 8) return '8';
    if (value == 9) return '9';
    return '?';
}
int remove_leading_zeros(char * str) {
    if (str == NULL) return 1;
    if (strlen(str) > 1) {
        // shift to left until non zero
        while (*(str) == '0') {
            for (size_t i = 0; i < strlen(str); ++i) {
                *(str + i) = *(str + i + 1);
            }
        }
    }
    *(str + strlen(str)) = '\0';
    return 0;
}
int subtract(const char* number1, const char* number2, char** result) {
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    if (validate(number1) != 0 || validate(number2) != 0) return 2;
    /*
     * Look for all cases before calculation
     * + + -> calculate normally
     * + - -> call add -> number1 + number2 ( with changed sign )
     * - + -> call add -> number1 + number2 ( without signs ) -> add minus sign to result
     * - - -> number2 - number1
     */
    if (*(number1) != 45 && *(number2) != 45) { // both are positive numbers
        int carry = 0;
        /*
         * 5 - 10 = -5
         * 10 - 5 = 5
         */
        int cmp = compare(number1, number2);
        size_t min, max;
        if (cmp == 0) { // both numbers are equal
            *result = calloc(strlen(number1) + 3, 1); if (*result == NULL) return 3;
            // result of 2 identical numbers is always 0
            strcpy(*result, "0");
            return 0;
        } else if (cmp == 1) { // number1 > number2  * base case *
            *result = calloc(strlen(number1) + 3, 1); if (*result == NULL) return 3;
            max = strlen(number1); min = strlen(number2);
            int diff = (int)(max - min);
            for (int i = (int)(min - 1); i >= 0; i--) {
                int sub = (*(number1 + (i + diff)) - '0') - (*(number2 + i) - '0') - carry;
                if (sub < 0) {
                    sub = sub + 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                char_push_back(digit_to_char(sub), *result, max + 3);
//                if (i >= 0 && sub == 0) { char_push_back('0', *result, max + 3); }
//                while (sub > 0) {
//                    int digit = sub % 10;
//                    char_push_back(digit_to_char(digit), *result, max + 3);
//                    sub /= 10;
//                }
            }
            for (int i = diff - 1; i >= 0; i--) {
                if (*(number1 + i) == '0' && carry) {
                    char_push_back('9', *result, max + 3);
                    continue;
                }
                int sub = ((*(number1 + i) - '0') - carry);
                if (i > 0 || sub > 0) {
                    char_push_back(digit_to_char(sub), *result, max + 3);
//                    while (sub > 0) {
//                        int digit = sub % 10;
//                        char_push_back(digit_to_char(digit), *result, max + 3);
//                        sub /= 10;
//                    }
                }
                carry = 0;
            }
            str_rev(*result);
            remove_leading_zeros(*result);
        } else { // number2 > number1
            // TODO: change
            int res = subtract(number2, number1, result);
            size_t space = (strlen(number1) > strlen(number2) ? strlen(number1) : strlen(number2));
            if (res != 0) return res;
            else {
                char_push_front('-', *result, space + 3);
                return 0;
            }
        }

    }
    if (*(number1) != 45 && *(number2) == 45) { // second number is negative, first positive
        return add(number1, number2 + 1, result);
    }
    if (*(number1) == 45 && *(number2) != 45) { // first negative, second positive
        int res = add(number1 + 1, number2, result);
        size_t max = (strlen(number1) > strlen(number2) ? strlen(number1) : strlen(number2));
        if (res != 0) return res;
        else {
            char_push_front('-', *result, max + 3);
            return 0;
        }
    }
    if (*(number1) == 45 && *(number2) == 45) { // both negative
        // -5 - -10 = 5
        // 10 - 5 = 5
        // -9 - -4 = -5
        // 4 - 9 = -5
        return subtract(number2 + 1, number1 + 1, result);
    }
    return 0;
}
int add(const char* number1, const char* number2, char** result) {
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    if (validate(number1) != 0 || validate(number2) != 0) return 2;
    /*
     * Look for all cases before calculation
     * + + -> calculate normally
     * + - -> call subtract -> number1 - number2
     * - + -> call subtract -> number2 - number1
     * - - -> calculate without signs and add minus to result
     */
    int carry = 0;
    int flag; // 0 when number1 is longer than number 2 // 1 when number2 is longer than number1
    if (*(number1) != 45 && *(number2) != 45) { // both are positive numbers
        size_t min, max;
        if (strlen(number1) > strlen(number2)) { max = strlen(number1); min = strlen(number2); flag = 0; }
        else { max = strlen(number2); min = strlen(number1); flag = 1;}
        int diff = (int)(max - min);
        *result = calloc(max + 3, 1); if (*result == NULL) return 3;
        for (int i = (int)(min - 1); i >= 0; i--) {
            int sum;
            if (flag) sum = (*(number1 + i) - '0') + (*(number2 + i + diff) - '0') + carry;
            else sum = (*(number2 + i) - '0') + (*(number1 + i + diff) - '0') + carry;
            char_push_back(digit_to_char(sum % 10), *result, max + 3);
            carry = sum / 10;
        }
        for (int i = diff - 1; i >= 0; i--) {
            int sum;
            if (flag) sum = (*(number2 + i) - '0') + carry;
            else sum = (*(number1 + i) - '0') + carry;
            char_push_back(digit_to_char(sum % 10), *result, max + 3);
            carry = sum / 10;
        }
        // split carry into digits and write them to result one by one
        while (carry > 0) {
            int digit = carry % 10;
            char_push_back(digit_to_char(digit), *result, max + 3);
            carry /= 10;
        }
        str_rev(*result); // reverse string at the end
        remove_leading_zeros(*result);
    }
    if (*(number1) != 45 && *(number2) == 45) { // second number is negative, first positive
        return subtract(number1, number2 + 1, result);
    }
    if (*(number1) == 45 && *(number2) != 45) { // first negative, second positive
        return subtract(number2, number1 + 1, result);
    }
    if (*(number1) == 45 && *(number2) == 45) { // both negative
        size_t min, max;
        const char * a = number1 + 1;
        const char * b = number2 + 1;
        if (strlen(a) > strlen(b)) { max = strlen(a); min = strlen(b); flag = 0; }
        else { max = strlen(b); min = strlen(a); flag = 1;}
        int diff = (int)(max - min);
        *result = calloc(max + 3, 1); if (*result == NULL) return 3;
        for (int i = (int)(min - 1); i >= 0; i--) {
            int sum;
            if (flag) sum = (*(a + i) - '0') + (*(b + i + diff) - '0') + carry;
            else sum = (*(b + i) - '0') + (*(a + i + diff) - '0') + carry;
            char_push_back(digit_to_char(sum % 10), *result, max + 3);
            carry = sum / 10;
        }
        for (int i = diff - 1; i >= 0; i--) {
            int sum;
            if (flag) sum = (*(b + i) - '0') + carry;
            else sum = (*(a + i) - '0') + carry;
            char_push_back(digit_to_char(sum % 10), *result, max + 3);
            carry = sum / 10;
        }
        // split carry into digits and write them to result one by one
        while (carry > 0) {
            int digit = carry % 10;
            char_push_back(digit_to_char(digit), *result, max + 3);
            carry /= 10;
        }
        char_push_back('-', *result, max + 3); // ad minus sign
        str_rev(*result); // reverse string at the end
        remove_leading_zeros(*result);

    }
    return 0;
}

int create(struct big_numbers_t *bn, int capacity) {
    if (bn == NULL || capacity <= 0) return 1;
    bn->big_number = (char **) malloc(capacity * sizeof(char *));
    if (bn->big_number == NULL) return 2;
    for (int i = 0; i < capacity; ++i) {
        *(bn->big_number + i) = NULL;
    }
    bn->size = 0;
    bn->capacity = capacity;
    return 0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity) {
    if (bn == NULL || capacity <= 0) return 1;
    *bn = malloc(sizeof(struct big_numbers_t));
    if (*bn == NULL) {
        *bn = NULL;
        bn = NULL;
        return 2;
    }
    if (create(*bn, capacity) != 0) {
        free(*bn);
        *bn = NULL;
        bn = NULL;
        return 2;
    }
    return 0;
}

void destroy(struct big_numbers_t *bn) {
    if (bn == NULL || bn->big_number == NULL || bn->size < 0 || bn->capacity <= 0 || bn->size > bn->capacity) return;
    for (int i = 0; i < bn->capacity; ++i) {
        free(*(bn->big_number + i));
    }
    free(bn->big_number);
}

void destroy_big_numbers(struct big_numbers_t **bn) {
    if (bn == NULL || *bn == NULL || (*bn)->big_number == NULL || (*bn)->size < 0 || (*bn)->capacity <= 0 || (*bn)->size > (*bn)->capacity) return;
    destroy(*bn);
    free(*bn);
    *bn = NULL;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number) {
    if (bn == NULL || bn->big_number == NULL || big_number == NULL || bn->size < 0 || bn->capacity <= 0 || bn->size > bn->capacity) return 1;
    if (validate(big_number) != 0) return 1;
    if (bn->size + 1 > bn->capacity) return 3;
    *(bn->big_number + bn->size) = malloc(strlen(big_number) + 1);
    if (*(bn->big_number + bn->size) == NULL) return 2;
    strcpy(*(bn->big_number + bn->size), big_number);
    bn->size = bn->size + 1;
    return 0;
}

void display(const struct big_numbers_t *bn) {
    if (bn == NULL || bn->big_number == NULL || bn->size < 0 || bn->capacity <= 0 || bn->size > bn->capacity) return;
    for (int i = 0; i < bn->size; ++i) {
        if (validate(*(bn->big_number + i)) != 0) return;
    }
    for (int i = 0; i < bn->size; ++i) {
        printf("%s\n", *(bn->big_number + i));
    }
}

int save_big_numbers_b(const struct big_numbers_t *bn, const char *filename) {
    if (bn == NULL || filename == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity) return 1;
    FILE * fp; fp = fopen(filename, "wb");
    if (fp == NULL) return 2;
    fwrite(&bn->size, 4, 1, fp);
    for (int i = 0; i < bn->size; ++i) {
        int len = (int) strlen(*(bn->big_number + i));
        fwrite(&len, 4, 1, fp);
        fwrite(*(bn->big_number + i), 1, len, fp);
    }
    fclose(fp);
    return 0;
}
int load_big_numbers_b(struct big_numbers_t **bn, const char *filename) {
    if (bn == NULL || filename == NULL) return 1;
    FILE * fp; fp = fopen(filename, "rb");
    if (fp == NULL) return 3;

    int amount;
    fread(&amount, 4, 1, fp);
    if (ferror(fp) != 0 || feof(fp) != 0 ) { fclose(fp); return 4; }
    if (amount <= 0) {
        fclose(fp);
        return 4;
    }
    int res = create_big_numbers(bn, amount);
    if (res != 0) {
        fclose(fp);
        return res;
    }

    int size;
    char * number = NULL;
    for (int i = 0; i < amount; ++i) {
        fread(&size, 4, 1, fp);
        if (ferror(fp) != 0 || feof(fp) != 0 || size <= 0) { fclose(fp); destroy_big_numbers(bn); return 4;}
        number = malloc(size + 1); if (number == NULL) {
            fclose(fp);
            destroy_big_numbers(bn);
            return 2;
        }
        fread(number, 1, size, fp);
        if (ferror(fp) != 0 || feof(fp) != 0 ) { fclose(fp); destroy_big_numbers(bn); free(number); return 4;}
        *(number + size) = '\0';
        if (validate(number) != 0) { fclose(fp); destroy_big_numbers(bn); free(number); return 4;}
        *((*bn)->big_number + i) = number;
        (*bn)->size = (*bn)->size + 1;
    }
    fclose(fp);
    return 0;
}
int sort_big_numbers_asc(struct big_numbers_t *bn) {
    if (bn == NULL || bn->big_number == NULL || bn->size < 0 || bn->capacity <= 0 || bn->size > bn->capacity) return 1;
    for (int i = 0; i < bn->size - 1; ++i) {
        for (int j = 0; j < bn->size - i - 1; ++j) {
            int cmp = compare(*(bn->big_number + j), *(bn->big_number + j + 1));
            if (cmp == 3) return 1;
            if (cmp == 1) { //swap
                char * tmp = *(bn->big_number + j);
                *(bn->big_number + j) = *(bn->big_number + j + 1);
                *(bn->big_number + j + 1) = tmp;
            }
        }
    }
    return 0;
}
char* total_sum_big_numbers(const struct big_numbers_t *bn, int *err_code) {
    if (err_code != NULL) *err_code = 0;
    if (bn == NULL || bn->big_number == NULL || bn->size < 0 || bn->capacity <= 0 || bn->size > bn->capacity) {
        if (err_code != NULL) *err_code = 1;
        return NULL;
    }
    char * main_result = malloc(2);
    if (main_result == NULL) {
        if (err_code != NULL) *err_code = 3;
        return NULL;
    }
    sprintf(main_result, "%s", "0");
    size_t main_size = 2;
    char * tmp_result;
    for (int i = 0; i < bn->size; ++i) {
        int err = add(main_result, *(bn->big_number + i), &tmp_result);
        if (err == 2) {
            if (err_code != NULL) *err_code = 2;
            free(main_result);
            return NULL;
        }
        if (err == 3) {
            if (err_code != NULL) *err_code = 3;
            free(main_result);
            return NULL;
        }
        if (strlen(tmp_result) + 1 > main_size) { // add memory
            char * after_alloc = realloc(main_result, strlen(tmp_result) + 1);
            if (after_alloc == NULL) {
                if (err_code != NULL) *err_code = 3;
                free(main_result);
                return NULL;
            } else {
                main_result = after_alloc;
            }
        }
        strcpy(main_result, tmp_result);
        free(tmp_result);
    }
    return main_result;
}
int multiply(const char* number1, const char* number2, char** result) {
    if (number1 == NULL || number2 == NULL || result == NULL) return 1;
    if (validate(number1) != 0 || validate(number2) != 0) return 2;
    /*
     * + + -> calculate normally      -> result positive
     * - - -> calculate without signs -> result positive
     * + - -> calculate without signs -> result negative
     * - + -> calculate without signs -> result negative
     */
    if (*number1 == '0' || *number2 == '0') {
       *result = calloc(2, 1); if (*result == NULL) return 3;
        char_push_back('0', *result, 2);
        return 0;
    }
    if (*number1 != '-' && *number2 != '-') { // base case
        size_t alloc_size = strlen(number1) + strlen(number2) + 2;
        char * correct_result_xd = calloc(alloc_size, 1); if (correct_result_xd == NULL) return 3;
        *result = correct_result_xd;
        size_t len_num1 = strlen(number1);
        size_t len_num2 = strlen(number2);
        int index_number1 = 0;
        int index_number2 = 0;
        for (int i = (int)(len_num1 - 1); i >= 0; i--) {
            int carry = 0;
            int n1 = *(number1 + i) - '0';
            index_number2 = 0;

            for (int j = (int)(len_num2 - 1); j >= 0; j--) {
                int n2 = *(number2 + j) - '0';
                int tmp;
                if (index_number1 == 0 && index_number2 == 0) tmp = 0;
                else {
                    if ( *(correct_result_xd + (index_number1 + index_number2)) == '\0') tmp = 0;
                    else tmp = *(correct_result_xd + (index_number1 + index_number2)) - '0';
                }
                int sum = n1 * n2 + tmp + carry;
                carry = sum / 10;
                //char_push_back(digit_to_char(sum % 10), *result, alloc_size);
                *(correct_result_xd + (index_number1 + index_number2)) = digit_to_char(sum % 10);
                index_number2++;
            }
            if (carry > 0) {
                int tmp;
                if (*(correct_result_xd + (index_number1 + index_number2)) == '\0') tmp = 0 + carry;
                else tmp = *(correct_result_xd + (index_number1 + index_number2)) - '0' + carry;
                *(correct_result_xd + (index_number1 + index_number2)) = digit_to_char(tmp);
            }
            index_number1++;
        }
        str_rev(*result);
        remove_leading_zeros(*result);
    } else if (*number1 == '-' && *number2 == '-') { // both negative
        multiply((number1 + 1), (number2 + 1), result);
    } else if (*number1 != '-' && *number2 == '-') { // second negative
        int res = multiply(number1, (number2 + 1), result);
        size_t space = strlen(number1) + strlen(number2) + 2;
        if (res != 0) return res;
        else {
            char_push_front('-', *result, space);
            return 0;
        }

    } else if (*number1 == '-' && *number2 != '-') { // first negative
        int res = multiply((number1 + 1), number2, result);
        size_t space = strlen(number1) + strlen(number2) + 2;
        if (res != 0) return res;
        else {
            char_push_front('-', *result, space);
            return 0;
        }
    }
    return 0;
}
int validate_expression(const char *expr) {
    if (expr == NULL) return 2;
    if (strlen(expr) == 0) return 1;
    if (*expr == '*' || *expr == '+') return 1;
    // go to next sign and check number on the way
    for (int i = 0; i < (int)(strlen(expr)); ++i) {
        // go to next operator
        if (*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*') {
            // check if next char after operator is allowed char ( - )
            if (isdigit(*(expr + i + 1)) == 0 && *(expr + i + 1) != '-') return 1;
            if (*(expr + i + 1) == '0') { // check for 012 number
                if ((i + 1) < (int)(strlen(expr) - 1)) {
                    if (isdigit(*(expr + i + 2)) != 0) return 1;
                }
            }
        } else {
            if (isdigit(*(expr + i)) == 0) return 1;
        }
    }
    return 0;
}
int calculate(const char* expr, char **result) {
    if (expr == NULL || result == NULL) return 1;
    if (validate_expression(expr) != 0) return 2;
    // find first operator
    int first_operator = -1;
    for (int i = 0; i < (int)strlen(expr); ++i) {
        if (*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*') {
            if (i == 0) continue;
            first_operator = i;
            break;
        }
    }
    if (first_operator == -1) {
        *result = calloc(strlen(expr) + 1, 1); // alloc memory for first token
        if (*result == NULL) return 3;
        strcpy(*result, expr);
        return 0;
    }
    *result = calloc(first_operator + 1, 1); // alloc memory for first token
    if (*result == NULL) return 3;
    strncpy(*result, expr, first_operator);
    if (first_operator == -1) return 0;
    int index_of_operator = 0;
    do {
        char operator;
        short operator_found = 0;
        int eoe = -1; // end of expr
        // find next operator
        for (int i = index_of_operator + 1; i < (int) strlen(expr); ++i) {
            if (*(expr + i) == '-' || *(expr + i) == '+' || *(expr + i) == '*') {
                if (*(expr + i - 1) == '-' || *(expr + i - 1) == '+' || *(expr + i - 1) == '*') continue;
                if (i == 0) continue;
                index_of_operator = i;
                operator_found = 1;
                operator = *(expr + i);
                // try to find another operator
                for (int j = index_of_operator + 1; j < (int) strlen(expr); ++j) {
                    if (*(expr + j) == '-' || *(expr + j) == '+' || *(expr + j) == '*') {
                        eoe = j;
                        if (index_of_operator + 1 == eoe) {
                            eoe = -1;
                            continue; // ignore 5--5
                        }
                        break;
                    }
                }
                if (eoe == -1) eoe = (int)strlen(expr);
                break;
            }
        }
        if (operator_found == 0) break;
        char *tmp_result = calloc(eoe + 1, 1);
        if (tmp_result == NULL) {
            free(*result);
            return 3;
        }
        strncpy(tmp_result, expr + index_of_operator + 1, eoe - index_of_operator -1);
        char * free_after = *result;
        int err = 0;
        switch (operator) {
            case '-':
                err = subtract(*result, tmp_result, result);
                break;
            case '+':
                err = add(*result, tmp_result, result);
                break;
            case '*':
                err = multiply(*result, tmp_result, result);
                break;
        }
        free(tmp_result);
        free(free_after);
        if (err == 3) {
            free(*result);
            return 3;
        }
        if (eoe == (int) strlen(expr)) break;
    } while (index_of_operator != -1);
    return 0;
}
