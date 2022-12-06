
typedef uint8_t  byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;

typedef uint8_t  BYTE;
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

#define IMAGE_DOS_HDR_OFFSET  (0)
#define IMAGE_DOS_HDR_SZ      (64)
#define IMAGE_DOS_STUB_OFFSET (IMAGE_DOS_HDR_OFFSET + IMAGE_DOS_HDR_SZ)
#define IMAGE_DOS_STUB_SZ     (64)
#define IMAGE_PE_HDR_OFFSET   (IMAGE_DOS_STUB_OFFSET + IMAGE_DOS_STUB_SZ)
#define IMAGE_PE_HDR_SZ       (sizeof(IMAGE_FILE_HEADER))
#define IMAGE_OPT_HDR_OFFSET  (IMAGE_PE_HDR_OFFSET + IMAGE_PE_HDR_SZ)
#define IMAGE_OPT_HDR_SZ      (sizeof(IMAGE_OPTIONAL_HEADER32));