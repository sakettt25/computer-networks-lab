// Write a C program to check whether the Host machine is in Little Endian or
// Big Endian. Enter a number, print the content of each byte location and
// Convert the Endianness of the same i.e. Little to Big Endian and vice-versa.


#include <stdio.h>
#include <stdint.h>

void check_endianness() {
    unsigned int i = 1;
    char *c = (char*)&i;
    if (*c) {
        printf("\nHost machine is Little Endian.\n");
    } else {
        printf("\nHost machine is Big Endian.\n");
    }
}

void print_bytes(unsigned int num) {
    unsigned char *ptr = (unsigned char *)&num;
    printf("\nContent of each byte location for 0x%X:\n", num);
    for (size_t i = 0; i < sizeof(unsigned int); i++) {
        printf("Byte %zu: 0x%02X\n", i + 1, ptr[i]);
    }
}

unsigned int swap_endianness(unsigned int num) {
    unsigned int swapped_num = 0;
    swapped_num |= ((num >> 24) & 0x000000FF);
    swapped_num |= ((num >> 8) & 0x0000FF00);
    swapped_num |= ((num << 8) & 0x00FF0000);
    swapped_num |= ((num << 24) & 0xFF000000);
    return swapped_num;
}

int main() {
    unsigned int num;

    check_endianness();

    printf("\nEnter an unsigned integer: ");
    scanf("%u", &num);

    print_bytes(num);

    unsigned int converted_num = swap_endianness(num);
    printf("\nOriginal number: 0x%X\n", num);
    printf("Converted Endianness number: 0x%X\n", converted_num);

    print_bytes(converted_num);

    return 0;
}