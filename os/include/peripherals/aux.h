/** @file
 * 	@brief AUX base adresses.
 * 
 * > The  Device  has  three  Auxiliary  peripherals:  One  mini  UART  and  two  SPI  masters.  
 * > These three  peripheral  are  grouped  together  as  they  share  the same  area  in  the  peripheral register map and they share a common interrupt. 
 * > Also all three are controlled by the auxiliary enable register. 
 */

#ifndef AUX_H
#define AUX_H

#include "gpio.h"

/**
 * @brief Enum containg all the relevant addresses. The offset is again the same for all RPi's, but the base address is not.
 */
enum
{
	AUX_BASE = (GPIO_BASE + 0x15000),

	/* The offsets for reach register for the UART */
	AUX_ENABLES     = (AUX_BASE + 0x04), /**< Auxiliary Enables */
	AUX_MU_IO_REG   = (AUX_BASE + 0x40), /**< Mini UART I/O Data */
	AUX_MU_IER_REG  = (AUX_BASE + 0x44), /**< Mini UART Interrupt Enable */
	AUX_MU_IIR_REG  = (AUX_BASE + 0x48), /**< Mini UART Interrupt Identify */
	AUX_MU_LCR_REG  = (AUX_BASE + 0x4C), /**< Mini UART Line Control */
	AUX_MU_MCR_REG  = (AUX_BASE + 0x50), /**< Mini UART Model Control */
	AUX_MU_LSR_REG  = (AUX_BASE + 0x54), /**< Mini UART Line Status */
	AUX_MU_MSR_REG  = (AUX_BASE + 0x58), /**< Mini UART Modem Status */
	AUX_MU_SCRATCH  = (AUX_BASE + 0x5C), /**< Mini UART Scratch */
	AUX_MU_CNTL_REG = (AUX_BASE + 0x60), /**< Mini UART Extra Control */
	AUX_MU_STAT_REG = (AUX_BASE + 0x64), /**< Mini UART Extra Status */
	AUX_MU_BAUD_REG = (AUX_BASE + 0x68)  /**< Mini UART Baudrate */
};

#endif // AUX_H