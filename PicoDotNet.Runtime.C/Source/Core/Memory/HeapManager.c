#include <Core/Memory/HeapManager.h>
#include <Core/Common.h>

#define HEAPS_MAX    32
#define HEAP_MAXENTS 24576

static PICO_Heap _heaps[HEAPS_MAX];
static size_t  _count;

void PICO_InitHeapManager()
{
    PICO_MemSet(_heaps, 0, sizeof(_heaps));
    _count = 0;

    PICO_MemoryBlock* blks = PICO_GetMemBlocks();
    for (size_t i = 0; i < PICO_GetMemBlockCount(); i++)
    {
        size_t table_sz = sizeof(PICO_HeapBlock) * HEAP_MAXENTS;
        if (blks[i].type == MEM_FREE && blks[i].sz >= table_sz * 2)
        {
            PICO_InitHeap(&_heaps[_count], blks[i].sz - table_sz, HEAP_MAXENTS, 0x1000, true);
            _count++;
        }
    }   

    PICO_Log("%s Initialized heap manager - %u heaps created\n", DEBUG_OK, _count);
}

size_t PICO_GetHeapCount() { return _count; }

PICO_Heap* PICO_GetHeaps() { return _heaps; }