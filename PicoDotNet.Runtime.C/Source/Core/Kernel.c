#include <Core/Common.h>

extern uintptr_t _kernel_start;
extern uintptr_t _kernel_end;
extern uintptr_t _stack_top;
extern uintptr_t _stack_bottom;

static PICO_Multiboot* _mboot;
static uint64_t      _ticks;
static PICO_RAMFS _test_ramfs;

void PICO_KernelBoot(PICO_Multiboot* mbp)
{
    _mboot = mbp;
    _ticks = 0;

    PICO_FlushBootScreen();
    PICO_FlushPrintBuffers();
    PICO_InitDebug();
    
    PICO_Log("%s Booting DotNetPico...\n", DEBUG_INFO);

    PICO_InitMemMgr(true);
    PICO_InitHeapManager();

    PICO_InitGDT();
    PICO_InitIDT();

    PICO_InitScheduler();
    PICO_InitKernelThread();

    PICO_InitDriverManager();

    PICO_MemoryBlock* mod = PICO_GetMemBlockByType(MEM_MODULE);
    PICO_Log("%s RAMDISK Module: %p-%p\n", DEBUG_INFO, mod->addr, mod->addr + mod->sz);

    PICO_InitRAMFS(&_test_ramfs, (void*)mod->addr, mod->sz);

    PICO_RAMFile* file = PICO_OpenRAMFile(&_test_ramfs, "hello.txt");
    if (file == NULL) { PICO_Panic("FAILED TO LOCATE FILE"); }
    else { PICO_Log("File contents:\n%s\n", (char*)PICO_ReadRAMFileData(&_test_ramfs, file)); }
}

void PICO_KernelRun()
{
    PICO_Log("%s Entered kernel main\n", DEBUG_OK);
    while (true)
    {
        PICO_SwitchThread(true);   
    }
}

void PICO_FlushBootScreen()
{
    PICO_MemSet16((void*)0xB8000, 0x0F20, 80 * 25 * 2);
}

PICO_Multiboot* PICO_GetMultiboot() { return _mboot; }

uint64_t PICO_GetKernelTicks() { return _ticks; }

uintptr_t PICO_GetKernelStart() { return (uintptr_t)&_kernel_start; }

uintptr_t PICO_GetKernelEnd() { return (uintptr_t)&_kernel_end; }

size_t PICO_GetKernelSize() { return PICO_GetKernelEnd() - PICO_GetKernelStart(); }

uintptr_t PICO_GetKernelStackBottom() { return (uintptr_t)&_stack_bottom; }

uintptr_t PICO_GetKernelStackTop() { return (uintptr_t)&_stack_top; }

size_t PICO_GetKernelStackSize() { return PICO_GetKernelStackTop() - PICO_GetKernelStackBottom(); }