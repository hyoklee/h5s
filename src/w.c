#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Simplified structures
typedef struct {
    char signature[8];
    uint8_t version;
    uint64_t root_group_addr;
} Superblock;

typedef struct {
    uint64_t object_header_addr;
} SymbolTableEntry;

int main() {
    const char *filename = "test.h5";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating file");
        return 1;
    }

    // Write superblock
    Superblock sb;
    const char *signature = "HDF\r\n\032\n";
    memcpy(sb.signature, signature, 8);
    sb.version = 0;
    sb.root_group_addr = sizeof(Superblock); // Point to root group

    if (fwrite(&sb, sizeof(sb), 1, file) != 1) {
        perror("Error writing superblock");
        fclose(file);
        return 1;
    }

    // Write root group symbol table entry
    SymbolTableEntry ste;
    ste.object_header_addr = sb.root_group_addr + sizeof(SymbolTableEntry);

    if (fwrite(&ste, sizeof(ste), 1, file) != 1) {
        perror("Error writing symbol table");
        fclose(file);
        return 1;
    }

    // Write data (example: single integer)
    int32_t data = 42;
    if (fwrite(&data, sizeof(data), 1, file) != 1) {
        perror("Error writing data");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("File %s created successfully\n", filename);
    return 0;
}
