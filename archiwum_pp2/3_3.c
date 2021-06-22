#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float* create_array(int N) {
    if (N <= 0) {
        return NULL;
    } else {
        float *tab = malloc(sizeof(float ) * N);
        if (tab == NULL) {
            return NULL;
        } else {
            return tab;
        }
    }
}
int main(){
    printf("zapodaj rozmiar tablicy: ");
    int size;
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input");
        return 1;
    } else {
        if (size <= 0) {
            printf("Incorrect input data");
            return 2;
        } else {
            float *tab = create_array(size);
            if (tab == NULL) {
                printf("Failed to allocate memory");
                return 8;
            } else {
                printf("Podaj liczby: ");
                for (int i = 0; i < size; ++i) {
                    if (scanf("%f", (tab + i)) != 1) {
                        printf("Incorrect input");
                        free(tab);
                        return 1;
                    }
                }
                for (int i = size-1; i >= 0; --i) {
                    printf("%f ", *(tab + i));
                }
                free(tab);
            }
        }
    }
    return 0;
}
