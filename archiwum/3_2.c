#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){
    float *pi = malloc(sizeof(float));
    if (pi == NULL) {
        printf("Failed to allocate memory");
        return 8;
    } else {
        *pi = 3.141593;
        printf("%f %p", *pi, (void *)pi);
        free(pi);
    }
    return 0;
}
