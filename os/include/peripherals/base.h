/**
 * @file base.h
 * @brief Memory-Mapped-IO base address.
 * 
 * The offset from the MMIO-base-address is the same for all RPi's, but the base-address itself depends on the model.
 * By setting a compiler directive we can choose for which model we compile the corresponding kernel.
 */

#ifndef BASE_H
#define BASE_H

/**
 * From the datasheet of the BCM2835 (RaspberryPi 0 and 1)
 *
 * > Peripherals  (at  physical  address  0x20000000  on)  are  mapped  into the  kernel  virtual  address space  starting  at  address  0xF2000000.  
 * > Thus  a  peripheral  advertised  here  at  bus  address 0x7Ennnnnn is available in the ARM kenel at virtual address 0xF2nnnnnn.
 * 
 */
enum {
#if MODEL_0 || MODEL_1
	/** For raspi 0,1 */
	MMIO_BASE = 0x20000000
#elif MODEL_2 || MODEL_3
	/** For raspi 2,3 */
	MMIO_BASE = 0x3F000000
#elif MODEL_4
	/** For raspi 4 */
	MMIO_BASE = 0xFE000000
#endif
};

#endif // BASE_H