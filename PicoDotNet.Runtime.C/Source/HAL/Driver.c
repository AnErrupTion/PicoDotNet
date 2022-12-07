#include <HAL/Driver.h>
#include <Core/Common.h>

PICO_Driver* PICO_NewDriver(const char* name, uint32_t id, size_t objsz, PICO_DriverStartEvent start, PICO_DriverStopEvent stop)
{
    PICO_Driver* driver   = PICO_Alloc(objsz < sizeof(PICO_Driver) ? sizeof(PICO_Driver) : objsz);
    driver->thread      = NULL;
    driver->is_threaded = false;
    driver->name        = PICO_NewString(name);
    driver->id          = id;
    driver->start       = start;
    driver->stop        = stop;
    PICO_Log("%s Created driver - ID:%p Size:%d Start:%p Stop:%p Name:%s\n", DEBUG_OK, id, objsz, start, stop, name);
    return driver;
}

PICO_Driver* PICO_NewDriverThreaded(const char* name, uint32_t id, size_t objsz, size_t stacksz, PICO_PtrList args, PICO_ThreadProtocol protocol, PICO_DriverStartEvent start, PICO_DriverStopEvent stop)
{
    PICO_Driver* driver   = PICO_Alloc(objsz < sizeof(PICO_Driver) ? sizeof(PICO_Driver) : objsz);
    driver->thread      = PICO_NewThread(name, stacksz, protocol, THREAD_PRIORITY_NORMAL, args);
    driver->is_threaded = true;
    driver->name        = driver->thread->name;
    driver->id          = id;
    driver->start       = start;
    driver->stop        = stop;
    PICO_Log("%s Created driver - ID:%p Size:%d Start:%p Stop:%p Main:%p Name:%s\n", DEBUG_OK, id, objsz, start, stop, protocol, name);
    return driver;
}

void PICO_FreeDriver(PICO_Driver* drv)
{
    if (drv == NULL) { PICO_Panic("PICO_FreeDriver(00000000) - Attempt to free null driver"); return; }
    if (!drv->is_threaded) { PICO_Free(drv->name); }
    PICO_Free(drv);
}