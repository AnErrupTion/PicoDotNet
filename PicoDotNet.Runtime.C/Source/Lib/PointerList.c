#include <Lib/PointerList.h>
#include <Core/Common.h>

PICO_PtrList PICO_NewPtrList()
{
    PICO_PtrList list = { NULL, 0 };
    return list;
}

PICO_PtrList PICO_DuplicatePtrList(PICO_PtrList* list)
{
    if (list == NULL || list->count == 0 || list->entries == NULL) { return PICO_NewPtrList(); }
    PICO_PtrList out = (PICO_PtrList){ PICO_Alloc(sizeof(void*) * list->count), list->count };
    return out;
}

void PICO_FreePtrList(PICO_PtrList* list, bool free_entries)
{
    if (list == NULL) { PICO_Panic("PICO_FreePtrList(00000000) - Attempt to free null pointer list"); return; }
    if (list->entries == NULL) { return; }
    if (free_entries)
    {
        for (size_t i = 0; i < list->count; i++) { PICO_Free(list->entries[i]); }
    }
    PICO_Free(list->entries);
    *list = (PICO_PtrList){ NULL, 0 };
}

void PICO_PtrListClear(PICO_PtrList* list, bool free_entries) { PICO_FreePtrList(list, free_entries); }

void* PICO_PtrListAdd(PICO_PtrList* list, void* value)
{
    if (list == NULL) { PICO_Panic("PICO_PtrListAdd(00000000, %p) - Attempt to add entry to null pointer list", value); return NULL; }
    void** entries = PICO_Alloc(sizeof(void*) * (list->count + 1));

    if (list->entries != NULL) { PICO_MemCopy(entries, list->entries, sizeof(void*) * list->count); PICO_Free(list->entries); }
    list->entries = entries;
    list->entries[list->count++] = value;
    return list->entries[list->count - 1];
}

bool PICO_PtrListErase(PICO_PtrList* list, int index, bool free)
{
    if (list == NULL) { PICO_Panic("PICO_PtrListErase(00000000, %d, %d) - Attempt to erase entry from null pointer list", index, free); return false; }
    if (index == 0 && list->count == 1) { PICO_FreePtrList(list, free); return true; }

    void** entries = PICO_Alloc(sizeof(void*) * (list->count - 1));

    int j = 0;
    for (size_t i = 0; i < list->count; i++) { if (i != (size_t)index) { entries[j++] = list->entries[i]; } }
    PICO_Free(list->entries);
    list->entries = entries;
    list->count--;
    return true;
}

void* PICO_PtrListAt(PICO_PtrList* list, int index)
{
    if (list == NULL) { PICO_Panic("PICO_PtrListAt(00000000, %d) - Index out of bounds", index); return NULL; }
    return list->entries[index];
}
