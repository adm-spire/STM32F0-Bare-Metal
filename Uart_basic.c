#include <stdint.h>

#define RCC_BASE    0x40021000
#define GPIOA_BASE  0x48000000
#define USART2_BASE 0x40004400

// Use direct register offset macros to avoid struct padding/ordering bugs
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

void uart_init(void) {
    // Enable GPIOA clock (bit 17) and USART2 clock (bit 17 on APB1)
    RCC_AHBENR  |= (1 << 17);
    RCC_APB1ENR |= (1 << 17);

    // PA2 (TX), PA3 (RX) → Alternate Function mode (MODER = 0b10)
    GPIOA_MODER &= ~((3 << 4) | (3 << 6));
    GPIOA_MODER |=  ((2 << 4) | (2 << 6));

    // AFRL: PA2 → AF1 (bits [11:8]), PA3 → AF1 (bits [15:12])
    GPIOA_AFRL &= ~((0xF << 8) | (0xF << 12));
    GPIOA_AFRL |=  ((0x1 << 8) | (0x1 << 12));

   

    // BRR: 8Mhz default on F072 / 115200 ≈ 69
   
    USART2_BRR = 69;

    // Enable USART (UE=bit0), TX (TE=bit3), RX (RE=bit2)
    USART2_CR1 = (1 << 0) | (1 << 3) | (1 << 2);
}

void uart_write(char c) {
    while (!(USART2_ISR & (1 << 7)));
    USART2_TDR = c;
}

char uart_read(void) {
    while (!(USART2_ISR & (1 << 5)));
    return (char)USART2_RDR;
}

int main(void) {
    uart_init();

    const char *msg = "UART ready!\r\n";
    for (int i = 0; msg[i]; i++) uart_write(msg[i]);

    while (1) {
        char c = uart_read();
        uart_write(c);
    }
}