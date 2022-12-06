#pragma once
#include <Lib/Types.h>

/// @brief Clear the working buffers used for primary print functions
void PICO_FlushPrintBuffers();

/// @brief Print list of arguments @param fmt Pointer to formatted string @param args Variadic arguments
void PICO_PrintArgs(const char* fmt, va_list args);

/// @brief Print list of arguments @param fmt Pointer to formatted string @param ... Arguments
void PICO_Print(const char* fmt, ...);

/// @brief Print list of arguments to specified location @param buff Pointer to output buffer @param fmt Pointer to formatted string @param args Variadic arguments
void PICO_PrintArgsTo(char* buff, const char* fmt, va_list args);

/// @brief Print list of arguments to specified location @param buff Pointer to output buffer @param fmt Pointer to formatted string @param ... Arguments
void PICO_PrintTo(char* buff, const char* fmt, ...);