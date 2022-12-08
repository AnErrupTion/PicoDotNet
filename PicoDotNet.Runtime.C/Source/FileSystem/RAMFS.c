#include <FileSystem/RAMFS.h>
#include <Core/Common.h>

void PICO_CreateRAMFS(PICO_RAMFS* fs, const char* label, size_t max_ents, size_t sz)
{
    fs->created = true;
    fs->sz      = PICO_MemAlign(sizeof(PICO_RAMFSHeader) + (max_ents * RAMFS_ENTSZ) + sz, 0x1000);
    fs->data    = (uint8_t*)PICO_Alloc(fs->sz);
    fs->hdr     = (PICO_RAMFSHeader*)fs->data;
    fs->hdr->table_offset = sizeof(PICO_RAMFSHeader),
    fs->hdr->table_size   = max_ents * RAMFS_ENTSZ,
    fs->hdr->data_offset  = sizeof(PICO_RAMFSHeader) + (max_ents * RAMFS_ENTSZ),
    fs->hdr->data_size    = sz,
    fs->hdr->count        = 0,
    fs->hdr->max          = max_ents,
    fs->hdr->wrpos        = 0,
    PICO_CreateRAMRootDirectory(fs, label);
    PICO_Log("%s Created RAMFS - Region:%8x-%8x Max:%u Size:%uMB(%u bytes)\n", DEBUG_OK, fs->data, fs->data + fs->sz, max_ents, sz / MEGABYTE, sz);
}

void PICO_InitRAMFS(PICO_RAMFS* fs, void* data, size_t sz)
{
    fs->sz      = sz;
    fs->data    = data;
    fs->hdr     = (PICO_RAMFSHeader*)fs->data;
    fs->created = false;
    PICO_Log("%s Initialized RAMFS - Ptr:%p Size:%a\n", DEBUG_OK, data, sz);
}

void PICO_FreeRAMFS(PICO_RAMFS* fs)
{
    if (fs == NULL) { PICO_Log("PICO_FreeRAMFS(00000000) - Attempt to free null RAMFS"); return; }
    if (fs->data != NULL && fs->created) { PICO_Free(fs->data); }
    fs->data    = NULL;
    fs->sz      = 0;
    fs->hdr     = NULL;
    fs->created = false;
}

PICO_RAMDirectory* PICO_CreateRAMRootDirectory(PICO_RAMFS* fs, const char* label)
{
    PICO_RAMDirectory* dir = PICO_RAMDirectoryAt(fs, 0);
    PICO_StrCopy(dir->name, label);
    dir->parent = -1;
    dir->flags.bits = (PICO_RAMFSFlagBits)
    {
        .present = true,
        .hidden  = true,
        .root    = true,
        .file    = false,
    };
    PICO_Log("%s Created root directory - Label:%s\n", DEBUG_OK, label);
    return dir;
}

PICO_RAMDirectory* PICO_CreateRAMDirectory(PICO_RAMFS* fs, const char* path, bool hidden)
{
    size_t plen = PICO_StrLen(path);
    if (plen == 0) { return NULL; }
    PICO_RAMDirectory* parent = PICO_RAMFSParentFromPath(fs, path);
    if (parent == NULL) { return NULL; }

    const char* p = path;
    for (size_t i = 0; i < plen; i++) { if (path[i] == '/' && i < plen - 1) { p = &path[i + 1]; } }
    PICO_RAMDirectory* dir = PICO_CreateRAMDirectoryEntry(fs, p, (uint32_t)PICO_GetRAMDirectoryIndex(fs, parent), hidden);
    return dir;
}

