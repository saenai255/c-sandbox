#include <stdio.h>


int main(void) {
    int *ptr;
    ptr = 0xb612244c;

    *ptr = 15;

    return 0;
}