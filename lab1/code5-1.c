// Write a C program to check whether the Host machine is in Little Endian or
// Big Endian.

#include<stdio.h>

int main() {
    unsigned int i = 1;
    char *c = (char*)&i;

    if (*c) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    return 0;
}