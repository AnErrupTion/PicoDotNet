#pragma once
#include <Lib/Types.h>

#define MEMBLK_MAX 1024

typedef enum
{
    MEM_INVALID,
    MEM_FREE,
    MEM_RESERVED,
    MEM_ACPI_RECLAIM,
    MEM_NVS,
    MEM_BADRAM,
    MEM_VRAM,
    MEM_KERNEL,
    MEM_MODULE,
    MEM_PFA,
    MEM_HEAP,
    MEM_ALLOC,
    MEM_UNUSED,
    MEM_COUNT,
} MEMORY_TYPE;

typedef struct
{
    uintptr_t   addr;
    size_t      sz;
    MEMORY_TYPE type;
} PICO_MemoryBlock;

void PICO_InitMemMgr(bool zero_free);
void PICO_ClearFreeMemory();

PICO_MemoryBlock* PICO_RequestMemBlock(size_t sz);
void PICO_ReleaseMemBlock(PICO_MemoryBlock* blk);

PICO_MemoryBlock* PICO_MapMemBlock(PICO_MemoryBlock blk);
void PICO_UnmapMemBlock(PICO_MemoryBlock* blk);

PICO_MemoryBlock* PICO_GetMemBlock(uintptr_t addr);
PICO_MemoryBlock* PICO_GetMemBlockAt(int index);

PICO_MemoryBlock* PICO_GetMemBlocks();

size_t PICO_GetMemBlockCount();
const char* PICO_GetMemTypeName(MEMORY_TYPE type);
