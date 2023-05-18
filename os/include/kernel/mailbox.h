#include <stdint.h>
#include "peripherals/base.h"
#ifndef MAILBOX_H
#define MAILBOX_H

/**
 * @file mailbox.h
 * @brief Mailbox interface
 *
 * The mailbox is a way to communicate with the GPU. It is a FIFO queue of
 * messages. The GPU can send messages to the CPU, and the CPU can send
 * messages to the GPU. The CPU can also send messages to itself.
 *
 */

#define MAILBOX_OFFSET 0xB880 /**< The offset of the mailbox registers */

#define MAILBOX_BASE                                                          \
    MMIO_BASE                                                                 \
    +MAILBOX_OFFSET /**< The base address of the mailbox registers */
#define MAIL0_READ                                                            \
    (((mail_message_t *)(0x00 + MAILBOX_BASE))) /**< Read from                \
                                                    mailbox 0 */
#define MAIL0_STATUS                                                          \
    (((mail_status_t *)(0x18 + MAILBOX_BASE))) /**< Status of                 \
                                                   mailbox 0 */
#define MAIL0_WRITE                                                           \
    (((mail_message_t *)(0x20 + MAILBOX_BASE))) /**< Write to                 \
                                                    mailbox 0 */

#define PROPERTY_CHANNEL 8    /**< Channel 8 is the property channel */
#define FRAMEBUFFER_CHANNEL 1 /**< Channel 1 is the framebuffer channel */

/**
 * @brief A message that can be sent to the mailbox
 *
 * The mailbox has 16 channels, and each channel has a 32 bit buffer
 * associated with it. The buffer is used to store the data for the message
 * that is being sent.
 *
 * A message is 32 bits, with the first 4 bits being the channel, and the
 * remaining 28 bits being the data to be sent. The channel is used to route
 * the message to the correct buffer, and the data is the actual data that is
 * being sent. The data is not interpreted by the mailbox or the GPU, it is
 * just passed through. The data is interpreted by the driver that is recieving
 * the message. The driver will know what to do with the data, and will know
 * how to interpret it.
 */
typedef struct
{
    uint8_t  channel : 4; /**< The channel to send the message to */
    uint32_t data : 28;   /**< The data to send */
} mail_message_t;

/**
 * @brief The status of the mailbox
 *
 * The mailbox has a status register that can be used to check if there is
 * mail to read, or if there is space to write mail to. The status register
 * is 32 bits, with the first 30 bits being reserved, and the last 2 bits
 * being the full and empty flags.
 *
 * The full and empty flags are mutually exclusive, so if the full flag is
 * set, then the empty flag will not be set, and vice versa.
 *
 * The reserved bits are reserved for future use, and should be set to 0. If
 * they are not set to 0, then the behavior is undefined.
 *
 * What goes into the reserved bits is not specified, so it is not possible
 * to check if the mailbox is empty or full by checking if the reserved bits
 * are 0 or not. The empty and full flags must be used instead.
 */
typedef struct
{
    uint32_t reserved : 30; /**< Reserved for future use */
    uint8_t  empty : 1;     /**< The empty flag */
    uint8_t  full : 1;      /**< The full flag */
} mail_status_t;            /**< The status of the mailbox */

/**
 * @brief Read from the mailbox
 *
 * This function will block until there is mail to read from the mailbox.
 *
 * @param channel The channel to read from
 * @return The message that was read from the mailbox
 */
mail_message_t mailbox_read(int channel);

/**
 * @brief Write to the mailbox
 *
 * This function will block until there is space to write to the mailbox.
 *
 * @param msg The message to write to the mailbox
 * @param channel The channel to write to
 */
void mailbox_send(mail_message_t msg, int channel);

/**
 * @brief A tag that can be sent to the mailbox
 *
 * A property message can either be a request, or a response, and a response
 * can be successfull or an error.
 */
typedef enum
{
    REQUEST          = 0x00000000, /**< Request code */
    RESPONSE_SUCCESS = 0x80000000, /**< Response success code */
    RESPONSE_ERROR   = 0x80000001  /**< Response error code */
} buffer_req_res_code_t;

/**
 * @brief A buffer that holds many property messages
 *
 * The last tag must be a 4 byte zero, and then padding to make the whole thing
 * 4 byte aligned. The size field is the size of the whole buffer, including
 * the size field itself.
 */
