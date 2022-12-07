#pragma once
#include <Lib/Types.h>
#include <Core/Multitasking/Thread.h>

void PICO_InitScheduler();
void PICO_InitKernelThread();
void PICO_SwitchThread(bool unlock);

void PICO_LoadThread(PICO_Thread* thread);
void PICO_UnloadThread(PICO_Thread* thread);
void PICO_StartThread(PICO_Thread* thread);
void PICO_StopThread(PICO_Thread* thread);
void PICO_TerminateThread(PICO_Thread* thread);

void     PICO_ToggleScheduler(bool enabled);
uint32_t PICO_GenerateThreadID();