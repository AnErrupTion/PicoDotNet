#pragma once
#include <Core/Memory/Heap.h>

void PICO_InitHeapManager();
void PICO_RegisterHeap(PICO_Heap* heap);

size_t PICO_GetHeapCount();
PICO_Heap* PICO_GetHeaps();