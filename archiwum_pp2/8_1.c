#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_equal(int a, int b) {
    return !(a ^ b);
}
int is_negative(int value) {
    if (is_equal(0, value)) return 0;
    int tmp = (value & 0x80000000);
    if (is_equal(tmp, 0)) return 0;
    return 1;
}
int main(){
    printf("zapodaj:\n");
    int a,b;
    if (!(is_equal(scanf("%d %d", &a, &b), 2))) {
        printf("Incorrect input");
        return 1;
    } else {
        int res = is_equal(a, b);
        if (is_equal(res, 0)) {
            printf("nierowne\n");
        } else {
            printf("rowne\n");
        }
        if (!is_negative(a)) {
            printf("nieujemna ");
        } else {
            printf("ujemna ");
        }
        if (!is_negative(b)) {
            printf("nieujemna");
        } else {
            printf("ujemna");
        }
    }
    return 0;
}
