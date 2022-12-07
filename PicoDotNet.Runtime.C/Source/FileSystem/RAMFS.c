#include <FileSystem/RAMFS.h>
#include <Core/Common.h>

void PICO_InitRAMFS(PICO_RAMFS* ramfs, void* data, size_t sz)
{

}

void PICO_FreeRAMFS(PICO_RAMFS* ramfs)
{

}

PICO_RAMDirectory* PICO_CreateRAMRootDirectory(PICO_RAMFS* fs, const char* label)
{
    return NULL;
}

PICO_RAMDirectory* PICO_CreateRAMDirectory(PICO_RAMFS* fs, const char* path, bool hidden)
{
    return NULL;
}

PICO_RAMFile* PICO_CreateRAMFile(PICO_RAMFS* fs, const char* path, void* contents, size_t sz, bool hidden)
{
    return NULL;
}

PICO_RAMDirectory*  ICO_OpenRAMDirectory(PICO_RAMFS* fs, const char* path)
{
    return NULL;
}

PICO_RAMFile* PICO_OpenRAMFile(PICO_RAMFS* fs, const char* path)
{
    return NULL;
}

PICO_RAMDirectory** PICO_GetRAMDirectories(PICO_RAMFS* fs, const char* path, size_t* sz)
{
    return NULL;
}

PICO_RAMFile** PICO_GetRAMFiles(PICO_RAMFS* fs, const char path, size_t* sz)
{
    return NULL;
}

bool PICO_RAMDirectoryExists(PICO_RAMFS* fs, const char* path)
{
    return false;
}

bool PICO_RAMFileExists(PICO_RAMFS* fs, const char* path)
{
    return false;
}

PICO_RAMDirectory* PICO_RAMFSParentFromPath(PICO_RAMFS* fs, const char* path)
{
    return NULL;
}

uint8_t* PICO_ConvertRAMFileOffset(PICO_RAMFS* fs, void* ent)
{
    return NULL;
}

uint32_t PICO_CountRAMDirectories(PICO_RAMFS* fs) { return 0; }

uint32_t PICO_CountRAMDirectoriesIn(PICO_RAMFS* fs, const char* path) { return 0; }

uint32_t PICO_CountRAMFiles(PICO_RAMFS* fs) { return 0; }

uint32_t PICO_CountRAMFilesIn(PICO_RAMFS* fs, const char* path) { return 0; }

PICO_RAMDirectory* PICO_RAMDirectoryAt(PICO_RAMFS* fs, int index)
{
    return NULL;
}

PICO_RAMFile* PICO_RAMFileAt(PICO_RAMFS* fs, int index)
{
    return NULL;
}

int PICO_GetRAMDirectoryIndex(PICO_RAMFS* fs, PICO_RAMDirectory* dir) { return 0; }

int PICO_GetRAMFileIndex(PICO_RAMFS* fs, PICO_RAMFile* file) { return 0; }

PICO_RAMDirectory* PICO_CreateRAMDirectoryEntry(PICO_RAMFS* fs, const char* name, int parent, bool hidden)
{
    return NULL;
}

PICO_RAMFile* PICO_CreateRAMFileEntry(PICO_RAMFS* fs, const char* name, int parent, uint32_t offset, size_t sz, bool hidden)
{
    return NULL;
}

void* PICO_NextFreeRAMFSEntry(PICO_RAMFS* fs)
{
    return NULL;
}