#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    const char* filename = "test.h5";
    if (argc > 1) {
        filename = argv[1];
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    printf("Hex dump of %s:\n", filename);
    printf("Offset   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F  ASCII\n");
    printf("------   ------------------------------------------------  ----------------\n");

    unsigned char buffer[16];
    size_t bytes_read;
    size_t offset = 0;

    while ((bytes_read = fread(buffer, 1, 16, file)) > 0) {
        printf("%06X   ", (unsigned int)offset);

        // Print hex values
        for (size_t i = 0; i < 16; i++) {
            if (i < bytes_read) {
                printf("%02X ", buffer[i]);
            } else {
                printf("   ");
            }
        }

        printf(" ");

        // Print ASCII representation
        for (size_t i = 0; i < bytes_read; i++) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }

        printf("\n");
        offset += bytes_read;
    }

    fclose(file);
    return 0;
}