#pragma once
#include <Lib/Types.h>

typedef struct
{
    void** entries;
    size_t count;
} PICO_PtrList;

PICO_PtrList PICO_NewPtrList();
PICO_PtrList PICO_DuplicatePtrList(PICO_PtrList* list);
void PICO_FreePtrList(PICO_PtrList* list, bool free_entries);
void PICO_PtrListClear(PICO_PtrList* list, bool free_entries);
void* PICO_PtrListAdd(PICO_PtrList* list, void* value);
bool  PICO_PtrListErase(PICO_PtrList* list, int index, bool free);
void* PICO_PtrListAt(PICO_PtrList* list, int index);
