#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

/* SysTick Registers (Cortex-M System Control Space) */
#define SYST_CSR  (*((volatile uint32_t*)0xE000E010))
#define SYST_RVR  (*((volatile uint32_t*)0xE000E014))
#define SYST_CVR  (*((volatile uint32_t*)0xE000E018))

#define CPU_CLOCK 8000000

#endif