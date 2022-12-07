#include <Core/Debug.h>
#include <Core/Common.h>

static PICO_SerialController _serial;

void PICO_InitDebug()
{
    _serial.driver.id          = 0xFFFFFF00;
    _serial.driver.start       = (PICO_DriverStartEvent)PICO_StartSerial;
    _serial.driver.stop        = (PICO_DriverStopEvent)PICO_StopSerial;
    _serial.driver.is_threaded = false;
    _serial.driver.thread      = NULL;
    _serial.driver.name        = "Serial";
    PICO_StartSerial(&_serial, SERIAL_COM1);
}

void PICO_Log(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    PICO_PrintArgs(fmt, args);
    va_end(args);
}

void PICO_Error(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    PICO_Print("%s ", DEBUG_ERROR);
    PICO_PrintArgs(fmt, args);
    PICO_Print("\n");
    va_end(args);
}

void PICO_Panic(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    PICO_Print("%s ", DEBUG_ERROR);
    PICO_PrintArgs(fmt, args);
    va_end(args);
    PICO_Log("\nThe system has been been halted to prevent any potential damage to\nyour computer.\n");
    asm volatile("cli; hlt");
}

void PICO_Breakpoint()
{
    asm volatile("xchg %bx, %bx");
}

PICO_SerialController* PICO_GetDebugSerial()
{
    return (PICO_SerialController*)&_serial;
}