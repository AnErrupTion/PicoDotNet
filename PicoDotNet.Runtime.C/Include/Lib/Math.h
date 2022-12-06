#pragma once
#include <Lib/Types.h>

/// @brief Integer clamp
int PICO_Clamp(int v, int min, int max);

/// @brief Integer ABS
int PICO_Abs(int v);

/// @brief Floating-point ceiling
float PICO_CeilF(float v);

/// @brief Double ceiling
double PICO_CeilD(double v);

/// @brief Floating-point floor
float PICO_FloorF(float v);

/// @brief Double floor
double PICO_FloorD(double v);

/// @brief Floating-point power
float PICO_PowF(float x, int y);

/// @brief Double power
double OS_PowD(double x, int y);