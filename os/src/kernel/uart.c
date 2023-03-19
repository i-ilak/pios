#include <stddef.h>
#include <stdint.h>

#include "common/string.h"

#include "kernel/uart.h"
#include "kernel/mmio.h"

#include "peripherals/gpio.h"
#include "peripherals/aux.h"

void uart_init()
{
	uint32_t selector;

	selector = mmio_read(GPFSEL1);
	selector &= ~(7 << 12);
	selector |= 2 << 12;
	selector &= ~(7 << 15);
	selector |= 2 << 15;
	mmio_write(GPFSEL1, selector);

	mmio_write(GPPUD, 0x00000000);
	delay(150);

	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);

	mmio_write(GPPUDCLK0, 0x00000000);

	mmio_write(AUX_ENABLES, 1);
	mmio_write(AUX_MU_CNTL_REG, 0);
	mmio_write(AUX_MU_IER_REG, (1 << 0) | (1 << 2) | (1 << 3));
	mmio_write(AUX_MU_IIR_REG, 0xC6);
	mmio_write(AUX_MU_LCR_REG, 3);
	mmio_write(AUX_MU_MCR_REG, 0);
	mmio_write(AUX_MU_BAUD_REG, 270);
	mmio_write(AUX_MU_CNTL_REG, 3);

}

void uart_putc(unsigned char c)
{
	if(c == '\r')		// Might need to remove this on RPi.
		c = '\n';		// On macOS necessary to get line breaks...
	while (1) {
		if (mmio_read(AUX_MU_LSR_REG) & (1 << 5))
			break;
	}
	mmio_write(AUX_MU_IO_REG, c);
}


unsigned char uart_getc()
{
	while (1) {
		if (mmio_read(AUX_MU_LSR_REG) & (1 << 0))
			break;
	}
	return mmio_read(AUX_MU_IO_REG);
}

void uart_puts(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\n')
			uart_putc('\r');
		uart_putc((unsigned char)str[i]);
	}
}

char* uart_gets()
{
	static char str[MAX_INPUT_LENGTH + 1];
	int i = 0;


	memset(&str, '\0', MAX_INPUT_LENGTH + 1);

	for (i = 0; i < MAX_INPUT_LENGTH; i++) {
		str[i] = (char) uart_getc();
		uart_putc(str[i]);
		if (str[i] == '\r' || str[i] == '\n') {
			break;
		}
	}

	str[i] = '\0';

	return str;
}