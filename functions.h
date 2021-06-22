//
// Created by Mateusz Pysera on 28/05/2021.
//
#include <stdlib.h>
#ifndef DANTE_P2_FUNCTIONS_H
#define DANTE_P2_FUNCTIONS_H

char **text_modifier(const char  *text, int count, ...);
char *lower_to_upper (const char *in);
char *upper_to_lower (const char *in);
char *space_to_dash (const char *in);
char *reverse_letter (const char *in);
void free_texts(char **);

#define DISPLAY_BITS(value) {                            \
    size_t size = sizeof(value);                         \
    unsigned char byte;                                  \
    for(int i = size - 1; i >= 0; i--) {                 \
        for(int j = 7; j >= 0; j--) {                    \
        byte = ((((value) >> (8 * i)) & 0xff) >> j) & 1; \
        printf("%u", byte);                              \
        }                                                \
    }                                                    \
}

#define REVERSE_BITS(pointer_to_variable) { \
    if ((pointer_to_variable) != NULL) {\
        size_t number_of_bits = sizeof(*(pointer_to_variable)) * 8; \
        if (sizeof(*(pointer_to_variable)) == sizeof(unsigned char)) { \
            unsigned char reversed = 0;     \
            unsigned char temp = 0;\
            for(size_t i = 0; i < number_of_bits; i++) {          \
                temp = *(pointer_to_variable) & (1u << i);      \
                if(temp) reversed |= (1u << ((number_of_bits - 1u) - i));\
            }                                   \
            *(pointer_to_variable) = reversed;\
        }                                   \
        if (sizeof(*(pointer_to_variable)) == sizeof(unsigned short)) { \
            unsigned short reversed = 0;    \
            unsigned short temp = 0;\
            for(size_t i = 0; i < number_of_bits; i++) {          \
                temp = *(pointer_to_variable) & (1u << i);      \
                if(temp) reversed |= (1u << ((number_of_bits - 1u) - i));\
            }                                   \
            *(pointer_to_variable) = reversed;\
        }                                   \
        if (sizeof(*(pointer_to_variable)) == sizeof(unsigned int)) { \
            unsigned int reversed = 0;      \
            unsigned int temp = 0;                                \
            for(size_t i = 0; i < number_of_bits; i++) {          \
                temp = *(pointer_to_variable) & (1u << i);      \
                if(temp) reversed |= (1u << ((number_of_bits - 1u) - i));\
            }                                   \
            *(pointer_to_variable) = reversed;\
        }                                   \
        if (sizeof(*(pointer_to_variable)) == sizeof(unsigned long)) { \
            unsigned long reversed = 0;     \
            unsigned long temp = 0;\
            for(size_t i = 0; i < number_of_bits; i++) {          \
                temp = *(pointer_to_variable) & (1ul << i);      \
                if(temp) reversed |= (1ul << ((number_of_bits - 1ul) - i));\
            }                                   \
            *(pointer_to_variable) = reversed;\
        }\
    }                                           \
}

#define COUNT_BITS(value, pointer_to_bits_set_counter, pointer_to_bits_cleared_counter) { \
    unsigned int count = 0;                                                               \
    unsigned long long tmp = value;                                                       \
    while(tmp) {                                                                          \
        count += (tmp) & 1;                                                               \
        (tmp) >>= 1;                                                                      \
    }                                                                                     \
    if((pointer_to_bits_set_counter) != NULL) {                                           \
        *(pointer_to_bits_set_counter) = count;                                           \
    }                                                                                     \
    if((pointer_to_bits_cleared_counter) != NULL){                                        \
        *(pointer_to_bits_cleared_counter) = (sizeof(value) * 8) - count;                 \
    }                                                                                     \
}
#endif //DANTE_P2_FUNCTIONS_H
