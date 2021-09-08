#include <stdio.h>
#include "big_numbers.h"
#include "tested_declarations.h"
#include "rdebug.h"

int main(){
    char * input = calloc(501, 1);
    char * result;
    if (input == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("zapodaj :");
    scanf("%500s", input);
    int res = validate_expression(input);
    if (res != 0)  {
        free(input);
        printf("Incorrect input");
        return 1;
    }
    res = calculate(input, &result);
    if (res == 3) {
        printf("Failed to allocate memory");
        free(input);
        return 8;
    }
    free(input);
    printf("%s", result);
    free(result);
}
