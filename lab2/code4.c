// Write a C Program to enter a number and store the number across the
// following structure and print the content of each member of the structure.
// Then aggregate each member of the structure to form the original number and
// print the same.
// struct pkt{
// char ch1;
// char ch2[2];
// char ch3;
// };



#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    unsigned int num;
    struct pkt packet;

    printf("Enter an unsigned integer (up to 4 bytes): ");
    scanf("%u", &num);

    packet.ch1 = (num >> 24) & 0xFF;
    packet.ch2[0] = (num >> 16) & 0xFF;
    packet.ch2[1] = (num >> 8) & 0xFF;
    packet.ch3 = num & 0xFF;

    printf("\nContent of structure members:\n");
    printf("ch1: 0x%02X\n", (unsigned char)packet.ch1);
    printf("ch2[0]: 0x%02X\n", (unsigned char)packet.ch2[0]);
    printf("ch2[1]: 0x%02X\n", (unsigned char)packet.ch2[1]);
    printf("ch3: 0x%02X\n", (unsigned char)packet.ch3);

    unsigned int reconstructed_num = 0;
    reconstructed_num |= ((unsigned int)packet.ch1 << 24);
    reconstructed_num |= ((unsigned int)packet.ch2[0] << 16);
    reconstructed_num |= ((unsigned int)packet.ch2[1] << 8);
    reconstructed_num |= (unsigned int)packet.ch3;

    printf("\nReconstructed number: %u (0x%X)\n", reconstructed_num, reconstructed_num);

    return 0;
}