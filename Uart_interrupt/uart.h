#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_write(char c);
char uart_read(void);
void USART2_IRQHandler(void);
#endif