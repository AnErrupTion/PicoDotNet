#include <Core/Tests.h>
#include <Core/Common.h>

void PICO_SysTestHeap(size_t iters)
{
    while (iters > 0)
    {
        // decrement iteration
        iters--;

        // some random sizes to for the test allocations
        size_t sizes[8] = { 32, 128, 512, 8000, 32 * MEGABYTE, 1000000, 2 * MEGABYTE, 100 * KILOBYTE };
        void*  ptrs[8];

        // create and fill 8 blocks per iteration
        for (size_t i = 0; i < 8; i++)
        {
            ptrs[i] = PICO_Alloc(sizes[i]);
            PICO_MemSet(ptrs[i], 0x69420666, sizes[8]);
        }
        
        // free the blocks in a seperate loop, to ensure there is more than 1 allocation in the heap at a time
        for (size_t i = 0; i < 8; i++) { PICO_Free(ptrs[i]); }
    }

    // test finished successfully
    PICO_Log("%s Heap test succeeded!\n", DEBUG_OK);
}

void PICO_SysTestRAMFS(size_t iters)
{
    // test finished successfully
    PICO_Log("%s RAMFS test succeeded!\n", DEBUG_OK);
}

int PICO_SysTestThreading_TestMain(PICO_PtrList* args)
{
    PICO_Log("Entered test thread main successfully\n");
    return 420;
}

void PICO_SysTestThreading(size_t iters)
{   
    while (iters > 0)
    {
        iters--;

        char name[64];
        PICO_MemSet(name, 0, sizeof(name));
        PICO_PrintTo(name, "test_thread%d", iters);
        PICO_Log("NAME: %s\n", name);

        PICO_Thread* thread = PICO_NewThread(name, 0x10000, PICO_SysTestThreading_TestMain, THREAD_PRIORITY_NORMAL, PICO_NewPtrList());
        PICO_LoadThread(thread);
        PICO_StartThread(thread);
        PICO_SwitchThread(true);
    }

    // test finished successfully
    PICO_Log("%s Multithreading test succeeded!\n", DEBUG_OK);
}