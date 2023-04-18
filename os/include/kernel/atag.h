#include <stdint.h>

#ifndef ATAG_H
#define ATAG_H

void print_atags(uint32_t address);

#define ATAG_NONE 0
#define ATAG_CORE 0x54410001
#define ATAG_MEM 0x54410002
#define ATAG_VIDEOTEXT 0x54410003
#define ATAG_RAMDISK 0x54410004
#define ATAG_INITRD2 0x54420005
#define ATAG_SERIAL 0x54410006
#define ATAG_REVISION 0x54410007
#define ATAG_VIDEOLFB 0x54410008
#define ATAG_CMDLINE 0x54410009

typedef struct atag_header
{
    uint32_t size;     /**< Size in words of this tag */
    uint32_t tag_type; /**< Tag value */
} atag_header;

/* ATAG_NONE ends the list of ATAGs */
typedef struct atag_none
{
    /* No further data in this ATAG */
} atag_none;

/* ATAG_CORE begins the list of ATAGs */
typedef struct atag_core
{
    /* Optional entries below */
    uint32_t flags;      /**< Bit 0 - read only. Others unused */
    uint32_t pagesize;   /**< Page size */
    uint32_t rootdevice; /**< Root device number */
} atag_core;

/* ATAG_MEM defines a physical memory region */
typedef struct atag_mem
{
    uint32_t size;    /**< Size of region */
    uint32_t address; /**< Address of start of region */
} atag_mem;

/* ATAG_VIDEOTEXT defines a VGA text screen. Not relevant to a Raspberry Pi  */

/* ATAG_RAMDISK defines an initial ramdisk - floppy images only? */
typedef struct atag_ramdisk
{
    uint32_t flags; /**< Bit 0 = load, bit 1 = prompt */
    uint32_t size;  /**< Decompressed size in KB */
    uint32_t start; /**< Start block of ram disk */
} atag_ramdisk;

/* ATAG_INITRD2 - define physical location of ramdisk image */
typedef struct atag_initrd2
{
    uint32_t address; /**< Address of ramdisk image */
    uint32_t size;    /**< Size of compressed(?) image */
} atag_initrd2;

/* ATAG_SERIAL has the 64-bit serial number */
typedef struct atag_serial
{
    uint32_t low;
    uint32_t high;
} atag_serial;

/* ATAG_REVISION - board revision number */
typedef struct atag_revision
{
    uint32_t revision;
} atag_revision;

/* ATAG_VIDEOLFB - describes a framebuffer */
typedef struct atag_videolfb
{
    uint16_t width;        /**< Width of buffer */
    uint16_t height;       /**< Height */
    uint16_t depth;        /**< Bits/pixel */
    uint16_t linelength;   // ?
    uint32_t address;      /**< Base address of buffer */
    uint32_t size;         /**< Size of buffer */
    unsigned char redsize; /**< Number of red bits in each pixel */
    unsigned char redpos;  /**< Position of red bits in pixel */
    unsigned char greensize;
    unsigned char greenpos;
    unsigned char bluesize;
    unsigned char bluepos;
    unsigned char reservedsize; /**< Number of reserved bits/pixel */
    unsigned char reservedpos;  /**< Position of reserved bits */
} atag_videolfb;

/* ATAG_CMDLINE - kernel command line */
typedef struct atag_cmdline
{
    char *commandline; /**< Multiple characters from here */
} atag_cmdline;

typedef struct atag_t
{
    atag_header header;
    union
    {
        atag_core core;
        atag_mem mem;
        atag_ramdisk ramdisk;
        atag_initrd2 initrd2;
        atag_serial serial;
        atag_revision revision;
        atag_videolfb videolfb;
        atag_cmdline cmdline;
    };
} atag_t;

#define tag_next(t) ((atag_t *)((uint32_t *)(t) + (t)->header.size))
#define tag_size(type) ((sizeof(atag_header) + sizeof(type)) >> 2)

uint32_t get_mem_size(atag_t *atags);

#endif