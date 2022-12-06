#include <Lib/Char.h>

bool PICO_IsAlpha(char c)
{
    if (c >= 'a' && c <= 'z') { return true; }
    if (c >= 'A' && c <= 'Z') { return true; }
    return false;
}

bool PICO_IsDigit(char c)
{
    if (c >= '0' && c <= '9') { return true; }
    return false;
}

bool PICO_IsHexDigit(char c)
{
    if (c >= '0' && c <= '9') { return true; }
    if (c >= 'A' && c <= 'F') { return true; }
    if (c >= 'a' && c <+ 'f') { return true; }
    return false;
}

bool PICO_IsAlphaNum(char c)
{
    if (PICO_IsAlpha(c)) { return true; }
    if (PICO_IsDigit(c)) { return true; }
    return false;
}

bool PICO_IsControl(char c)
{
    if (c < 32)   { return true; }
    if (c == 127) { return true; }
    return false;
}

bool PICO_IsPunctuation(char c)
{
    if (c >= 33 && c <= 47)   { return true; }
    if (c >= 58 && c <= 64)   { return true; }
    if (c >= 91 && c <= 96)   { return true; }
    if (c >= 123 && c <= 126) { return true; }
    return false;
}

bool PICO_IsGraphic(char c)
{
    if (PICO_IsAlphaNum(c)) { return true; }
    if (PICO_IsPunctuation(c)) { return true; }
    return false;
}

bool PICO_IsLower(char c)
{
    if (c >= 'a' && c <= 'z') { return true; }
    return false;
}

bool PICO_IsUpper(char c)
{
    if (c >= 'A' && c <= 'Z') { return true; }
    return false;
}

bool PICO_IsSpace(char c)
{
    if (c == 32) { return true; }
    if (c >= 12 && c <= 15) { return true; }
    return false;
}