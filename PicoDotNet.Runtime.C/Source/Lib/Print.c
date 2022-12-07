#include <Lib/Print.h>
#include <Core/Common.h>

#define PRINT_BUFFSZ 0x10000
#define PRINT_WORKSZ 0x1000

char _buffer[PRINT_BUFFSZ];
char _workbuff[PRINT_WORKSZ];

void PICO_FlushPrintBuffers()
{
    PICO_MemSet(_buffer,   0, PRINT_BUFFSZ);
    PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
}

void PICO_PrintArgs(const char* fmt, va_list args)
{
    PICO_FlushPrintBuffers();
    PICO_PrintArgsTo(_buffer, fmt, args);
    PICO_SerialPrint(PICO_GetDebugSerial(), _buffer);
}

void PICO_Print(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    PICO_PrintArgs(fmt, args);
    va_end(args);
}

void PICO_PrintArgsTo(char* buff, const char* fmt, va_list args)
{
    if (buff == NULL) { return; }
    if (fmt == NULL || PICO_StrLen(fmt) == 0) { return; }

    while (*fmt != 0)
    {
        if (*fmt == '%')
        {
            fmt++;
            if (*fmt == '%') { PICO_StrAppend(buff, '%'); fmt++; }
            else if (*fmt == 'c') { PICO_StrAppend(buff, va_arg(args, int)); }
            else if (*fmt == 'd')
            {
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertIntToStr(va_arg(args, int), _workbuff, 10));
            }
            else if (*fmt == 'u')
            {
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertUIntToStr(va_arg(args, uint32_t), _workbuff, 10));
            }
            else if (*fmt == 'x')
            {
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertUIntToStr(va_arg(args, uint32_t), _workbuff, 16));
            }
            else if (*fmt == '2')
            {
                fmt++;
                if (*fmt != 'x' && *fmt != 'X') { PICO_StrAppend(_buffer, *fmt); fmt++; continue; }
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertUIntToHex(va_arg(args, uint32_t), _workbuff, 1));
            }
            else if (*fmt == '4')
            {
                fmt++;
                if (*fmt != 'x' && *fmt != 'X') { PICO_StrAppend(_buffer, *fmt); fmt++; continue; }
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertUIntToHex(va_arg(args, uint32_t), _workbuff, 2));
            }
            else if (*fmt == '8')
            {
                fmt++;
                if (*fmt != 'x' && *fmt != 'X') { PICO_StrAppend(_buffer, *fmt); fmt++; continue; }
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertUIntToHex(va_arg(args, uint32_t), _workbuff, 4));
            }
            else if (*fmt == 'p')
            {
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertUIntToHex(va_arg(args, uint32_t), _workbuff, 4));
            }
            else if (*fmt == 'a')
            {
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);

                uint32_t v = va_arg(args, uint32_t);
                if (v < KILOBYTE)                       { PICO_StrConcat(_buffer, PICO_ConvertUIntToStr(v, _workbuff, 10)); PICO_StrConcat(_buffer, "B"); }
                else if (v >= KILOBYTE && v < MEGABYTE) { PICO_StrConcat(_buffer, PICO_ConvertUIntToStr(v / KILOBYTE, _workbuff, 10)); PICO_StrConcat(_buffer, "KB"); }
                else if (v >= MEGABYTE && v < GIGABYTE) { PICO_StrConcat(_buffer, PICO_ConvertUIntToStr(v / MEGABYTE, _workbuff, 10)); PICO_StrConcat(_buffer, "MB"); }
                else if (v >= GIGABYTE)                 { PICO_StrConcat(_buffer, PICO_ConvertUIntToStr(v / GIGABYTE, _workbuff, 10)); PICO_StrConcat(_buffer, "GB"); }
            }
            else if (*fmt == 'f')
            {
                PICO_MemSet(_workbuff, 0, PRINT_WORKSZ);
                PICO_StrConcat(_buffer, PICO_ConvertFloatToStr(va_arg(args, float), _workbuff, 3));
            }
            else if (*fmt == 's') { PICO_StrConcat(_buffer, va_arg(args, char*)); }
            else { PICO_StrAppend(_buffer, *fmt); }
        }
        else { PICO_StrAppend(_buffer, *fmt); }
        fmt++;
    }
}

void PICO_PrintTo(char* buff, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    PICO_PrintArgsTo(buff, fmt, args);
    va_end(args);
}