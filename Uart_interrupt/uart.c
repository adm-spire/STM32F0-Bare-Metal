#include "uart.h"
#include "registers.h"

void uart_init(void)
{
    RCC_AHBENR  |= (1 << 17);
    RCC_APB1ENR |= (1 << 17);

    GPIOA_MODER &= ~((3 << 4) | (3 << 6));
    GPIOA_MODER |=  ((2 << 4) | (2 << 6));

    GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12));
    GPIOA_AFRL |=  ((0x1 << 8) | (0x1 << 12));

    USART2_BRR = 69;

    USART2_CR1 = (1 << 0) | (1 << 3) | (1 << 2) | (1 << 5);    // RXNEIE (RX interrupt enable)
    NVIC_ISER |= (1 << 28); // Enable USART2 interrupt in NVIC
    
}

void uart_write(char c)
{
    while (!(USART2_ISR & (1 << 7)));
    USART2_TDR = c;
}

char uart_read(void)
{
    while (!(USART2_ISR & (1 << 5)));
    return (char)USART2_RDR;
}

void USART2_IRQHandler(void)
{
    if (USART2_ISR & (1 << 5))   // RXNE flag
    {
        char c = (char)USART2_RDR;

        uart_write(c);           // echo back
    }
}