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

#define MAILBOX_OFFSET 0xB880

#define MAILBOX_BASE MMIO_BASE + MAILBOX_OFFSET
#define MAIL0_READ (((mail_message_t *)(0x00 + MAILBOX_BASE)))
#define MAIL0_STATUS (((mail_status_t *)(0x18 + MAILBOX_BASE)))
#define MAIL0_WRITE (((mail_message_t *)(0x20 + MAILBOX_BASE)))

#define PROPERTY_CHANNEL 8
#define FRAMEBUFFER_CHANNEL 1

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
    uint8_t channel : 4;
    uint32_t data : 28;
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
    uint32_t reserved : 30;
    uint8_t empty : 1;
    uint8_t full : 1;
} mail_status_t;

mail_message_t mailbox_read(int channel);
void mailbox_send(mail_message_t msg, int channel);

/**
 * @brief A tag that can be sent to the mailbox
 *
 * A property message can either be a request, or a response, and a response
 * can be successfull or an error.
 */
typedef enum
{
    REQUEST = 0x00000000,
    RESPONSE_SUCCESS = 0x80000000,
    RESPONSE_ERROR = 0x80000001
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
    uint32_t size; /**< Size includes the size itself */
    buffer_req_res_code_t req_res_code;
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
    NULL_TAG = 0,
    FB_ALLOCATE_BUFFER = 0x00040001,
    FB_RELESE_BUFFER = 0x00048001,
    FB_GET_PHYSICAL_DIMENSIONS = 0x00040003,
    FB_SET_PHYSICAL_DIMENSIONS = 0x00048003,
    FB_GET_VIRTUAL_DIMENSIONS = 0x00040004,
    FB_SET_VIRTUAL_DIMENSIONS = 0x00048004,
    FB_GET_BITS_PER_PIXEL = 0x00040005,
    FB_SET_BITS_PER_PIXEL = 0x00048005,
    FB_GET_BYTES_PER_ROW = 0x00040008
} property_tag_t;

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
    void *fb_addr;
    uint32_t fb_size;
} fb_allocate_res_t;

/**
 * @brief Response value buffer for FB_ALLOCATE_BUFFER
 *
 * The response value buffer for FB_ALLOCATE_BUFFER is the address and size
 * of the framebuffer.
 */
typedef struct
{
    uint32_t width;
    uint32_t height;
} fb_screen_size_t;

/**
 * @brief Union of all possible value buffers
 *
 * Different types of data that can be sent with the tags, depending on the
 * specific tag being used.
 */
typedef union
{
    uint32_t fb_allocate_align;
    fb_allocate_res_t fb_allocate_res;
    fb_screen_size_t fb_screen_size;
    uint32_t fb_bits_per_pixel;
    uint32_t fb_bytes_per_row;
} value_buffer_t;

/**
 * @brief A message that can be sent to the mailbox.
 *
 * A tag is a property tag, and a value buffer. The value buffer is the data
 * that is sent with the tag.
 */
typedef struct
{
    property_tag_t proptag;
    value_buffer_t value_buffer;
} property_message_tag_t;

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