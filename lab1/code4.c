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

// Define the structure as specified
struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    unsigned int original_num; // Use unsigned int to handle bitwise operations cleanly
    struct pkt packet;

    printf("Enter an unsigned integer (up to 4 bytes, e.g., 0x12345678): ");
    scanf("%u", &original_num);

    // --- Store the number across the structure members ---
    // Assuming a 4-byte integer and extracting bytes from most significant to least significant
    // The order of assignment here determines how bytes are conceptually mapped to structure members.
    // This mapping is arbitrary and depends on how you want to interpret the 'pkt' structure.
    // For example, ch1 = MSB, ch2[0] = next, ch2[1] = next, ch3 = LSB.

    packet.ch1 = (original_num >> 24) & 0xFF; // Most significant byte
    packet.ch2[0] = (original_num >> 16) & 0xFF; // Second byte
    packet.ch2[1] = (original_num >> 8) & 0xFF;  // Third byte
    packet.ch3 = original_num & 0xFF;         // Least significant byte

    // --- Print the content of each member of the structure ---
    printf("\nContent of structure members:\n");
    printf("packet.ch1:   0x%02X (Decimal: %d)\n", (unsigned char)packet.ch1, (unsigned char)packet.ch1);
    printf("packet.ch2[0]: 0x%02X (Decimal: %d)\n", (unsigned char)packet.ch2[0], (unsigned char)packet.ch2[0]);
    printf("packet.ch2[1]: 0x%02X (Decimal: %d)\n", (unsigned char)packet.ch2[1], (unsigned char)packet.ch2[1]);
    printf("packet.ch3:   0x%02X (Decimal: %d)\n", (unsigned char)packet.ch3, (unsigned char)packet.ch3);

    // --- Aggregate each member of the structure to form the original number ---
    unsigned int reconstructed_num = 0;

    // Reconstruct the number using bitwise OR and left shifts
    reconstructed_num |= ((unsigned int)packet.ch1 << 24);
    reconstructed_num |= ((unsigned int)packet.ch2[0] << 16);
    reconstructed_num |= ((unsigned int)packet.ch2[1] << 8);
    reconstructed_num |= (unsigned int)packet.ch3;

    // --- Print the aggregated number ---
    printf("\nOriginal number entered: 0x%X (Decimal: %u)\n", original_num, original_num);
    printf("Reconstructed number:    0x%X (Decimal: %u)\n", reconstructed_num, reconstructed_num);

    // Verify if the reconstructed number matches the original
    if (original_num == reconstructed_num) {
        printf("Reconstruction successful!\n");
    } else {
        printf("Reconstruction failed!\n");
    }

    return 0;
}