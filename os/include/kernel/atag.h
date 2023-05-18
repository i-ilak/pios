// All implementation details have been taken from here
// http://www.simtec.co.uk/products/SWLINUX/files/booting_article.html#appendix_tag_reference
/**
 * @file atag.h
 * @brief ATAG parsing
 */

#include <stdint.h>

#ifndef ATAG_H
#define ATAG_H /**< ATAG_H */

/**
 * @brief Prints the ATAGs
 *
 * @param address Address of the ATAGs
 */
void print_atags(uint32_t address);

/**
 * @brief Enumearation of ATAG types
 */
enum ATAG_TYPE
{
    ATAG_NONE      = 0,          /**< Empty tag used to end the list */
    ATAG_CORE      = 0x54410001, /**< First tag used to start the list */
    ATAG_MEM       = 0x54410002, /**< Describes a physical area of memory */
    ATAG_VIDEOTEXT = 0x54410003, /**< VGA text screen information */
    ATAG_RAMDISK   = 0x54410004, /**< Describes how the ramdisk will be used */
    ATAG_INITRD2   = 0x54420005, /**< Describes where the compressed ramdisk
                                    image is placed in memory */
    ATAG_SERIAL   = 0x54410006,  /**< Board serial number */
    ATAG_REVISION = 0x54410007,  /**< Board revision */
    ATAG_VIDEOLFB = 0x54410008,  /**< Framebuffer information */
    ATAG_CMDLINE  = 0x54410009   /**< Command line */
};

/**
 * @brief ATAG header structure
 */
typedef struct atag_header
{
    uint32_t size;     /**< Size in words of this tag */
    uint32_t tag_type; /**< Tag value */
} atag_header;

/**
 * @brief ATAG_NONE structure
 *
 * This is the end of the list of ATAGs.
 */
typedef struct atag_none
{
    /* No further data in this ATAG */
} atag_none;

/**
 * @brief ATAG_CORE structure
 *
 * This is the first ATAG in the list. It is required. It contains the flags
 * and page size.
 */
typedef struct atag_core
{
    /* Optional entries below */
    uint32_t flags;      /**< Bit 0 - read only. Others unused */
    uint32_t pagesize;   /**< Page size */
    uint32_t rootdevice; /**< Root device number */
} atag_core;

/**
 * @brief ATAG_MEM structure
 *
 * This ATAG describes a physical memory region.
 */
typedef struct atag_mem
{
    uint32_t size;    /**< Size of region */
    uint32_t address; /**< Address of start of region */
} atag_mem;

/* ATAG_VIDEOTEXT defines a VGA text screen. Not relevant to a Raspberry Pi  */

/**
 * @brief ATAG_RAMDISK structure
 *
 * This ATAG describes the location of a ramdisk.
 */
typedef struct atag_ramdisk
{
    uint32_t flags; /**< Bit 0 = load, bit 1 = prompt */
    uint32_t size;  /**< Decompressed size in KB */
    uint32_t start; /**< Start block of ram disk */
} atag_ramdisk;

/**
 * @brief ATAG_INITRD2 structure
 *
 * This ATAG describes the location of an initial ramdisk.
 */
typedef struct atag_initrd2
{
    uint32_t address; /**< Address of ramdisk image */
    uint32_t size;    /**< Size of compressed(?) image */
} atag_initrd2;

/**
 * @brief ATAG_SERIAL structure
 *
 * This ATAG describes the serial number of the board.
 */
typedef struct atag_serial
{
    uint32_t low;  /**< Low 32 bits of serial number */
    uint32_t high; /**< High 32 bits of serial number */
} atag_serial;

/**
 * @brief ATAG_REVISION structure
 *
 * This ATAG describes the revision of the board.
 */
typedef struct atag_revision
{
    uint32_t revision; /**< Board revision */
} atag_revision;

/**
 * @brief ATAG_VIDEOLFB structure
 *
 * This ATAG describes the parameters for a framebuffer type display.
 */
typedef struct atag_videolfb
{
    uint16_t      width;        /**< Width of buffer */
    uint16_t      height;       /**< Height */
    uint16_t      depth;        /**< Bits/pixel */
    uint16_t      linelength;   /**< Length of a line in bytes */
    uint32_t      address;      /**< Base address of buffer */
    uint32_t      size;         /**< Size of buffer */
    unsigned char redsize;      /**< Number of red bits in each pixel */
    unsigned char redpos;       /**< Position of red bits in pixel */
    unsigned char greensize;    /**< Number of green bits in each pixel */
    unsigned char greenpos;     /**< Position of green bits in pixel */
    unsigned char bluesize;     /**< Number of blue bits in each pixel */
    unsigned char bluepos;      /**< Position of blue bits in pixel */
    unsigned char reservedsize; /**< Number of reserved bits/pixel */
    unsigned char reservedpos;  /**< Position of reserved bits */
} atag_videolfb;

/**
 * @brief ATAG_CMDLINE structure
 *
 * This ATAG describes the command line to be passed to the kernel.
 */
typedef struct atag_cmdline
{
    char *commandline; /**< Multiple characters from here */
} atag_cmdline;

/**
 * @brief ATAG structure
 *
 * This is the union of all the ATAG types.
 */
typedef struct atag_t
{
    atag_header header; /**< Standard header */
    union
    {
        atag_core     core;     /**< Core tag */
        atag_mem      mem;      /**< Memory tag */
        atag_ramdisk  ramdisk;  /**< Ramdisk tag */
        atag_initrd2  initrd2;  /**< Initrd2 tag */
        atag_serial   serial;   /**< Serial tag */
        atag_revision revision; /**< Revision tag */
        atag_videolfb videolfb; /**< Videolfb tag */
        atag_cmdline  cmdline;  /**< Cmdline tag */
    };
} atag_t; /**< ATAG structure */

#define tag_next(t)                                                           \
    ((atag_t *)((uint32_t *)(t) + (t)->header.size)) /**< Get next tag */
#define tag_size(type)                                                        \
    ((sizeof(atag_header) + sizeof(type)) >> 2) /**< Get size of tag */

/**
 * @brief Get the memory size from the ATAGs
 *
 * @param atags Pointer to the ATAGs
 */
uint32_t get_mem_size(atag_t *atags);

#endif