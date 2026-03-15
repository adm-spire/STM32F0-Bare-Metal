#include "uart.h"
#include "registers.h"
#include <stdint.h>
#include "uart.c"
int main(void)
{
    uart_init();

    const char *msg = "UART ready!\r\n";

    for(int i = 0; msg[i]; i++)
        uart_write(msg[i]);

    while (1)
    {
        
    }
}