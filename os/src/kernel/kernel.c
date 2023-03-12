#include <stdint.h>

#include "kernel/uart.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    uart_init();
    
    uart_puts("Hello World!\n");
    
    while(1) {
        uart_putc(uart_getc());
    }
}