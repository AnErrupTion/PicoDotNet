#include <Lib/Math.h>
#include <Core/Common.h>

int PICO_Clamp(int v, int min, int max)
{
    if (v < min) { return min; }
    if (v > max) { return max; }
    return v;
}

int PICO_Abs(int v)
{
    return (v < 0 ? -v : v);
}

float PICO_CeilF(float v)
{
    unsigned input;
    PICO_MemCopy(&input, &v, 4);
    int exponent = ((input >> 23) & 255) - 127;
    if (exponent < 0) return (v > 0);

    int fractional_bits = 23 - exponent;
    if (fractional_bits <= 0) return v;

    unsigned integral_mask = 0xffffffff << fractional_bits;
    unsigned output = input & integral_mask;

    PICO_MemCopy(&v, &output, 4);
    if (v > 0 && output != input) ++v;
    return v;
}

double PICO_CeilD(double v) { return (double)PICO_CeilF((float)v); }

float PICO_FloorF(float v)
{
    if (v >= INT64_MAX || v <= INT64_MIN || v != v) { return v; }
    uint64_t n = (uint64_t)v;
    float d = (float)n;
    if (d == v || v >= 0) { return d; } else { return d - 1; }
    return 0;
}

double PICO_FloorD(double v)
{
    if (v >= INT64_MAX || v <= INT64_MIN || v != v) { return v; }
    uint64_t n = (uint64_t)v;
    double d = (double)n;
    if (d == v || v >= 0) { return d; } else { return d - 1; }
    return 0;
}

float PICO_PowF(float x, int y)
{
    float temp;
    if (y == 0) { return 1; }
    temp = PICO_PowF(x, y / 2);
    if ((y % 2) == 0) { return temp * temp; } 
    else 
    {
        if (y > 0) { return x * temp * temp; }
        else { return (temp * temp) / x; }
    }
}

double PICO_PowD(double x, int y)
{
    double temp;
    if (y == 0) { return 1; }
    temp = PICO_PowD(x, y / 2);
    if ((y % 2) == 0) { return temp * temp; } 
    else 
    {
        if (y > 0) { return x * temp * temp; }
        else { return (temp * temp) / x; }
    }
}