typedef struct
{
    uint32_t              size;         /**< Size includes the size itself */
    buffer_req_res_code_t req_res_code; /**< Request or response code */
    uint32_t tags[1]; /**< The tags start here. Will use overrun to make large
                         enough */
} property_message_buffer_t;

/**
 * @brief A tag that can be sent to the mailbox
 *
 * A message is identified by a tag. These are some of the possible tags. The
 * full list can be found in the BCM2835 ARM Peripherals manual, section 6.1
 * (page 102)
 * https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf
 *
 * For general information about the mailbox, see the following link:
 * https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
 */
typedef enum
{
    NULL_TAG                   = 0,          /**< The end of the tag list */
    FB_ALLOCATE_BUFFER         = 0x00040001, /**< Allocate a framebuffer */
    FB_RELESE_BUFFER           = 0x00048001, /**< Release a framebuffer */
    FB_GET_PHYSICAL_DIMENSIONS = 0x00040003, /**< Get the physical dimensions
                                                of the framebuffer */
    FB_SET_PHYSICAL_DIMENSIONS = 0x00048003, /**< Set the physical dimensions
                                                of the framebuffer */
    FB_GET_VIRTUAL_DIMENSIONS = 0x00040004,  /**< Get the virtual dimensions of
                                                 the framebuffer */
    FB_SET_VIRTUAL_DIMENSIONS = 0x00048004,  /**< Set the virtual dimensions of
                                                 the framebuffer */
    FB_GET_BITS_PER_PIXEL = 0x00040005, /**< Get the number of bits per pixel
                                            of the framebuffer */
    FB_SET_BITS_PER_PIXEL = 0x00048005, /**< Set the number of bits per pixel
                                            of the framebuffer */
    FB_GET_BYTES_PER_ROW = 0x00040008   /**< Get the number of bytes per row of
                                              the framebuffer */
} property_tag_t;                       /**< The tag */

/**
 * For each possible tag, we create a struct corresponding to the request value
 * buffer, and the response value buffer
 */

/**
 * @brief Request value buffer for FB_ALLOCATE_BUFFER
 *
 * The request value buffer for FB_ALLOCATE_BUFFER is just the alignment
 * that the framebuffer should be aligned to. The alignment must be
 * a power of 2 and at least 16 bytes.
 */
typedef struct
{
    void    *fb_addr; /**< The address of the framebuffer */
    uint32_t fb_size; /**< The size of the framebuffer */
} fb_allocate_res_t;  /**< The response value buffer for FB_ALLOCATE_BUFFER */

/**
 * @brief Response value buffer for FB_ALLOCATE_BUFFER
 *
 * The response value buffer for FB_ALLOCATE_BUFFER is the address and size
 * of the framebuffer.
 */
typedef struct
{
    uint32_t width;  /**< The width of the screen */
    uint32_t height; /**< The height of the screen */
} fb_screen_size_t;  /**< The response value buffer for
                        FB_GET_PHYSICAL_DIMENSIONS */

/**
 * @brief Union of all possible value buffers
 *
 * Different types of data that can be sent with the tags, depending on the
 * specific tag being used.
 */
typedef union
{
    uint32_t fb_allocate_align;        /**< The alignment of the framebuffer */
    fb_allocate_res_t fb_allocate_res; /**< The response value buffer for
                                           FB_ALLOCATE_BUFFER */
    fb_screen_size_t fb_screen_size;   /**< The response value buffer for
                                            FB_GET_PHYSICAL_DIMENSIONS */
    uint32_t fb_bits_per_pixel;        /**< The number of bits per pixel */
    uint32_t fb_bytes_per_row;         /**< The number of bytes per row */
} value_buffer_t;                      /**< The value buffer */

/**
 * @brief A message that can be sent to the mailbox.
 *
 * A tag is a property tag, and a value buffer. The value buffer is the data
 * that is sent with the tag.
 */
typedef struct
{
    property_tag_t property_tag; /**< The property tag */
    value_buffer_t value_buffer; /**< The value buffer */
} property_message_tag_t;        /**< The property message tag */

/**
 * @brief Send a message to the mailbox
 *
 * @param tags The tags to send.
 * @return 0 on success, -1 on failure
 *
 *
 * Given an array of tags, will send all of the tags given, and will populate
 * that array with the responses. The last tag must be a 4 byte zero, and then
 * padding to make the whole thing 4 byte aligned. The size field is the size
 * of the whole buffer, including the size field itself.
 */
int send_messages(property_message_tag_t *tags);

#endif // MAILBOX_H