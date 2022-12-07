#include <HAL/DriverManager.h>
#include <Core/Common.h>

static PICO_PtrList _drivers;

bool drv_start(PICO_Driver* drv, void* arg)
{
    PICO_Log("STARTED TEST DRIVER\n");
    return true;
}

void drv_stop(PICO_Driver* drv)
{
    PICO_Log("STOPPED TEST DRIVER\n");
}

void PICO_InitDriverManager()
{
    _drivers = PICO_NewPtrList();

    PICO_InstallDriver((PICO_Driver*)PICO_GetDebugSerial());

    PICO_Log("%s Initialized driver manager - %u drivers installed\n", DEBUG_OK, _drivers.count);
}

void PICO_InstallDriver(PICO_Driver* drv)
{
    if (drv == NULL) { PICO_Panic("PICO_InstallDriver(00000000) - Attempt to install null device driver"); return; }
    PICO_PtrListAdd(&_drivers, drv);
    PICO_Log("%s Installed device driver %p(%s) at %p\n", DEBUG_INFO, drv->id, drv->name, drv);
}

void PICO_InstallAndStartDriver(PICO_Driver* drv, void* arg)
{
    PICO_InstallDriver(drv);
    PICO_StartDriver(drv, arg);
}

void PICO_UninstallDriver(PICO_Driver* drv)
{
    if (drv == NULL) { PICO_Panic("PICO_UninstallDriver(00000000) - Attempt to uninstall null device driver"); return; }
    for (size_t i = 0; i < _drivers.count; i++)
    {
        PICO_Driver* d = PICO_PtrListAt(&_drivers, i);
        if (d == drv)
        {
            PICO_PtrListErase(&_drivers, i, false);
            PICO_Log("%s Uninstalled device driver %p(%s) at %p\n", DEBUG_INFO, drv->id, drv->name, drv);
            if (drv->is_threaded && drv != NULL) { PICO_TerminateThread(drv->thread); }
            PICO_FreeDriver(drv);
            return;
        }
    }
    PICO_Panic("PICO_UninstallDriver(%p) - Failed to uninstall device driver", drv);
}

void PICO_StartDriver(PICO_Driver* drv, void* arg)
{
    if (drv == NULL) { PICO_Panic("PICO_StartDriver(00000000) - Attempt to start null device driver"); return; }
    drv->start(drv, arg);
    if (drv->is_threaded && drv->thread != NULL) { PICO_StartThread(drv->thread); }
    PICO_Log("%s Started device driver %p(%s) at %p\n", DEBUG_INFO, drv->id, drv->name, drv);
}

void PICO_StopDriver(PICO_Driver* drv)
{
    if (drv == NULL) { PICO_Panic("PICO_StartDriver(00000000) - Attempt to start null device driver"); return; }
    drv->stop(drv);
    if (drv->is_threaded && drv->thread != NULL) { PICO_StopThread(drv->thread); }
    PICO_Log("%s Stopped device driver %p(%s) at %p\n", DEBUG_INFO, drv->id, drv->name, drv);
}

PICO_Driver* PICO_FetchDriver(uint32_t id)
{
    if (id == 0) { return NULL; }

    for (size_t i = 0; i < _drivers.count; i++)
    {
        PICO_Driver* drv = PICO_PtrListAt(&_drivers, i);
        if (drv->id == id) { return drv; }
    }
    return NULL;
}

PICO_Driver* PICO_FetchDriverFromName(const char* name)
{
    if (name == NULL || PICO_StrLen(name) == 0) { return NULL; }

    for (size_t i = 0; i < _drivers.count; i++)
    {
        PICO_Driver* drv = PICO_PtrListAt(&_drivers, i);
        if (PICO_StrEquals(drv->name, name)) { return drv; }
    }
    return NULL;
}

PICO_Driver* PICO_FetchDriverAt(int index) { return PICO_PtrListAt(&_drivers, index); }

size_t PICO_GetDriverCount() { return _drivers.count; }