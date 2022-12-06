#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;
typedef uint32_t LONG;

typedef struct _IMAGE_DOS_HEADER {
    // Cumulative size:
    WORD e_magic;      // 2
    WORD e_cblp;       // 4
    WORD e_cp;         // 6
    WORD e_crlc;       // 8
    WORD e_cparhdr;    // 10
    WORD e_minalloc;   // 12
    WORD e_maxalloc;   // 14
    WORD e_ss;         // 16
    WORD e_sp;         // 18
    WORD e_csum;       // 20
    WORD e_ip;         // 22
    WORD e_cs;         // 24
    WORD e_lfarlc;     // 26
    WORD e_ovno;       // 28
    WORD e_res[4];     // 36
    WORD e_oemid;      // 38
    WORD e_oeminfo;    // 40
    WORD e_res2[10];   // 60
    LONG e_lfanew;     // 64
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

typedef struct _IMAGE_FILE_HEADER {
    LONG  Signature;
    WORD  Machine;
    WORD  NumberOfSections;
    DWORD TimeDateStamp;
    DWORD PointerToSymbolTable;
    DWORD NumberOfSymbols;
    WORD  SizeOfOptionalHeader;
    WORD  Characteristics;
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
    DWORD VirtualAddress;
    DWORD Size;
} IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_HEADER_SECTION {
    BYTE  Name[8];
    union {
        DWORD PhysicalAddress;
        DWORD VirtualSize;
    } Misc;
    DWORD VirtualAddress;
    DWORD SizeOfRawData;
    DWORD PointerToRawData;
    DWORD PointerToRelocations;
    DWORD PointerToLinenumbers;
    WORD  NumberOfRelocations;
    WORD  NumberOfLinenumbers;
    DWORD Characteristics;
} IMAGE_HEADER_SECTION, *PIMAGE_HEADER_SECTION;

typedef struct _IMAGE_OPTIONAL_HEADER {
    WORD                 Magic;
    BYTE                 MajorLinkerVersion;
    BYTE                 MinorLinkerVersion;
    DWORD                SizeOfCode;
    DWORD                SizeOfInitializedData;
    DWORD                SizeOfUninitializedData;
    DWORD                AddressOfEntryPoint;
    DWORD                BaseOfCode;
    DWORD                BaseOfData;
    DWORD                ImageBase;
    DWORD                SectionAlignment;
    DWORD                FileAlignment;
    WORD                 MajorOperatingSystemVersion;
    WORD                 MinorOperatingSystemVersion;
    WORD                 MajorImageVersion;
    WORD                 MinorImageVersion;
    WORD                 MajorSubsystemVersion;
    WORD                 MinorSubsystemVersion;
    DWORD                Win32VersionValue;
    DWORD                SizeOfImage;
    DWORD                SizeOfHeaders;
    DWORD                CheckSum;
    WORD                 Subsystem;
    WORD                 DllCharacteristics;
    DWORD                SizeOfStackReserve;
    DWORD                SizeOfStackCommit;
    DWORD                SizeOfHeapReserve;
    DWORD                SizeOfHeapCommit;
    DWORD                LoaderFlags;
    DWORD                NumberOfRvaAndSizes;
    IMAGE_DATA_DIRECTORY DataDirectory[16];
    IMAGE_HEADER_SECTION Sections[3];
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_CLR_HEADER {
    DWORD HeaderSize;
    WORD MajorRuntimeVersion;
    WORD MinorRuntimeVersion;
    DWORD MetaDataDirectoryAddress;
    DWORD MetaDataDirectorySize;
    DWORD Flags;
    DWORD EntryPointToken;
    DWORD ResourcesDirectoryAddress;
    DWORD ResourcesDirectorySize;
    DWORD StrongNameSignatureAddress;
    DWORD StrongNameSignatureSize;
    DWORD CodeManagerTableAddress;
    DWORD CodeManagerTableSize;
    DWORD VTableFixupsAddress;
    DWORD VTableFixupsSize;
    DWORD ExportAddressTableJumpsAddress;
    DWORD ExportAddressTableJumpsSize;
    DWORD ManagedNativeHeaderAddress;
    DWORD ManagedNativeHeaderSize;
} IMAGE_CLR_HEADER, *PIMAGE_CLR_HEADER;

byte* ReadBytes(const char* name) {
    FILE* file = fopen(name, "r");
    if (file == NULL)
        printf("YOu fucked up nerd");

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

    for (int i = 0; i < size; i++)
        buf[i] = buffer[offset + i];

    return buf;
}

ushort number_of_sections;
IMAGE_HEADER_SECTION* sections;

ulong RvaToOffset(ulong rva) {
    if (rva == 0) {
        printf("RVA cannot be 0!\n");
        exit(1);
    }

    for (ushort i = 0; i < number_of_sections; i++) {
        IMAGE_HEADER_SECTION section = sections[i];
        if (section.VirtualAddress <= rva && section.VirtualAddress + section.SizeOfRawData >= rva)
            return section.PointerToRawData + (rva - section.VirtualAddress);
    }

    printf("Cannot find the section.\n");
    exit(1);
}

int main() {
    buffer = ReadBytes("TestApp.dll");
    uint offset = 0;

    IMAGE_DOS_HEADER* dos_header = (IMAGE_DOS_HEADER*) GetBuffer(offset, sizeof(IMAGE_DOS_HEADER));
    offset += dos_header->e_lfanew - 1;

    if (dos_header->e_magic != 0x5A4D) {
        printf("Invalid DOS header magic!\n");
        exit(1);
    }

    IMAGE_FILE_HEADER* pe_file_header = (IMAGE_FILE_HEADER*) GetBuffer(offset, sizeof(IMAGE_FILE_HEADER));
    offset += sizeof(IMAGE_FILE_HEADER);

    if (pe_file_header->Signature != 0x4550) {
        printf("Invalid PE file header signature!\n");
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
    return 0;
}