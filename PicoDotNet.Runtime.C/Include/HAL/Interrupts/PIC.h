#pragma once
#include <Lib/Types.h>
#include <HAL/System/Ports.h>

static inline void PICO_RemapPIC()
{
    PICO_PortOutb(0x20, 0x11);
    PICO_PortOutb(0xA0, 0x11);
    PICO_PortOutb(0x21, 0x20);
    PICO_PortOutb(0xA1, 0x28);
    PICO_PortOutb(0x21, 0x04);
    PICO_PortOutb(0xA1, 0x02);
    PICO_PortOutb(0x21, 0x01);
    PICO_PortOutb(0xA1, 0x01);
    PICO_PortOutb(0x21, 0x0);
    PICO_PortOutb(0xA1, 0x0);
}