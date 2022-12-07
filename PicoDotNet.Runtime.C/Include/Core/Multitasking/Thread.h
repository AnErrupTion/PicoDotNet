#pragma once
#include <Lib/Types.h>
#include <Lib/PointerList.h>

typedef enum { UNLOCKED, LOCKED } THREAD_LOCK;

typedef enum
{
    THREAD_HALTED,
    THREAD_WAITING,
    THREAD_RUNNING,
    THREAD_TERMINATED,
} THREAD_STATE;

typedef enum
{
    THREAD_PRIORITY_LOW,
    THREAD_PRIORITY_NORMAL,
    THREAD_PRIORITY_HIGH,
} THREAD_PRIORITY;

typedef struct
{
    uint64_t ticks;
    uint32_t tps;
    uint8_t  cpu_usage;
} PICO_ThreadTime;

typedef struct
{
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax, eflags;
} PICO_ThreadRegisters;

typedef int (*PICO_ThreadProtocol)(PICO_PtrList* args);

typedef struct
{
    PICO_ThreadRegisters registers;
    PICO_ThreadProtocol  protocol;
    PICO_ThreadTime      time;
    THREAD_STATE       state;
    THREAD_PRIORITY    priority;
    THREAD_LOCK        lock;
    PICO_PtrList         args;
    size_t             stacksz;
    uint32_t*          stack;
    uint32_t           id;
    char*              name;
} PICO_Thread;

PICO_Thread* PICO_NewThread(const char* name, size_t stacksz, PICO_ThreadProtocol protocol, THREAD_PRIORITY priority, PICO_PtrList args);
void PICO_FreeThread(PICO_Thread* thread);

extern PICO_Thread* THIS_THREAD;
extern PICO_Thread* NEXT_THREAD;