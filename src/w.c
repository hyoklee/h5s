#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#pragma pack(push, 1)

// HDF5 Superblock Version 0
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

// Object Header Version 1
typedef struct {
    uint8_t version;                // Version number
    uint8_t reserved;               // Reserved byte
    uint16_t total_header_messages; // Total number of header messages
    uint32_t reference_count;       // Object reference count
    uint32_t header_size;           // Object header size
    uint32_t reserved2;             // Reserved bytes
} ObjectHeaderV1;

// Header Message
typedef struct {
    uint16_t message_type;          // Message type
    uint16_t message_size;          // Message data size
    uint8_t message_flags;          // Message flags
    uint8_t reserved[3];            // Reserved bytes
} HeaderMessage;

// Group Info Message (Type 0x000A)
typedef struct {
    uint8_t version;                // Version
    uint8_t flags;                  // Flags
    uint16_t max_compact;           // Maximum compact value
    uint16_t min_dense;             // Minimum dense value
    uint16_t estimated_entries;     // Estimated number of entries
    uint16_t estimated_length;      // Estimated name length
} GroupInfoMessage;

// Link Info Message (Type 0x0002)
typedef struct {
    uint8_t version;                // Version
    uint8_t flags;                  // Flags
    uint64_t max_creation_index;    // Maximum creation order value
    uint64_t fractal_heap_address;  // Fractal heap address
    uint64_t name_index_address;    // Name index B-tree address
    uint64_t creation_order_address; // Creation order index address (optional)
} LinkInfoMessage;

#pragma pack(pop)

int main() {
    const char *filename = "test.h5";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating file");
        return 1;
    }

    // Calculate addresses
    size_t superblock_size = sizeof(SuperblockV0);
    size_t object_header_size = sizeof(ObjectHeaderV1) + sizeof(HeaderMessage) + sizeof(GroupInfoMessage);
    size_t end_of_file = superblock_size + object_header_size;

    // Write superblock
    SuperblockV0 sb = {0};
    const uint8_t signature[8] = {0x89, 'H', 'D', 'F', '\r', '\n', 0x1a, '\n'};
    memcpy(sb.signature, signature, 8);
    sb.version_superblock = 0;
    sb.version_freespace = 0;
    sb.version_root_group = 0;
    sb.reserved = 0;
    sb.version_shared_header = 0;
    sb.sizeof_address = 8;
    sb.sizeof_lengths = 8;
    sb.reserved2 = 0;
    sb.group_leaf_k = 4;
    sb.group_internal_k = 16;
    sb.file_consistency_flags = 0;
    sb.base_address = 0;
    sb.freespace_address = 0xFFFFFFFFFFFFFFFFULL; // Undefined
    sb.end_of_file_address = end_of_file;
    sb.driver_info_address = 0xFFFFFFFFFFFFFFFFULL; // Undefined
    sb.root_group_address = superblock_size;

    if (fwrite(&sb, sizeof(sb), 1, file) != 1) {
        perror("Error writing superblock");
        fclose(file);
        return 1;
    }

    // Write root group object header
    ObjectHeaderV1 obj_header = {0};
    obj_header.version = 1;
    obj_header.reserved = 0;
    obj_header.total_header_messages = 1;
    obj_header.reference_count = 1;
    obj_header.header_size = sizeof(HeaderMessage) + sizeof(GroupInfoMessage);
    obj_header.reserved2 = 0;

    if (fwrite(&obj_header, sizeof(obj_header), 1, file) != 1) {
        perror("Error writing object header");
        fclose(file);
        return 1;
    }

    // Write header message for group info
    HeaderMessage msg = {0};
    msg.message_type = 0x000A; // Group Info Message
    msg.message_size = sizeof(GroupInfoMessage);
    msg.message_flags = 0;

    if (fwrite(&msg, sizeof(msg), 1, file) != 1) {
        perror("Error writing header message");
        fclose(file);
        return 1;
    }

    // Write group info message
    GroupInfoMessage group_info = {0};
    group_info.version = 0;
    group_info.flags = 0;
    group_info.max_compact = 8;
    group_info.min_dense = 6;
    group_info.estimated_entries = 0;
    group_info.estimated_length = 0;

    if (fwrite(&group_info, sizeof(group_info), 1, file) != 1) {
        perror("Error writing group info");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("File %s created successfully\n", filename);
    return 0;
}
