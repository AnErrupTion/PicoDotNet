#pragma once
#include <Core/Multiboot.h>

/// @brief Start critical system components @param mbp Pointer to multiboot header
void PICO_KernelBoot(PICO_Multiboot* mbp);

/// @brief Main loop of kernel thread
void PICO_KernelRun();

/// @brief Get multiboot header @return Pointer to multiboot header
PICO_Multiboot* PICO_GetMultiboot();

/// @brief Clear entire VGA memory buffer
void PICO_FlushBootScreen();

/// @brief Get total amount of kernel ticks
uint64_t PICO_GetKernelTicks();

/// @brief Retrieve starting address of kernel memory
uintptr_t PICO_GetKernelStart();

/// @brief Retrieve end address of kernel memory
uintptr_t PICO_GetKernelEnd();

/// @brief Retrieve size of kernel memory
size_t PICO_GetKernelSize();

/// @brief Retrieve starting address/initial bottom of kernel stack
uintptr_t PICO_GetKernelStackBottom();

/// @brief Retrieve end address/initial top of kernel stack
uintptr_t PICO_GetKernelStackTop();

/// @brief Retrieve size of kernel stack
size_t PICO_GetKernelStackSize();