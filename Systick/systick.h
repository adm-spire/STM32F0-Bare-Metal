#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

/* global millisecond counter */
extern volatile uint32_t ms_ticks;

void systick_init(void);
void delay_ms(uint32_t ms);

#endif