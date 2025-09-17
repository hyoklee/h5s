#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)

// HDF5 Superblock Version 0 (matching w.c)
typedef struct {
    uint8_t signature[8];           // HDF5 signature
    uint8_t version_superblock;     // Version of superblock
    uint8_t version_freespace;      // Version of freespace storage
    uint8_t version_root_group;     // Version of root group symbol table entry
    uint8_t reserved;               // Reserved byte
    uint8_t version_shared_header;  // Version of shared header message format
    uint8_t sizeof_address;         // Size of addresses
    uint8_t sizeof_lengths;         // Size of lengths
    uint8_t reserved2;              // Reserved byte
    uint16_t group_leaf_k;          // Group leaf node K
    uint16_t group_internal_k;      // Group internal node K
    uint32_t file_consistency_flags; // File consistency flags
    uint64_t base_address;          // Base address
    uint64_t freespace_address;     // Address of global free-space index
    uint64_t end_of_file_address;   // End of file address
    uint64_t driver_info_address;   // Driver information address
    uint64_t root_group_address;    // Root group symbol table entry
} SuperblockV0;

// Object Header Version 1 (matching w.c)
typedef struct {
    uint8_t version;                // Version number
    uint8_t reserved;               // Reserved byte
    uint16_t total_header_messages; // Total number of header messages
    uint32_t reference_count;       // Object reference count
    uint32_t header_size;           // Object header size
    uint32_t reserved2;             // Reserved bytes
} ObjectHeaderV1;

// Header Message (matching w.c)
typedef struct {
    uint16_t message_type;          // Message type
    uint16_t message_size;          // Message data size
    uint8_t message_flags;          // Message flags
    uint8_t reserved[3];            // Reserved bytes
} HeaderMessage;

// Group Info Message (Type 0x000A) (matching w.c)
typedef struct {
    uint8_t version;                // Version
    uint8_t flags;                  // Flags
    uint16_t max_compact;           // Maximum compact value
    uint16_t min_dense;             // Minimum dense value
    uint16_t estimated_entries;     // Estimated number of entries
    uint16_t estimated_length;      // Estimated name length
} GroupInfoMessage;

#pragma pack(pop)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.h5>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Read superblock
    SuperblockV0 sb;
    if (fread(&sb, sizeof(sb), 1, file) != 1) {
        perror("Error reading superblock");
        fclose(file);
        return 1;
    }

    // Verify signature
    const uint8_t valid_sig[8] = {0x89, 'H', 'D', 'F', '\r', '\n', 0x1a, '\n'};
    if (memcmp(sb.signature, valid_sig, 8) != 0) {
        fprintf(stderr, "Invalid HDF5 file signature\n");
        fclose(file);
        return 1;
    }

    printf("HDF5 file validation successful!\n");
    printf("Superblock version: %d\n", sb.version_superblock);
    printf("Address size: %d bytes\n", sb.sizeof_address);
    printf("Length size: %d bytes\n", sb.sizeof_lengths);
    printf("End of file address: 0x%016llX\n", (unsigned long long)sb.end_of_file_address);
    printf("Root group address: 0x%016llX\n", (unsigned long long)sb.root_group_address);

    // Navigate to root group object header
    if (fseek(file, sb.root_group_address, SEEK_SET) != 0) {
        perror("Error seeking to root group");
        fclose(file);
        return 1;
    }

    // Read object header
    ObjectHeaderV1 obj_header;
    if (fread(&obj_header, sizeof(obj_header), 1, file) != 1) {
        perror("Error reading object header");
        fclose(file);
        return 1;
    }

    printf("\nRoot Group Object Header:\n");
    printf("Version: %d\n", obj_header.version);
    printf("Total header messages: %d\n", obj_header.total_header_messages);
    printf("Reference count: %d\n", obj_header.reference_count);
    printf("Header size: %d bytes\n", obj_header.header_size);

    // Read each header message
    for (int i = 0; i < obj_header.total_header_messages; i++) {
        HeaderMessage msg;
        if (fread(&msg, sizeof(msg), 1, file) != 1) {
            perror("Error reading header message");
            fclose(file);
            return 1;
        }

        printf("\nHeader Message %d:\n", i + 1);
        printf("Message type: 0x%04X", msg.message_type);

        switch (msg.message_type) {
            case 0x000A:
                printf(" (Group Info Message)\n");
                break;
            case 0x0002:
                printf(" (Link Info Message)\n");
                break;
            default:
                printf(" (Unknown Message Type)\n");
                break;
        }

        printf("Message size: %d bytes\n", msg.message_size);
        printf("Message flags: 0x%02X\n", msg.message_flags);

        // Read message data based on type
        if (msg.message_type == 0x000A) { // Group Info Message
            GroupInfoMessage group_info;
            if (fread(&group_info, sizeof(group_info), 1, file) != 1) {
                perror("Error reading group info message");
                fclose(file);
                return 1;
            }

            printf("Group Info Details:\n");
            printf("  Version: %d\n", group_info.version);
            printf("  Flags: 0x%02X\n", group_info.flags);
            printf("  Max compact: %d\n", group_info.max_compact);
            printf("  Min dense: %d\n", group_info.min_dense);
            printf("  Estimated entries: %d\n", group_info.estimated_entries);
            printf("  Estimated length: %d\n", group_info.estimated_length);
        } else {
            // Skip unknown message data
            if (fseek(file, msg.message_size, SEEK_CUR) != 0) {
                perror("Error skipping message data");
                fclose(file);
                return 1;
            }
        }
    }

    printf("\nHDF5 file read successfully!\n");
    fclose(file);
    return 0;
}
