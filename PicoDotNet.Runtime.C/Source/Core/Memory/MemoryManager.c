#include <Core/Memory/MemoryManager.h>
#include <Core/Common.h>

static const char* MEMTYPE_NAMES[] = 
{
    "invalid     ",
    "free        ",
    "reserved    ",
    "acpi_reclaim",
    "nvs         ",
    "bad_ram     ",
    "video_ram   ",
    "kernel      ",
    "module      ",
    "pgfrm_alloc ",
    "heap        ",
    "allocation  ",
    "unused      ",
};

static PICO_MemoryBlock _blocks[MEMBLK_MAX];
static size_t         _count;

void PICO_InitMemMgr(bool zero_free)
{
    PICO_MemSet(_blocks, 0, sizeof(_blocks));
    _count = 0;

    PICO_MemoryMapEntry* mmap   = PICO_GetMultiboot()->mmap;
    size_t             mmapsz = PICO_GetMultiboot()->mmap_len / sizeof(PICO_MemoryMapEntry);
    for (size_t i = 0; i < mmapsz; i++)
    {
        if (mmap[i].address == PICO_GetKernelStart())
        {
            PICO_MapMemBlock((PICO_MemoryBlock){ (uint32_t)mmap[i].address, PICO_GetKernelSize(), MEM_KERNEL });
            PICO_MapMemBlock((PICO_MemoryBlock){ (uint32_t)mmap[i].address + PICO_GetKernelSize(), (uint32_t)mmap[i].size - PICO_GetKernelSize(), MEM_FREE });
        }
        else { PICO_MapMemBlock((PICO_MemoryBlock){ (uint32_t)mmap[i].address, (uint32_t)mmap[i].size, ((mmap[i].address < PICO_GetKernelStart() && mmap[i].type == MEM_FREE) ? MEM_UNUSED : mmap[i].type) }); }
    }

    if (zero_free) { PICO_ClearFreeMemory(); }
    PICO_Log("%s Kernel memory - Region:%p:%p, Size:%uKB\n", DEBUG_INFO, PICO_GetKernelStart(), PICO_GetKernelEnd(), PICO_GetKernelSize() / KILOBYTE);
    PICO_Log("%s Kernel stack  - Region:%p:%p, Size:%uKB\n", DEBUG_INFO, PICO_GetKernelStackBottom(), PICO_GetKernelStackTop(), PICO_GetKernelStackSize() / KILOBYTE);
    PICO_Log("%s Initialized memory manager\n", DEBUG_OK);
}

void PICO_ClearFreeMemory()
{
    PICO_Log("%s Zeroing all available free memory...", DEBUG_INFO);

    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (_blocks[i].type == MEM_FREE) { PICO_MemSet((void*)_blocks[i].addr, 0, _blocks[i].sz); PICO_Log("."); }
    }
    PICO_Log("\n%s Finished zeroing available free memory\n", DEBUG_OK);;
}

PICO_MemoryBlock* PICO_RequestMemBlock(size_t sz)
{
    if (sz == 0) { PICO_Panic("PICO_RequestMemBlock(0) - Invalid size"); return NULL; }
    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (_blocks[i].type == MEM_FREE && _blocks[i].sz >= sz)
        {
            PICO_MemoryBlock* blk = PICO_MapMemBlock((PICO_MemoryBlock){ _blocks[i].addr, sz, MEM_RESERVED });
            _blocks[i].addr += sz;
            _blocks[i].sz   -= sz;
            PICO_Log("%s Granted request for %a memory block\n", DEBUG_OK, sz);
            return blk;
        }
    }
    PICO_Panic("PICO_RequestMemBlock(%u) - Request for memory block failed", sz);
    return NULL;
}

void PICO_ReleaseMemBlock(PICO_MemoryBlock* blk)
{
    if (blk == NULL) { PICO_Panic("PICO_ReleaseMemBlock(00000000) - Attempt to release null memory block"); return; }
    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (_blocks[i].type == MEM_INVALID) { continue; }
        if (&_blocks[i] == blk)
        {
            _blocks[i].type = MEM_FREE;
            PICO_Log("%s Released %a memory block at %p\n", DEBUG_INFO, _blocks[i].sz, _blocks[i].addr);
            return;
        }
    }
    PICO_Panic("PICO_ReleaseMemBlock(%p) - Failed to release memory block", blk);
}

PICO_MemoryBlock* PICO_MapMemBlock(PICO_MemoryBlock blk)
{
    if (blk.sz == 0 || blk.type == MEM_INVALID) { PICO_Panic("PICO_MapMemBlock({ %p, %u, %s }) - Invalid memory block", blk.addr, blk.sz, PICO_GetMemTypeName(blk.type)); return NULL; }
    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (_blocks[i].type == MEM_INVALID)
        {
            _blocks[i] = blk;
            _count++;
            PICO_Log("%s I:%u Region:%p-%p Type:%s Size:%a\n", DEBUG_MMAP, i, blk.addr, blk.addr + blk.sz, PICO_GetMemTypeName(blk.type), blk.sz);
            return &_blocks[i];
        }
    }
    PICO_Panic("PICO_MapMemBlock({ %p, %u, %s }) - Failed to map memory block", blk.addr, blk.sz, PICO_GetMemTypeName(blk.type)); 
    return NULL; 
}

void PICO_UnmapMemBlock(PICO_MemoryBlock* blk)
{
    if (blk == NULL) { PICO_Panic("PICO_UnmapMemBlock(00000000) - Attempt to unmap null memory block"); return; }
    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (&_blocks[i] == blk)
        {
            MEMORY_TYPE type = _blocks[i].type;
            _blocks[i] = (PICO_MemoryBlock){ 0, 0, MEM_INVALID };
            _count--;
            PICO_Log("%s I:%u Region:%p-%p Type:%s Size:%a\n", DEBUG_MUNMAP, i, blk->addr, blk->addr + blk->sz, PICO_GetMemTypeName(type), blk->sz);
            return;
        }
    }
    PICO_Panic("PICO_UnmapMemBlock(%p) - Failed to unmap memory block", blk);
}

PICO_MemoryBlock* PICO_GetMemBlock(uintptr_t addr)
{
    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (_blocks[i].type == MEM_INVALID) { continue; }
        if (_blocks[i].addr == addr) { return &_blocks[i]; }
    }
    return NULL;
}

PICO_MemoryBlock* PICO_GetMemBlockAt(int index)
{
    if (index < 0 || index >= MEMBLK_MAX) { PICO_Panic("PICO_GetMemBlockAt(%d) - Invalid index", index); return NULL; }
    return &_blocks[index];
}

PICO_MemoryBlock* PICO_GetMemBlocks() { return _blocks; }

size_t PICO_GetMemBlockCount()
{
    size_t count = 0;
    for (size_t i = 0; i < MEMBLK_MAX; i++)
    {
        if (_blocks[i].type == MEM_INVALID) { continue; }
        count++;
    }
    return count;
}

const char* PICO_GetMemTypeName(MEMORY_TYPE type)
{
    return MEMTYPE_NAMES[type >= MEM_COUNT ? MEM_INVALID : type]; 
}
