#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t uint;

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
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct _IMAGE_HEADER_SECTION {
    BYTE  Name[8];
    DWORD VirtualSize;
    DWORD VirtualAddress;
    DWORD SizeOfRawData;
    DWORD PointerToRawData;
    DWORD PointerToRelocations;
    DWORD PointerToLinenumbers;
    WORD  NumberOfRelocations;
    WORD  NumberOfLinenumbers;
    DWORD Characteristics;
} IMAGE_HEADER_SECTION, *PIMAGE_HEADER_SECTION;

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

byte* GetBuffer(byte* buffer, uint offset, uint size) {
    byte* buf = malloc(size);

    for (int i = 0; i < size; i++)
        buf[i] = buffer[offset + i];

    return buf;
}

int main() {
    byte* buffer = ReadBytes("TestApp.dll");
    uint offset = 0;

    IMAGE_DOS_HEADER* dos_header = (IMAGE_DOS_HEADER*) GetBuffer(buffer, offset, sizeof(IMAGE_DOS_HEADER));
    offset += dos_header->e_lfanew - 1;

    IMAGE_FILE_HEADER* pe_file_header = (IMAGE_FILE_HEADER*) GetBuffer(buffer, offset, sizeof(IMAGE_FILE_HEADER));
    offset += sizeof(IMAGE_FILE_HEADER);

    IMAGE_OPTIONAL_HEADER32* pe_optional_header = (IMAGE_OPTIONAL_HEADER32*) GetBuffer(buffer, offset, sizeof(IMAGE_OPTIONAL_HEADER32));
    offset += sizeof(IMAGE_OPTIONAL_HEADER32);

    IMAGE_HEADER_SECTION* sections = (IMAGE_HEADER_SECTION*) GetBuffer(buffer, offset, pe_file_header->NumberOfSections);
    IMAGE_HEADER_SECTION section = sections[0];

    IMAGE_DATA_DIRECTORY clr_directory_header = pe_optional_header->DataDirectory[15];

    offset = section.PointerToRawData + (clr_directory_header.VirtualAddress - section.VirtualAddress);
    byte* clr_directory_data = GetBuffer(buffer, offset, clr_directory_header.Size);

    IMAGE_CLR_HEADER* clr_header = (IMAGE_CLR_HEADER*) GetBuffer(clr_directory_data, 0, sizeof(IMAGE_CLR_HEADER));

    // TODO: Read strong name hash, parse metadata

    free(clr_header);
    free(clr_directory_data);
    free(sections);
    free(pe_optional_header);
    free(pe_file_header);
    free(dos_header);
    free(buffer);
    return 0;
}