#pragma once
#include <Lib/Types.h>

typedef struct
{
    bool present : 1;
    bool hidden  : 1;
    bool root    : 1;
    bool file    : 1;
} attr_pack PICO_RAMFSFlagBits;

typedef union
{
    PICO_RAMFSFlagBits bits;
    uint32_t           value;
} PICO_RAMFSFlags;

typedef struct PICO_RAMDirectory PICO_RAMDirectory;
struct attr_pack PICO_RAMDirectory
{
    char            name[80];
    PICO_RAMFSFlags flags;
    int             parent;    
    uint8_t         reserved[8];
};

typedef struct PICO_RAMFile PICO_RAMFile;
struct attr_pack PICO_RAMFile 
{
    char            name[80];
    PICO_RAMFSFlags flags;
    int             parent;   
    uintptr_t       offset;
    size_t          size;
};

typedef struct
{
    uint32_t table_offset;
    uint32_t table_size;
    uint32_t data_offset;
    uint32_t data_size;
    uint32_t count;
    uint32_t max;
    uint32_t wrpos;
} attr_pack PICO_RAMFSHeader;

typedef struct
{
    PICO_RAMFSHeader* hdr;
    uint8_t*          data;
    size_t            sz;
    bool              created;
} attr_pack PICO_RAMFS;

void PICO_CreateRAMFS(PICO_RAMFS* fs, const char* label, size_t max_ents, size_t sz);
void PICO_InitRAMFS(PICO_RAMFS* fs, void* data, size_t sz);
void PICO_FreeRAMFS(PICO_RAMFS* fs);

PICO_RAMDirectory*  PICO_CreateRAMRootDirectory(PICO_RAMFS* fs, const char* label);
PICO_RAMDirectory*  PICO_CreateRAMDirectory(PICO_RAMFS* fs, const char* path, bool hidden);
PICO_RAMFile*       PICO_CreateRAMFile(PICO_RAMFS* fs, const char* path, void* contents, size_t sz, bool hidden);
PICO_RAMDirectory*  PICO_OpenRAMDirectory(PICO_RAMFS* fs, const char* path);
PICO_RAMFile*       PICO_OpenRAMFile(PICO_RAMFS* fs, const char* path);
PICO_RAMDirectory** PICO_GetRAMDirectories(PICO_RAMFS* fs, const char* path, size_t* sz);
PICO_RAMFile**      PICO_GetRAMFiles(PICO_RAMFS* fs, const char* path, size_t* sz);

bool PICO_RAMDirectoryExists(PICO_RAMFS* fs, const char* path);
bool PICO_RAMFileExists(PICO_RAMFS* fs, const char* path);

PICO_RAMDirectory* PICO_RAMFSParentFromPath(PICO_RAMFS* fs, const char* path);
uint8_t*           PICO_ConvertRAMFileOffset(PICO_RAMFS* fs, void* ent);

uint32_t PICO_CountRAMDirectories(PICO_RAMFS* fs);
uint32_t PICO_CountRAMDirectoriesIn(PICO_RAMFS* fs, const char* path);
uint32_t PICO_CountRAMFiles(PICO_RAMFS* fs);
uint32_t PICO_CountRAMFilesIn(PICO_RAMFS* fs, const char* path);

PICO_RAMDirectory* PICO_RAMDirectoryAt(PICO_RAMFS* fs, int index);
PICO_RAMFile*      PICO_RAMFileAt(PICO_RAMFS* fs, int index);

int PICO_GetRAMDirectoryIndex(PICO_RAMFS* fs, PICO_RAMDirectory* dir);
int PICO_GetRAMFileIndex(PICO_RAMFS* fs, PICO_RAMFile* file);

PICO_RAMDirectory* PICO_CreateRAMDirectoryEntry(PICO_RAMFS* fs, const char* name, int parent, bool hidden);
PICO_RAMFile*      PICO_CreateRAMFileEntry(PICO_RAMFS* fs, const char* name, int parent, uint32_t offset, size_t sz, bool hidden);
void*              PICO_NextFreeRAMFSEntry(PICO_RAMFS* fs);

#define RAMFS_ENTSZ (sizeof(PICO_RAMDirectory))
#define RAMFS_ROOT  0