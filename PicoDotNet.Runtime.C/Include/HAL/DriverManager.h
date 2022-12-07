#pragma once
#include <Lib/Types.h>
#include <Lib/PointerList.h>
#include <HAL/Driver.h>

void PICO_InitDriverManager();
void PICO_InstallDriver(PICO_Driver* drv);
void PICO_InstallAndStartDriver(PICO_Driver* drv, void* arg);
void PICO_UninstallDriver(PICO_Driver* drv);
void PICO_StartDriver(PICO_Driver* drv, void* arg);
void PICO_StopDriver(PICO_Driver* drv);

PICO_Driver* PICO_FetchDriver(uint32_t id);
PICO_Driver* PICO_FetchDriverFromName(const char* name);
PICO_Driver* PICO_FetchDriverAt(int index);

size_t PICO_GetDriverCount();