#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include "types.h"

byte* ReadBytes(const char* name) {
    FILE* file = fopen(name, "r");
    if (file == NULL) { printf("Failed to located file at '%s'\n", name); exit(1); return NULL; }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    byte* dstBuf = malloc(size);
    fread(dstBuf, size, 1, file);
    fclose(file);

    return dstBuf;
}

byte* buffer;

byte* GetBuffer(uint offset, uint size) {
    byte* buf = malloc(size);

    for (uint i = 0; i < size; i++)
        buf[i] = buffer[offset + i];

    return buf;
}

ushort number_of_sections;
IMAGE_HEADER_SECTION* sections;

ulong RvaToOffset(ulong rva) {
    if (rva == 0) {
        printf("RVA cannot be 0!\n");
        exit(1);
        return 0;
    }

    for (ushort i = 0; i < number_of_sections; i++) {
        IMAGE_HEADER_SECTION section = sections[i];
        if (section.VirtualAddress <= rva && section.VirtualAddress + section.SizeOfRawData >= rva)
            return section.PointerToRawData + (rva - section.VirtualAddress);
    }

    printf("Cannot find the section.\n");
    exit(1);
    return 0;
}

int main() {
    buffer = ReadBytes("../TestApp/net7.0/TestApp.dll");
    uint offset = 0;

    IMAGE_DOS_HEADER* dos_header = (IMAGE_DOS_HEADER*) GetBuffer(offset, sizeof(IMAGE_DOS_HEADER));
    offset += dos_header->e_lfanew - 1;

    if (dos_header->e_magic != 0x5A4D) {
        printf("Invalid DOS header magic!\n");
        exit(1);
    }

    IMAGE_FILE_HEADER* pe_file_header = (IMAGE_FILE_HEADER*)((uintptr_t)buffer + 0x80); // GetBuffer(offset, sizeof(IMAGE_FILE_HEADER));
    offset += sizeof(IMAGE_FILE_HEADER);

    if (pe_file_header->Signature != 0x4550) {
        printf("Invalid PE file header signature! - %08X\n", pe_file_header->Signature);
        exit(1);
    }

    IMAGE_OPTIONAL_HEADER32* pe_optional_header = (IMAGE_OPTIONAL_HEADER32*) GetBuffer(offset, sizeof(IMAGE_OPTIONAL_HEADER32));
    offset += sizeof(IMAGE_OPTIONAL_HEADER32);

    if (pe_optional_header->Magic != 0x10B) { // 0x10B is 32-bit, 0x20B is 64-bit
        printf("Invalid PE optional header magic!\n");
        exit(1);
    }

    for (int i = 0; i < 16; i++) {
        IMAGE_DATA_DIRECTORY directory = pe_optional_header->DataDirectory[i];
        printf("%d: virt %d sz %d\n", i, directory.VirtualAddress, directory.Size);
    }

    number_of_sections = pe_file_header->NumberOfSections;
    // TODO: This reads incorrectly, why??
    //sections = (IMAGE_HEADER_SECTION*) GetBuffer(offset, number_of_sections);
    sections = pe_optional_header->Sections;

    for (ushort i = 0; i < number_of_sections; i++) {
        IMAGE_HEADER_SECTION section = sections[i];
        for (int j = 0; j < 8; j++)
            printf("%c", section.Name[j]);
        printf("\n");
    }

    IMAGE_DATA_DIRECTORY clr_directory_header = pe_optional_header->DataDirectory[14];

    // TODO: Why is the size so huge and addr 0???
    offset = RvaToOffset(clr_directory_header.VirtualAddress);
    IMAGE_CLR_HEADER* clr_header = (IMAGE_CLR_HEADER*) GetBuffer(offset, clr_directory_header.Size);

    printf("sz %d addr %d maj %d min %d\n", clr_header->HeaderSize, clr_header->StrongNameSignatureAddress, clr_header->MajorRuntimeVersion, clr_header->MinorRuntimeVersion);

    offset = RvaToOffset(clr_header->StrongNameSignatureAddress);
    printf("%d\n", offset);
    //byte* strong_name_hash = GetBuffer(offset, clr_header->StrongNameSignatureSize);

    // TODO: Parse metadata

    //free(strong_name_hash);
    free(clr_header);
    //free(sections);
    free(pe_optional_header);
    free(pe_file_header);
    free(dos_header);
    free(buffer);
    printf("Interpreted finished\n");
    return 0;
}