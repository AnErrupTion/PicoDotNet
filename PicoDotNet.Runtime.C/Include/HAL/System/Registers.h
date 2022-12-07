#pragma once
#include <Lib/Types.h>
#include <Lib/Memory.h>

typedef struct
{
    uint16_t di, si, bp, sp, bx, dx, cx, ax;
    uint16_t gs, fs, es, ds, eflags;
} attr_pack PICO_Registers16;

static inline PICO_Registers16 mk_regs16()
{
    PICO_Registers16 regs;
    PICO_MemSet(&regs, 0, sizeof(PICO_Registers16));
    return regs;
}

extern void _regwr_cr0(uint32_t cr0);
extern void _regwr_cr3(uint32_t cr3);
extern void _regwr_cr4(uint32_t cr4);
extern uint32_t _regrd_cr0();
extern uint32_t _regrd_cr2();
extern uint32_t _regrd_cr3();
extern uint32_t _regrd_cr4();
extern uint32_t _regrd_eflags();

extern void int32(uint8_t irq, PICO_Registers16* regs);