#include <FileSystem/RAMFS.h>
#include <Core/Common.h>

void PICO_InitRAMFS(PICO_RAMFS* fs, void* data, size_t sz)
{
    fs->data  = (uint8_t*)data;
    fs->sz    = sz;
    fs->hdr   = (PICO_RAMFSHeader*)fs->data;
    fs->files = (PICO_RAMFile*)((uintptr_t)fs->data + sizeof(PICO_RAMFSHeader));
    PICO_Log("%s Initialized RAMFS - Ptr:%p Count:%d/%d Size:%a\n", DEBUG_OK, fs->data, fs->hdr->count, fs->hdr->max, fs->hdr->data_size);

    for (int i = 0; i < 1024; i++)
    {
        if (i % 16 == 0) { PICO_Log("\n"); }
        PICO_Log("%2x ", fs->data[i]);
    }

}

PICO_RAMFile* PICO_OpenRAMFile(PICO_RAMFS* fs, const char* name)
{
    if (name == NULL || PICO_StrLen(name) == 0) { return NULL; }
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (fs->files[i].name[0] == 0) { continue; }
        if (PICO_StrEquals(fs->files[i].name, name)) { return &fs->files[i]; }
    }
    return NULL;
}

void* PICO_ReadRAMFileData(PICO_RAMFS* fs, PICO_RAMFile* file)
{
    void* filedata = (void*)((uintptr_t)fs->data + fs->hdr->data_offset + file->offset);
    return filedata;
}

bool PICO_RAMFileExists(PICO_RAMFS* fs, const char* name)
{
    PICO_RAMFile* file = PICO_OpenRAMFile(fs, name);
    return (file != NULL);
}