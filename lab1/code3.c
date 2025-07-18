// Write a C program to extract each byte from a given number and store them in
// separate character variables and print the content of those variables.


#include <stdio.h>

int main() {
    unsigned int num = 0x12345678;

    char byte1 = (num >> 24) & 0xFF;
    char byte2 = (num >> 16) & 0xFF;
    char byte3 = (num >> 8) & 0xFF;
    char byte4 = num & 0xFF;

    printf("Original number: 0x%X (Decimal: %u)\n", num, num);
    printf("\nExtracted Bytes (as characters, showing their integer value):\n");
    printf("Byte 1 (MSB): 0x%02X (Decimal: %d)\n", (unsigned char)byte1, (unsigned char)byte1);
    printf("Byte 2:     0x%02X (Decimal: %d)\n", (unsigned char)byte2, (unsigned char)byte2);
    printf("Byte 3:     0x%02X (Decimal: %d)\n", (unsigned char)byte3, (unsigned char)byte3);
    printf("Byte 4 (LSB): 0x%02X (Decimal: %d)\n", (unsigned char)byte4, (unsigned char)byte4);

    printf("\nExtracted Bytes (as characters, if printable):\n");
    printf("Byte 1: '%c'\n", (char)byte1);
    printf("Byte 2: '%c'\n", (char)byte2);
    printf("Byte 3: '%c'\n", (char)byte3);
    printf("Byte 4: '%c'\n", (char)byte4);

    return 0;
}