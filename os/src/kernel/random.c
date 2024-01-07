#include "kernel/random.h"
#include "peripherals/base.h"
#include "kernel/mmio.h"
#include "common/stdlib.h"

enum
{
    RNG_CTRL        = (MMIO_BASE + 0x00104000),
    RNG_STATUS      = (MMIO_BASE + 0x00104004),
    RNG_DATA        = (MMIO_BASE + 0x00104008),
    RNG_INT_MASK    = (MMIO_BASE + 0x00104010),
};

void rand_init()
{
    mmio_write(RNG_STATUS, 0x40000);
    // mask interrupt
    uint32_t mask = mmio_read(RNG_INT_MASK);
    mmio_write(RNG_INT_MASK, mask|=1);
    // enable
    uint32_t ctrl = mmio_read(RNG_CTRL);
    mmio_write(RNG_CTRL, ctrl|=1);
}

unsigned int rand(unsigned int min, unsigned int max)
{
    // may need to wait for entropy: bits 24-31 store how many words are
    // available for reading; require at least one
    while(!(mmio_read(RNG_STATUS)>>24)) asm volatile("nop");
    
    divmod_t rand = divmod(mmio_read(RNG_DATA), (max-min));
    return rand.mod + min;
}
