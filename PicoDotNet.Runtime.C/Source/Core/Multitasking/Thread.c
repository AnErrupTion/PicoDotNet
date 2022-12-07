#include <Core/Multitasking/Thread.h>
#include <Core/Common.h>

#define STACKSZ_MIN (4 * KILOBYTE)
#define STACKSZ_MAX (8 * MEGABYTE)

PICO_Thread* THIS_THREAD = NULL;
PICO_Thread* NEXT_THREAD = NULL;

void PICO_OnThreadReturn()
{
    register int eax asm("eax");   
    int exitcode = eax;

    asm volatile("cli");
    PICO_TerminateThread(THIS_THREAD);
    PICO_Log("%s Thread %x(%s) has exited with code %d\n", DEBUG_INFO, THIS_THREAD->id, THIS_THREAD->name, exitcode);

    asm volatile("sti");
    while (true) { PICO_SwitchThread(true); }
    
}

PICO_Thread* PICO_NewThread(const char* name, size_t stacksz, PICO_ThreadProtocol protocol, THREAD_PRIORITY priority, PICO_PtrList args)
{    
    PICO_Thread* thread = PICO_Alloc(sizeof(PICO_Thread*));
    thread->name      = PICO_NewString(name);
    thread->stacksz   = PICO_Clamp(stacksz, STACKSZ_MIN, STACKSZ_MAX);
    thread->stack     = PICO_Alloc(thread->stacksz);
    thread->id        = PICO_GenerateThreadID();
    thread->protocol  = protocol;
    thread->priority  = priority;
    thread->lock      = UNLOCKED;
    thread->state     = THREAD_HALTED;
    thread->args      = PICO_DuplicatePtrList(&args);
    thread->time      = (PICO_ThreadTime) { 0, 0, 0 };
    
    uint32_t* stk = (uint32_t*)((uintptr_t)thread->stack + (thread->stacksz - sizeof(PICO_ThreadRegisters) - 16));
    *--stk = (uint32_t)thread;
    *--stk = (uint32_t)&thread->args;
    *--stk = (uint32_t)PICO_OnThreadReturn;
    *--stk = (uint32_t)protocol;

    thread->registers.edx    = (uint32_t)thread;
    thread->registers.esp    = (uint32_t)stk;
    thread->registers.eflags = (uint32_t)0x202;

    PICO_Log("%s Ptr:%p Stack:%p-%p Entry:%p Args:%u ID:%x Name:%s\n", DEBUG_THREAD, thread, thread->stack, (uint32_t)thread->stack + thread->stacksz, thread->protocol, thread->args.count, thread->id, thread->name);
    return thread;
}

void PICO_FreeThread(PICO_Thread* thread)
{
    if (thread == NULL) { PICO_Panic("PICO_FreeThread(00000000) - Attempt to free null thread"); return; }
    PICO_FreePtrList(&thread->args, false);
    PICO_Free(thread->name);
    PICO_Free(thread->stack);
    PICO_Free(thread);
}