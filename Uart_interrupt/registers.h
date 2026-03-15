#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

#define RCC_BASE    0x40021000
#define GPIOA_BASE  0x48000000
#define USART2_BASE 0x40004400

#define RCC_AHBENR   (*((volatile uint32_t*)(RCC_BASE  + 0x14)))
#define RCC_APB1ENR  (*((volatile uint32_t*)(RCC_BASE  + 0x1C)))

#define GPIOA_MODER  (*((volatile uint32_t*)(GPIOA_BASE + 0x00)))
#define GPIOA_AFRL   (*((volatile uint32_t*)(GPIOA_BASE + 0x20)))
#define GPIOA_ODR    (*((volatile uint32_t*)(GPIOA_BASE + 0x14)))

#define USART2_CR1   (*((volatile uint32_t*)(USART2_BASE + 0x00)))
#define USART2_BRR   (*((volatile uint32_t*)(USART2_BASE + 0x0C)))
#define USART2_ISR   (*((volatile uint32_t*)(USART2_BASE + 0x1C)))
#define USART2_RDR   (*((volatile uint32_t*)(USART2_BASE + 0x24)))
#define USART2_TDR   (*((volatile uint32_t*)(USART2_BASE + 0x28)))
#define NVIC_ISER (*((volatile uint32_t*)0xE000E100))

#endif