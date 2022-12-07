#include <Lib/Memory.h>
#include <Core/Common.h>

uint32_t PICO_MemAlign(uint32_t value, uint32_t alignment)
{
    uint32_t out = value;
    out &= (0xFFFFFFFF - (alignment - 1));
    if (out < value) { out += alignment; }
    return out;
}

uint64_t PICO_MemAlign64(uint64_t value, uint64_t alignment)
{
    uint64_t out = value;
    out &= (0xFFFFFFFFFFFFFFFF - (alignment - 1));
    if (out < value) { out += alignment; }
    return out;
}

void* PICO_MemCopy(void* dest, const void* src, size_t sz)
{
    uint32_t  num_dwords = sz / 4;
    uint32_t  num_bytes  = sz % 4;
    uint32_t* dest32     = (uint32_t*)dest;
    uint32_t* src32      = (uint32_t*)src;
    uint8_t*  dest8      = ((uint8_t*)dest) + num_dwords * 4;
    uint8_t*  src8       = ((uint8_t*)src) + num_dwords * 4;
    asm volatile("cld;rep movsl" : "+D"(dest32), "+S"(src32), "+c"(num_dwords) : : "memory");
    asm volatile("cld;rep movsb" : "+D"(dest8),  "+S"(src8),  "+c"(num_bytes)  : : "memory");
    return dest;
}

void* PICO_MemSet(void* ptr, int v, size_t sz)
{
    uint32_t  num_dwords = sz / 4;
    uint32_t  num_bytes  = sz % 4;
    uint32_t* dest32     = (uint32_t*)ptr;
    uint8_t*  dest8      = ((uint8_t*)ptr) + num_dwords * 4;
    asm volatile("cld;rep stosl" : "+D"(dest32), "+c"(num_dwords) : "a"(v) : "memory");
    asm volatile("cld;rep stosb" : "+D"(dest8),  "+c"(num_bytes)  : "a"(v) : "memory");
    return ptr;
}

void* PICO_MemSet16(void* ptr, uint16_t v, size_t sz)
{
    return (uint16_t*)PICO_MemSet(ptr, (v << 16) | v, sz);
}

int PICO_MemCompare(const void* ptr1, const void* ptr2, size_t sz)
{
    int r = 0;
    uint8_t* x = (uint8_t*)ptr1;
    uint8_t* y = (uint8_t*)ptr2;

    while (sz--) 
    {
        r = *x - *y;
        if (r) { return r; }
        x++; y++;
    }
    return 0;
}

const void* PICO_MemLocate(const void* ptr, int v, size_t sz)
{
    uint8_t* p    = (uint8_t*)ptr;
    uint8_t* find = NULL;
    while((ptr != NULL) && (sz--))
    {
        if (*p != (uint8_t)v) { p++; } else { find = p; break; }
    }
    return find;
}

void* PICO_Alloc(size_t sz)
{
    for (size_t i = 0; i < PICO_GetHeapCount(); i++)
    {
        if (PICO_GetHeaps()[i].sz == 0) { continue; }
        void* ptr = PICO_HeapAllocate(&PICO_GetHeaps()[i], sz, true);
        if (ptr != NULL) { return ptr; }
    }

    PICO_Panic("PICO_Alloc(%a) - Failed to allocate memory", sz);
    return NULL;
}

void PICO_Free(void* ptr)
{
    for (size_t i = 0; i < PICO_GetHeapCount(); i++)
    {
        if (PICO_GetHeaps()[i].sz == 0) { continue; }
        bool freed = PICO_HeapFree(&PICO_GetHeaps()[i], ptr);
        if (freed) { return; }
    }
    
    PICO_Panic("PICO_Free(%p) - Failed to free pointer to allocated memory", ptr);
}