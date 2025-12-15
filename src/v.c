#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int validate_hdf5_signature(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    uint8_t signature[8];
    if (fread(signature, 1, 8, file) != 8) {
        printf("Error: Cannot read HDF5 signature\n");
        fclose(file);
        return 0;
    }

    // Expected HDF5 signature: 0x89, 'H', 'D', 'F', '\r', '\n', 0x1a, '\n'
    uint8_t expected[8] = {0x89, 'H', 'D', 'F', '\r', '\n', 0x1a, '\n'};

    int valid = 1;
    for (int i = 0; i < 8; i++) {
        if (signature[i] != expected[i]) {
            valid = 0;
            break;
        }
    }

    printf("HDF5 signature validation: %s\n", valid ? "PASSED" : "FAILED");

    if (!valid) {
        printf("Expected: ");
        for (int i = 0; i < 8; i++) {
            printf("0x%02X ", expected[i]);
        }
        printf("\nActual:   ");
        for (int i = 0; i < 8; i++) {
            printf("0x%02X ", signature[i]);
        }
        printf("\n");
    }

    // Check superblock version
    uint8_t version;
    if (fread(&version, 1, 1, file) == 1) {
        printf("Superblock version: %d\n", version);
    }

    fclose(file);
    return valid;
}

int main(int argc, char* argv[]) {
    const char* filename = "test.h5";
    if (argc > 1) {
        filename = argv[1];
    }

    printf("Validating HDF5 file: %s\n", filename);

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    printf("File size: %ld bytes\n", file_size);

    if (validate_hdf5_signature(filename)) {
        printf("Basic HDF5 validation: PASSED\n");
        return 0;
    } else {
        printf("Basic HDF5 validation: FAILED\n");
        return 1;
    }
}