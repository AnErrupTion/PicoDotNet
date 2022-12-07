#pragma once
#include <Lib/Types.h>
#include <Lib/PointerList.h>
#include <Core/Multitasking/Thread.h>

typedef struct PICO_Driver PICO_Driver;

typedef bool (*PICO_DriverStartEvent)(PICO_Driver* drv, void*);
typedef void (*PICO_DriverStopEvent)(PICO_Driver* drv);

struct PICO_Driver
{
    PICO_Thread*          thread;
    PICO_DriverStartEvent start;
    PICO_DriverStopEvent  stop;
    uint32_t            id;
    char*               name;
    bool                is_threaded;
};

PICO_Driver* PICO_NewDriver(const char* name, uint32_t id, size_t objsz, PICO_DriverStartEvent start, PICO_DriverStopEvent stop);
PICO_Driver* PICO_NewDriverThreaded(const char* name, uint32_t id, size_t objsz, size_t stacksz, PICO_PtrList args, PICO_ThreadProtocol protocol, PICO_DriverStartEvent start, PICO_DriverStopEvent stop);
void PICO_FreeDriver(PICO_Driver* drv);