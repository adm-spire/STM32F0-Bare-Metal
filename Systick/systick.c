#include "systick.h"
#include "registers.h"

/* Global millisecond counter */
volatile uint32_t ms_ticks = 0;

/* SysTick initialization */
void systick_init(void)
{
    /* Reload value for 1 ms interrupt */
    SYST_RVR = (CPU_CLOCK / 1000) - 1;

    /* Reset counter */
    SYST_CVR = 0;

    /* Enable SysTick
       bit0 = ENABLE
       bit1 = TICKINT
       bit2 = CLKSOURCE
    */
    SYST_CSR = (1 << 0) | (1 << 1) | (1 << 2);
}

/* SysTick interrupt handler */
void SysTick_Handler(void)
{
    ms_ticks++;
}

/* Delay function using interrupt counter */
void delay_ms(uint32_t ms)
{
    uint32_t start = ms_ticks;

    while ((ms_ticks - start) < ms);
}
