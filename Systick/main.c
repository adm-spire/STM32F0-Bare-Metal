#include "systick.h"
#include "registers.h"
#define RCC_AHBENR   (*((volatile uint32_t*)0x40021014))

#define GPIOA_MODER  (*((volatile uint32_t*)0x48000000))
#define GPIOA_ODR    (*((volatile uint32_t*)0x48000014))
int main(void)
{
    /* Enable GPIOA clock */
    RCC_AHBENR |= (1 << 17);

    /* Set PA5 as output */
    GPIOA_MODER &= ~(3 << 10);   // clear bits
    GPIOA_MODER |=  (1 << 10);   // set output mode

    systick_init();

    while (1)
    {
        /* Toggle LED */
        GPIOA_ODR ^= (1 << 5);

        delay_ms(1000);
    }
}