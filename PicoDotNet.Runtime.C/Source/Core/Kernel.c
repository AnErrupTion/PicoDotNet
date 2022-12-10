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
    // set local multiboot pointer so we can access it after we leave this function
    _mboot = mbp;

    // reset tick count
    _ticks = 0;

    // get the system ready enough for debugging output
    PICO_FlushBootScreen();
    PICO_FlushPrintBuffers();
    PICO_InitDebug();
    PICO_Log("%s Booting DotNetPico...\n", DEBUG_INFO);

    // parse multiboot memory map and passover to our own memory map
    PICO_InitMemMgr(true);

    // initalize kernel heap - for the moment it uses all available memory left at this point
    PICO_InitHeapManager();

    // initialize descriptor tables and interrupts
    PICO_InitGDT();
    PICO_InitIDT();

    // initialize multitasking and create kernel thread
    PICO_InitScheduler();
    PICO_InitKernelThread();

    // initialize device/driver manager
    PICO_InitDriverManager();

    // assume our ramdisk always exists and is the first module - then load it
    PICO_MemoryBlock* mod = PICO_GetMemBlockByType(MEM_MODULE);
    PICO_InitRAMFS(&_test_ramfs, (void*)mod->addr, mod->sz);

    // run system tests before completing boot sequence
    //PICO_SysTestHeap(10);
    //PICO_SysTestThreading(5);
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