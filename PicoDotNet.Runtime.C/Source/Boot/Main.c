#include <Core/Common.h>

void main(PICO_Multiboot* mbp)
{
    PICO_KernelBoot(mbp);
    PICO_ToggleScheduler(true);
    PICO_KernelRun();
}