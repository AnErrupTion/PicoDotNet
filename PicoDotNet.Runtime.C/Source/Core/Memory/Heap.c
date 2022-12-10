#include <Core/Memory/Heap.h>
#include <Core/Common.h>

void PICO_InitHeap(PICO_Heap* heap, size_t sz, size_t max_ents, size_t align, bool auto_collect)
{
    if (heap == NULL) { PICO_Panic("PICO_InitHeap(00000000, %u, %u, %u, %d) - Attempt to access null heap", sz, max_ents, align, auto_collect); return; }
    heap->memblk_table  = PICO_RequestMemBlock(max_ents * sizeof(PICO_HeapBlock));
    heap->memblk_data   = PICO_RequestMemBlock(sz);
    heap->sz            = sz;
    heap->count         = 0;
    heap->max           = max_ents;
    heap->alignment     = align;
    heap->auto_collect  = auto_collect;
    heap->blocks        = (PICO_HeapBlock*)heap->memblk_table->addr;

    PICO_HeapCreateBlock(heap, (PICO_HeapBlock){ heap->memblk_data->addr, heap->sz, MEM_FREE, NULL });

    PICO_Log("%s Heap - Table:%p-%p Data:%p-%p Size:%a Max:%u Align:%p AC:%d\n", DEBUG_OK, 
            heap->memblk_table->addr, heap->memblk_table->addr + heap->memblk_table->sz, heap->memblk_data->addr, heap->memblk_data->addr + heap->memblk_data->sz, heap->sz, heap->max, heap->alignment, heap->auto_collect);
}

void* PICO_HeapAllocate(PICO_Heap* heap, size_t sz, bool zero_fill)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapAllocate(00000000, %a, %d) - Attempt to access null heap", sz, zero_fill); return NULL; }
    if (sz > 0) { sz = PICO_MemAlign(sz, heap->alignment); }

    PICO_HeapBlock* blk = PICO_HeapRequestBlock(heap, sz);
    if (blk == NULL) { return NULL; }

    if (zero_fill) { PICO_MemSet((void*)blk->addr, 0, blk->sz); }
    PICO_Log("%s Region:%p-%p Size:%a\n", DEBUG_MALLOC, blk->addr, blk->addr + blk->sz, blk->sz);
    return (void*)blk->addr;
}

bool PICO_HeapFree(PICO_Heap* heap, void* ptr)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapFree(00000000, %p) - Attempt to access null heap", ptr); return false; }
    if (ptr  == NULL) { PICO_Panic("PICO_HeapFree(%p, 00000000) - Attempt to free null heap block", heap); return false; }

    for (size_t i = 0; i < heap->max; i++)
    {
        if (heap->blocks[i].type == MEM_INVALID) { continue; }
        if (heap->blocks[i].addr == (uintptr_t)ptr)
        {
            heap->blocks[i].type = MEM_FREE;
            PICO_Log("%s Region:%p-%p Size:%a\n", DEBUG_FREE, heap->blocks[i].addr, heap->blocks[i].addr + heap->blocks[i].sz, heap->blocks[i].sz);
            if (heap->auto_collect) 
            { 
                size_t collected = PICO_HeapCollect(heap); 
                if (collected > 0) { PICO_Log("%s Collected and merged %u free heap blocks\n", DEBUG_INFO, collected); }
            }
            return true;
        }
    }
    return false;
}

size_t PICO_HeapCollect(PICO_Heap* heap)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapCollect(00000000) - Attempt to access null heap"); return 0; }

    size_t c = 0;
    PICO_HeapBlock* nblk;
    for (size_t i = 0; i < heap->max; i++)
    {
        if (heap->blocks[i].type != MEM_FREE) { continue; }
        nblk = PICO_HeapNearestBlock(heap, &heap->blocks[i]);
        if (nblk != NULL) { c += PICO_HeapMerge(heap, &heap->blocks[i], nblk); }
    }

    nblk = PICO_HeapNearestBlock(heap, &heap->blocks[0]);
    if (nblk != NULL) { c += PICO_HeapMerge(heap, &heap->blocks[0], nblk); }

    return c;
}

bool PICO_HeapMerge(PICO_Heap* heap, PICO_HeapBlock* blk1, PICO_HeapBlock* blk2)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapMerge(00000000, %p, %p) - Attempt to access null heap", blk1, blk2); return false; }
    if (blk1 == NULL || blk2 == NULL) { return false; }
    if (blk1->addr > blk2->addr) { blk1->addr = blk2->addr; }
    blk1->sz += blk2->sz;
    PICO_HeapRemoveBlock(heap, blk2);
    return true;
}

