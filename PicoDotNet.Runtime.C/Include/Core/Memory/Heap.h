#pragma once
#include <Lib/Types.h>
#include <Core/Memory/MemoryManager.h>

typedef struct
{
    uintptr_t   addr;
    size_t      sz;
    MEMORY_TYPE type;
    void*       thread;
} PICO_HeapBlock;

typedef struct
{
    PICO_MemoryBlock* memblk_table;
    PICO_MemoryBlock* memblk_data;
    PICO_HeapBlock*   blocks;
    size_t          alignment;
    size_t          sz, count, max;
    bool            auto_collect;
} PICO_Heap;

void   PICO_InitHeap(PICO_Heap* heap, size_t sz, size_t max_ents, size_t align, bool auto_collect);
void*  PICO_HeapAllocate(PICO_Heap* heap, size_t sz, bool zero_fill);
bool   PICO_HeapFree(PICO_Heap* heap, void* ptr);
size_t PICO_HeapCollect(PICO_Heap* heap);
bool   PICO_HeapMerge(PICO_Heap* heap, PICO_HeapBlock* blk1, PICO_HeapBlock* blk2);

PICO_HeapBlock* PICO_HeapRequestBlock(PICO_Heap* heap, size_t sz);
PICO_HeapBlock* PICO_HeapNextBlock(PICO_Heap* heap);
PICO_HeapBlock* PICO_HeapNearestBlock(PICO_Heap* heap, PICO_HeapBlock* blk);
PICO_HeapBlock* PICO_HeapCreateBlock(PICO_Heap* heap, PICO_HeapBlock blk);
void          PICO_HeapRemoveBlock(PICO_Heap* heap, PICO_HeapBlock* blk);

PICO_HeapBlock* PICO_HeapFetch(PICO_Heap* heap, void* ptr);

size_t PICO_HeapCountType(PICO_Heap* heap, MEMORY_TYPE type);
size_t PICO_HeapAmountFree(PICO_Heap* heap);
size_t PICO_HeapAmountUsed(PICO_Heap* heap);
size_t PICO_HeapSize(PICO_Heap* heap);
