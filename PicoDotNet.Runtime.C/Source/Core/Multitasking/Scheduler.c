#include "Core/Multitasking/Scheduler.h"
#include <Core/Common.h>

extern void main(void*);
extern void _context_switch();

static PICO_PtrList _threads;
static int        _active;
static uint32_t   _tid;
static bool       _modifying;
static bool       _ready;

void PICO_InitScheduler()
{
    _threads   = PICO_NewPtrList();
    _tid       = 0;
    _active    = 0;
    _modifying = false;
    _ready     = false;
    PICO_Log("%s Initialized scheduler\n", DEBUG_OK);
}

void PICO_InitKernelThread()
{
    PICO_Thread* thread = PICO_Alloc(sizeof(PICO_Thread));
    thread->name      = PICO_NewString("kernel");
    thread->id        = _tid++;
    thread->priority  = THREAD_PRIORITY_NORMAL;
    thread->state     = THREAD_RUNNING;
    thread->protocol  = (PICO_ThreadProtocol)main;
    thread->stack     = (uint32_t*)PICO_GetKernelStackBottom();
    thread->stacksz   = PICO_GetKernelStackSize();
    PICO_Log("%s Ptr:%p Stack:%p-%p Entry:%p Args:%u ID:%x Name:%s\n", DEBUG_THREAD, thread, thread->stack, (uint32_t)thread->stack + thread->stacksz, thread->protocol, thread->args.count, thread->id, thread->name);
    PICO_LoadThread(thread);
}

void PICO_SwitchThread(bool unlock)
{
    if (_modifying || !_ready) { return; }
    asm volatile("cli");
    _modifying = true;

    THIS_THREAD = PICO_PtrListAt(&_threads, _active);
    if (THIS_THREAD->lock == LOCKED)
    {
        if (!unlock) { asm volatile("sti"); _modifying = false; return; }
        THIS_THREAD->lock = UNLOCKED;
    }

    while (true)
    {
        _active++;
        PICO_Thread* thread = PICO_PtrListAt(&_threads, _active);

        if ((size_t)_active >= _threads.count) { _active = 0; NEXT_THREAD = PICO_PtrListAt(&_threads, 0); break; }
        if (thread == NULL) { PICO_Panic("Null thread located in scheduler"); return; }
        if (thread->state == THREAD_HALTED || thread->state == THREAD_WAITING) { continue; }
        if (thread->state == THREAD_TERMINATED) { PICO_UnloadThread(thread); continue; }
        NEXT_THREAD = thread;
        break;
    }

    _modifying = false;
    _context_switch();
}

void PICO_LoadThread(PICO_Thread* thread)
{
    if (thread == NULL) { PICO_Panic("PICO_LoadThread(00000000) - Attempt to load null thread into scheduler"); return; }
    _modifying = true;
    PICO_PtrListAdd(&_threads, thread);
    PICO_Log("%s Loaded thread %x(%s) at %p\n", DEBUG_INFO, thread->id, thread->name, thread);
    _modifying = false;
}

void PICO_UnloadThread(PICO_Thread* thread)
{
    if (thread == NULL) { PICO_Panic("PICO_UnloadThread(00000000) - Attempt to unload null thread from scheduler"); return; }
    _modifying = true;
    for (size_t i = 0; i < _threads.count; i++)
    {
        PICO_Thread* t = PICO_PtrListAt(&_threads, i);
        if (thread == t)
        {
            PICO_Log("%s Unloading thread %x(%s) at %p\n", DEBUG_INFO, thread->id, thread->name, thread);
            PICO_PtrListErase(&_threads, i, false);
            PICO_FreeThread(thread);
            _modifying = false;
            return;
        }
    }
    _modifying = false;
    PICO_Panic("PICO_UnloadThread(%p) - Failed to unload thread", thread);
}

void PICO_StartThread(PICO_Thread* thread)
{
    if (thread == NULL) { PICO_Panic("PICO_StartThread(00000000) - Attempt to start null thread"); return; }
    if (thread->state == THREAD_RUNNING) { return; }
    _modifying = true;
    thread->state = THREAD_RUNNING;
    PICO_Log("%s Started thread %x(%s) at %p\n", DEBUG_INFO, thread->id, thread->name, thread);
    _modifying = false;
}

void PICO_StopThread(PICO_Thread* thread)
{
    if (thread == NULL) { PICO_Panic("PICO_StopThread(00000000) - Attempt to stop null thread"); return; }
    if (thread->state == THREAD_HALTED) { return; }
    _modifying = true;
    thread->state = THREAD_HALTED;
    PICO_Log("%s Stopped thread %x(%s) at %p\n", DEBUG_INFO, thread->id, thread->name, thread);
    _modifying = false;
}

void PICO_TerminateThread(PICO_Thread* thread)
{
    if (thread == NULL) { PICO_Panic("PICO_StopThread(00000000) - Attempt to stop null thread"); return; }
    if (thread->state == THREAD_TERMINATED) { return; }
    _modifying = true;
    thread->state = THREAD_TERMINATED;
    PICO_Log("%s Terminated thread %x(%s) at %p\n", DEBUG_INFO, thread->id, thread->name, thread);
    _modifying = false;
}

void PICO_ToggleScheduler(bool enabled) { _ready = enabled; }

uint32_t PICO_GenerateThreadID() { return _tid++; }

uint32_t PICO_GetThreadCount() { return _threads.count; }