PICO_HeapBlock* PICO_HeapRequestBlock(PICO_Heap* heap, size_t sz)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapSize(00000000, %a) - Attempt to access null heap", sz); return NULL; }
    if (sz   == 0)    { PICO_Panic("PICO_HeapRequestBlock(%p, 0) - Attempt to request 0 byte heap block", heap); return NULL; }
    
    for (size_t i = 0; i < heap->max; i++)
    {
        if (heap->blocks[i].sz >= sz && heap->blocks[i].type == MEM_FREE)
        {
            PICO_HeapBlock* blk     = PICO_HeapCreateBlock(heap, (PICO_HeapBlock){ heap->blocks[i].addr, sz, MEM_ALLOC, NULL });
            heap->blocks[i].addr += sz;
            heap->blocks[i].sz   -= sz;
            return blk;
        }
    }
    return NULL;
}

PICO_HeapBlock* PICO_HeapNextBlock(PICO_Heap* heap)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapNextBlock(00000000) - Attempt to access null heap"); return NULL; }
    
    for (size_t i = 0; i < heap->max; i++) { if (heap->blocks[i].type == MEM_INVALID) { return &heap->blocks[i]; } }

    PICO_Panic("PICO_HeapNextBlock(%p) - Maximum amount of heap blocks reached", heap);
    return NULL;
}

PICO_HeapBlock* PICO_HeapNearestBlock(PICO_Heap* heap, PICO_HeapBlock* blk)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapNearestBlock(00000000, %p) - Attempt to access null heap", blk); return NULL; }
    if (blk  == NULL) { return NULL; }

    for (size_t i = 0; i < heap->max; i++)
    {
        if (heap->blocks[i].type != MEM_FREE) { continue; }
        if (heap->blocks[i].addr + heap->blocks[i].sz == blk->addr) { return &heap->blocks[i]; }
        if (blk->addr - blk->sz == heap->blocks[i].addr) { return &heap->blocks[i]; }
    }
    return NULL;
}

PICO_HeapBlock* PICO_HeapCreateBlock(PICO_Heap* heap, PICO_HeapBlock blk)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapCreateBlock(00000000, %p) - Attempt to access null heap", blk); return NULL; }
    if (blk.sz == 0 || blk.addr == 0) { PICO_Panic("PICO_HeapCreateBlock(%p, 00000000) - Attempt to create invalid heap block", heap); return NULL; }

    PICO_HeapBlock* p_blk = PICO_HeapNextBlock(heap);
    *p_blk = blk;
    heap->count++;
    return p_blk;
}

void PICO_HeapRemoveBlock(PICO_Heap* heap, PICO_HeapBlock* blk)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapRemoveBlock(00000000, %p) - Attempt to access null heap", blk); return; }
    if (blk  == NULL) { PICO_Panic("PICO_HeapRemoveBlock(%p, 00000000) - Attempt to remove null block from heap", heap); return; }

    for (size_t i = 0; i < heap->max; i++)
    {
        if (&heap->blocks[i] == blk)
        {
            heap->blocks[i] = (PICO_HeapBlock){ 0, 0, MEM_INVALID, NULL };
            heap->count--;
            return;
        }
    }
    PICO_Panic("PICO_HeapRemoveBlock(%p, %p) - Failed to remove heap block", heap, blk);
}

PICO_HeapBlock* PICO_HeapFetch(PICO_Heap* heap, void* ptr)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapFetch(00000000, %p) - Attempt to access null heap", ptr); return NULL; }
    if (ptr  == NULL) { return NULL;}

    for (size_t i = 0; i < heap->max; i++)
    {
        if (heap->blocks[i].type != MEM_ALLOC) { continue; }
        if (heap->blocks[i].addr == (uintptr_t)ptr) { return &heap->blocks[i]; }
    }
    return NULL;
}

size_t PICO_HeapCountType(PICO_Heap* heap, MEMORY_TYPE type)
{
    if (heap == NULL) { PICO_Panic("PICO_HeapCountType(00000000) - Attempt to access null heap"); return 0; }

    size_t sz = 0;
    for (size_t i = 0; i < heap->max; i++)
    {
        if (heap->blocks[i].type != type) { continue; }
        sz += heap->blocks[i].sz;
    }
    return sz;
}

size_t PICO_HeapAmountFree(PICO_Heap* heap) { return PICO_HeapCountType(heap, MEM_FREE); }

size_t PICO_HeapAmountUsed(PICO_Heap* heap) { return PICO_HeapCountType(heap, MEM_ALLOC); }

size_t PICO_HeapSize(PICO_Heap* heap) { return PICO_HeapCountType(heap, MEM_FREE) + PICO_HeapCountType(heap, MEM_ALLOC); }