PICO_RAMFile* PICO_CreateRAMFile(PICO_RAMFS* fs, const char* path, void* contents, size_t sz, bool hidden)
{
    size_t plen = PICO_StrLen(path);
    if (plen == 0) { return NULL; }
    PICO_RAMDirectory* parent = NULL;
    if (PICO_StrRChr(path, '/') == path) { parent = PICO_RAMDirectoryAt(fs, RAMFS_ROOT); } else { parent =  PICO_RAMFSParentFromPath(fs, path); }
    if (parent == NULL) { return NULL; }
    
    const char* fname = path;
    for (size_t i = 0; i < plen; i++) { if (path[i] == '/' && i < plen - 1) { fname = &path[i + 1]; } }
    if (fname[PICO_StrLen(fname) - 1] == '/') { return NULL; }

    sz = PICO_MemAlign(sz, 0x10);
    if (fs->hdr->wrpos + sz > fs->hdr->data_size) { PICO_Error("PICO_CreateRAMFile(%p, %s, %p, %a, %d) - Image out of space", fs, path, contents, sz, hidden); return NULL; }
    uint8_t* offset = (uint8_t*)((uintptr_t)fs->data + fs->hdr->data_offset + fs->hdr->wrpos);
    PICO_MemCopy(offset, contents, sz);
    PICO_RAMFile* file = PICO_CreateRAMFileEntry(fs, fname, PICO_GetRAMDirectoryIndex(fs, parent), fs->hdr->wrpos, sz, hidden);
    fs->hdr->wrpos += sz;
    PICO_Log("%s Created file - Name:'%s' Parent:%d Hidden:%d Offset:%8x Size:%u bytes\n", DEBUG_OK, path, file->parent, file->flags.bits.hidden, file->offset, file->size);
    return file;
}

PICO_RAMDirectory* PICO_OpenRAMDirectory(PICO_RAMFS* fs, const char* path)
{
    size_t plen = PICO_StrLen(path);
    if (plen == 0) { return NULL; }
    PICO_RAMDirectory* parent = NULL;
    if (PICO_StrEquals(path, "/")) { return PICO_RAMDirectoryAt(fs, 0); }
    if (PICO_StrRChr(path, '/') == path) { parent = PICO_RAMDirectoryAt(fs, RAMFS_ROOT); } else { parent =  PICO_RAMFSParentFromPath(fs, path); }
    if (parent == NULL) { return NULL; }

    char* dname = (char*)path;
    for (size_t i = 0; i < plen; i++) { if (path[i] == '/' && i < plen - 1) { dname = (char*)&path[i + 1]; } }
    if (dname[PICO_StrLen(dname) - 1] == '/') { dname[PICO_StrLen(dname) - 1] = 0; }

    PICO_RAMDirectory* ents = (PICO_RAMDirectory*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || ents[i].flags.bits.file) { continue; }
        if (PICO_StrEquals(ents[i].name, dname) && (int)ents[i].parent == PICO_GetRAMDirectoryIndex(fs, parent)) { return &ents[i]; }
    }
    return NULL;
}

PICO_RAMFile* PICO_OpenRAMFile(PICO_RAMFS* fs, const char* path)
{
    size_t plen = PICO_StrLen(path);
    if (plen == 0) { return NULL; }
    PICO_RAMDirectory* parent = PICO_RAMFSParentFromPath(fs, path);
    if (parent == NULL) { return NULL; }

    const char* fname = path;
    for (size_t i = 0; i < plen; i++) { if (path[i] == '/' && i < plen - 1) { fname = &path[i + 1]; } }
    if (fname[PICO_StrLen(fname) - 1] == '/') { return NULL; }

    PICO_RAMFile* ents = (PICO_RAMFile*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || !ents[i].flags.bits.file) { continue; }
        if (PICO_StrEquals(ents[i].name, fname) && (int)ents[i].parent == PICO_GetRAMDirectoryIndex(fs, parent)) { return &ents[i]; }
    }
    return NULL;
}

PICO_RAMDirectory** PICO_GetRAMDirectories(PICO_RAMFS* fs, const char* path, size_t* sz)
{
    uint32_t      count = PICO_CountRAMDirectoriesIn(fs, path);
    PICO_RAMDirectory*  dir   = PICO_OpenRAMDirectory(fs, path);
    PICO_RAMDirectory*  ents  = (PICO_RAMDirectory*)((uintptr_t)fs->data + fs->hdr->table_offset);
    int           index = PICO_GetRAMDirectoryIndex(fs, dir);
    PICO_RAMDirectory** list  = (PICO_RAMDirectory**)PICO_Alloc(sizeof(PICO_RAMDirectory*) * count);

    size_t j = 0;
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || ents[i].flags.bits.file || PICO_StrLen(ents[i].name) == 0) { continue; }
        if ((int)ents[i].parent == index) { list[j++] = &ents[i]; }
    }
    *sz = j;
    return list;
}

