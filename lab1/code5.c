// Write a C program to check whether the Host machine is in Little Endian or
// Big Endian. Enter a number, print the content of each byte location and
// Convert the Endianness of the same i.e. Little to Big Endian and vice-versa.


#include <stdio.h>
#include <stdint.h>

uint32_t swap(uint32_t num) {
    uint32_t num = 0;
    num |= (num & 0x000000FF) << 24;
    num |= (num & 0x0000FF00) << 8;
    num |= (num & 0x00FF0000) >> 8;
    num |= (num & 0xFF000000) >> 24;
    return num;
}

// input - x
// converted num - y
//  (0x%08X) in memory order

int main() {
    unsigned int i = 1;
    char *c = (char*)&i;
    uint32_t x;
    uint32_t y;

    printf("\nEndianness Check\n");
    if (*c) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    printf("\nNumber Byte Analysis and Conversion\n");
    printf("Enter an unsigned 32-bit integer");
    scanf("%u", &x);

    char *num_bytes = (char*)&x;

    printf("\nBytes of the entered number\n", x);
    for (size_t byte_index = 0; byte_index < sizeof(uint32_t); byte_index++) {
        printf("Byte %zu (at address +%zu): 0x%02X (Decimal: %u)\n", byte_index, byte_index, (unsigned char)num_bytes[byte_index], (unsigned char)num_bytes[byte_index]);
    }

    y = swap(x);

    printf("\nOriginal Number:   0x%08X (Decimal: %u)\n", x, x);
    printf("Converted Number:  0x%08X (Decimal: %u)\n", y, y);

    char *y_bytes = (char*)&y;

    printf("\nBytes of the converted number\n", y);
    for (size_t byte_index = 0; byte_index < sizeof(uint32_t); byte_index++) {
        printf("Byte %zu (at address +%zu): 0x%02X (Decimal: %u)\n", byte_index, byte_index, (unsigned char)y_bytes[byte_index], (unsigned char)y_bytes[byte_index]);
    }

    return 0;
}





//uint32_t - It represents an unsigned integer that is guaranteed to be exactly 32 bits in size.

//Unsigned integers are used when we know that the value that we are storing will always be non-negative (zero or positive)

//size_t: This is an unsigned integer type specifically designed to represent the size of objects in memory. It is the type returned by the sizeof operator. The actual size of size_t can vary depending on the system architecture (e.g., 32-bit or 64-bit).

//z: This is a length modifier introduced in the C99 standard. It indicates that the argument being printed is of type size_t.

//u: This indicates that the argument is an unsigned integer.

//Therefore, %zu together ensures that a size_t value is printed correctly as an unsigned integer, regardless of the underlying size of size_t on a particular system. This promotes portability in your C code.


//Here's a breakdown of %02x:

//   %: This indicates that we are using string formatting.

//   0: This is the padding character, which, in this case, is a zero.

//   2: This specifies the minimum width of the formatted string. In this case, it should be at least two characters wide.

//   x: This is the conversion type character, which means the integer will be formatted as a lowercase hexadecimal number.

//  actually it represent an integer as a two-digit hexadecimal (base-16) number

