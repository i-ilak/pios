#include "kernel/power.h"

#include "peripherals/gpio.h"
#include "kernel/mailbox.h"
#include "kernel/mmio.h"
#include "kernel/delays.h"

enum 
{
    PM_RSTC = MMIO_BASE+0x0010001c,
    PM_RSTS = MMIO_BASE+0x00100020,
    PM_WDOG = MMIO_BASE+0x00100024,
};
#define PM_WDOG_MAGIC   0x5a000000
#define PM_RSTC_FULLRST 0x00000020


void reset()
{
    unsigned int r;
    // trigger a restart by instructing the GPU to boot from partition 0
    r = mmio_read(PM_RSTS);
    r &= ~0xfffffaaa;
    mmio_write(PM_RSTS, PM_WDOG_MAGIC | r);   // boot from partition 0
    mmio_write(PM_WDOG, PM_WDOG_MAGIC | 10);
    mmio_write(PM_RSTC, PM_WDOG_MAGIC | PM_RSTC_FULLRST);
}

void power_off()
{
    unsigned int r;

    // power off gpio pins (but not VCC pins)
    mmio_write(GPFSEL0, 0); 
    mmio_write(GPFSEL1, 0); 
    mmio_write(GPFSEL2, 0); 
    mmio_write(GPFSEL3, 0); 
    mmio_write(GPFSEL4, 0); 
    mmio_write(GPFSEL5, 0);
    mmio_write(GPPUD, 0);
    wait_cycles(150);
    mmio_write(GPPUDCLK0, 0xffffffff); 
    mmio_write(GPPUDCLK1, 0xffffffff);
    wait_cycles(150);
    mmio_write(GPPUDCLK0, 0);           // flush GPIO setup
    mmio_write(GPPUDCLK1, 0);           // flush GPIO setup

    // power off the SoC (GPU + CPU)
    r = mmio_read(PM_RSTS);
    r &= ~0xfffffaaa;
    r |= 0x555;                         // partition 63 used to indicate halt
    mmio_write(PM_RSTS, PM_WDOG_MAGIC | r);
    mmio_write(PM_WDOG, PM_WDOG_MAGIC | 10);
    mmio_write(PM_RSTC, PM_WDOG_MAGIC | PM_RSTC_FULLRST);
}
