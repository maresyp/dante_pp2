#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* create_array_int(int N) {
    if (N <= 0) return NULL;
    return (int *) malloc(sizeof(int) * N);

}
int* copy_array_int(const int* ptr, int N) {
    if (ptr == NULL || N <= 0) return NULL;
    int *copy = malloc(sizeof(int) * N);
    if (copy == NULL) return NULL;
    memcpy(copy, ptr, sizeof(int) * N);
    return copy;
}
void display_array_int(const int* ptr, int N) {
    if (ptr == NULL || N <= 0) return;
    for (int i = 0; i < N; ++i) {
        printf("%d ", *(ptr + i));
    }
}

int main(){
    printf("Zapodaj rozmiar tablicy: ");
    int tab_size;
    if (scanf("%d", &tab_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (tab_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    int *res = create_array_int(tab_size);
    if (res == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    printf("Podaj liczby: ");
    int val, i = 0;
    do {
        if (scanf("%d", &val) != 1) {
            printf("Incorrect input");
            free(res);
            return 1;
        }
        *(res + i) = val; i++;
    } while (i != tab_size);
    int *res2 = copy_array_int(res, tab_size);

    if (res2 == NULL) {
        printf("Failed to allocate memory");
        free(res);
        return 8;
    }
    display_array_int(res, tab_size);
    printf("\n");
    display_array_int(res2, tab_size);
    free(res);
    free(res2);
    return 0;
}