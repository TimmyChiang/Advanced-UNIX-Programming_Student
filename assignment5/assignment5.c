#include <stdio.h>

int* f1(int *ptr) {
    return ptr;
}

int main() {
    int val = 5;
    int* where = f1(&val);
    printf("Value %d is at %p\n", val, where);
    return 0;
}