PICO_RAMFile** PICO_GetRAMFiles(PICO_RAMFS* fs, const char* path, size_t* sz)
{
    uint32_t       count = PICO_CountRAMFilesIn(fs, path);
    PICO_RAMDirectory*   dir   = PICO_OpenRAMDirectory(fs, path);
    PICO_RAMFile*  ents  = (PICO_RAMFile*)((uintptr_t)fs->data + fs->hdr->table_offset);
    int            index = PICO_GetRAMDirectoryIndex(fs, dir);
    PICO_RAMFile** list  = (PICO_RAMFile**)PICO_Alloc(sizeof(PICO_RAMFile*) * count);

    size_t j = 0;
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || !ents[i].flags.bits.file || PICO_StrLen(ents[i].name) == 0) { continue; }
        if ((int)ents[i].parent == index) { list[j++] = &ents[i]; }
    }
    *sz = j;
    return list;
}

bool PICO_RAMDirectoryExists(PICO_RAMFS* fs, const char* path)
{
    PICO_RAMDirectory* dir = PICO_OpenRAMDirectory(fs, path);
    return (dir != NULL);
}

bool PICO_RAMFileExists(PICO_RAMFS* fs, const char* path)
{
    PICO_RAMFile* file = PICO_OpenRAMFile(fs, path);
    return (file != NULL);
}

PICO_RAMDirectory* PICO_RAMFSParentFromPath(PICO_RAMFS* fs, const char* path)
{
    if (PICO_StrLen(path) == 0) { return NULL; }
    if (PICO_StrEquals(path, "/")) { return PICO_RAMDirectoryAt(fs, RAMFS_ROOT); }

    size_t split_sz = 0;
    char** split    = PICO_StrSplit(path, '/', &split_sz);
    if (split_sz <= 1) { PICO_FreeArray((void**)split, split_sz); return PICO_RAMDirectoryAt(fs, RAMFS_ROOT); }

    PICO_RAMDirectory* parent_dir = NULL;
    for (size_t i = 0; i < split_sz - 1; i++)
    {
        bool found = false;
        for (size_t j = 0; j < fs->hdr->max; j++)
        {
            PICO_RAMDirectory* dir = PICO_RAMDirectoryAt(fs, j);
            if (dir == NULL) { continue; }
            if (!PICO_RAMDirectoryAt(fs, j)->flags.bits.present) { continue; }
            if (PICO_StrEquals(PICO_RAMDirectoryAt(fs, j)->name, split[i])) { parent_dir = PICO_RAMDirectoryAt(fs, j); found = true; break; }
        }
        if (!found) { PICO_FreeArray((void**)split, split_sz); return NULL; }
    }
    PICO_FreeArray((void**)split, split_sz);
    return parent_dir;
}

uint8_t* PICO_ConvertRAMFileOffset(PICO_RAMFS* fs, void* ent)
{
    if (!((PICO_RAMDirectory*)ent)->flags.bits.file) { return NULL; }
    return (uint8_t*)((uintptr_t)fs->data + fs->hdr->data_offset + ((PICO_RAMFile*)ent)->offset);
}

uint32_t PICO_CountRAMDirectories(PICO_RAMFS* fs)
{
    uint32_t c = 0;
    PICO_RAMFile* ents = (PICO_RAMFile*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || ents[i].flags.bits.file || PICO_StrLen(ents[i].name) == 0) { continue; }
        c++;
    }
    return c;
}

uint32_t PICO_CountRAMDirectoriesIn(PICO_RAMFS* fs, const char* path)
{
    PICO_RAMDirectory* dir = PICO_OpenRAMDirectory(fs, path);
    if (dir == NULL) { return 0; }
    int index = PICO_GetRAMDirectoryIndex(fs, dir);

    uint32_t c = 0;
    PICO_RAMDirectory* ents = (PICO_RAMDirectory*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || ents[i].flags.bits.file || PICO_StrLen(ents[i].name) == 0) { continue; }
        if ((int)ents[i].parent == index) { c++; }
    }
    return c;
}

