#pragma once
#include <Lib/Types.h>

typedef struct PICO_RAMFile PICO_RAMFile;
struct attr_pack PICO_RAMFile 
{
    char     name[64];
    bool     hidden : 8;
    uint32_t offset;
    size_t   size;
};

typedef struct
{
    uint32_t table_offset;
    uint32_t table_size;
    uint32_t data_offset;
    uint32_t data_size;
    uint32_t data_pos;
    uint32_t count;
    uint32_t max;
} attr_pack PICO_RAMFSHeader;

typedef struct
{
    PICO_RAMFSHeader* hdr;
    uint8_t*          data;
    size_t            sz;
    PICO_RAMFile*     files;
} attr_pack PICO_RAMFS;

#define RAMFS_ENTSZ (sizeof(PICO_RAMFile))
#define RAMFS_ROOT  0

void PICO_InitRAMFS(PICO_RAMFS* fs, void* data, size_t sz);
PICO_RAMFile* PICO_OpenRAMFile(PICO_RAMFS* fs, const char* name);
void* PICO_ReadRAMFileData(PICO_RAMFS* fs, PICO_RAMFile* file);
bool PICO_RAMFileExists(PICO_RAMFS* fs, const char* name);