uint32_t PICO_CountRAMFiles(PICO_RAMFS* fs)
{
    uint32_t c = 0;
    PICO_RAMFile* ents = (PICO_RAMFile*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || !ents[i].flags.bits.file) { continue; }
        c++;
    }
    return c;
}

uint32_t PICO_CountRAMFilesIn(PICO_RAMFS* fs, const char* path)
{
    PICO_RAMFile* file = PICO_OpenRAMFile(fs, path);
    if (file == NULL) { return 0; }
    int index = PICO_GetRAMFileIndex(fs, file);

    uint32_t c = 0;
    PICO_RAMFile* ents = (PICO_RAMFile*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present || !ents[i].flags.bits.file) { continue; }
        if ((int)ents[i].parent == index) { c++; }
    }
    return c;
}

PICO_RAMDirectory* PICO_RAMDirectoryAt(PICO_RAMFS* fs, int index)
{
    if (index < 0 || index >= (int)fs->hdr->max) { return NULL; }
    PICO_RAMDirectory* ents = (PICO_RAMDirectory*)((uintptr_t)fs->data + fs->hdr->table_offset);
    if (ents[index].flags.bits.file) { return NULL; }
    return &ents[index];
}

PICO_RAMFile* PICO_RAMFileAt(PICO_RAMFS* fs, int index)
{
    if (index < 0 || index >= (int)fs->hdr->max) { return NULL; }
    PICO_RAMFile* ents = (PICO_RAMFile*)((uintptr_t)fs->data + fs->hdr->table_offset);
    if (!ents[index].flags.bits.file) { return NULL; }
    return &ents[index];
}

int PICO_GetRAMDirectoryIndex(PICO_RAMFS* fs, PICO_RAMDirectory* dir)
{
    if (dir == NULL) { return -1; }
    PICO_RAMDirectory* ents = (PICO_RAMDirectory*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (PICO_StrEquals(ents[i].name, dir->name) && ents[i].flags.value == dir->flags.value && ents[i].parent == dir->parent) { return i; }
    }
    return -1;
}

int PICO_GetRAMFileIndex(PICO_RAMFS* fs, PICO_RAMFile* file) { return PICO_GetRAMDirectoryIndex(fs, (PICO_RAMDirectory*)file); }

PICO_RAMDirectory* PICO_CreateRAMDirectoryEntry(PICO_RAMFS* fs, const char* name, int parent, bool hidden)
{
    PICO_RAMDirectory* dir = (PICO_RAMDirectory*)PICO_NextFreeRAMFSEntry(fs);
    if (dir == NULL) { PICO_Error("RAMFS::create_dir_ent() - No more available entries"); }
    PICO_StrCopy(dir->name, name);
    dir->parent             = parent;
    dir->flags.bits.file    = false;
    dir->flags.bits.present = true;
    dir->flags.bits.root    = false;
    dir->flags.bits.hidden  = hidden;
    return dir;
}

PICO_RAMFile* PICO_CreateRAMFileEntry(PICO_RAMFS* fs, const char* name, int parent, uint32_t offset, size_t sz, bool hidden)
{
    PICO_RAMFile* file = (PICO_RAMFile*)PICO_NextFreeRAMFSEntry(fs);
    if (file == NULL) { PICO_Error("RAMFS::create_file_ent() - No more available entries"); }
    PICO_StrCopy(file->name, name);
    file->parent             = parent;
    file->offset             = offset;
    file->size               = sz;
    file->flags.bits.file    = true;
    file->flags.bits.present = true;
    file->flags.bits.root    = false;
    file->flags.bits.hidden  = hidden;
    return file;
}

void* PICO_NextFreeRAMFSEntry(PICO_RAMFS* fs)
{
    PICO_RAMDirectory* ents = (PICO_RAMDirectory*)((uintptr_t)fs->data + fs->hdr->table_offset);
    for (size_t i = 0; i < fs->hdr->max; i++)
    {
        if (!ents[i].flags.bits.present) { return &ents[i]; }
    }
    return NULL;
}