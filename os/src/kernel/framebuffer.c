#include "kernel/framebuffer.h"

#include "kernel/mailbox.h"
#include "kernel/gpu.h"
#include "kernel/memory.h"

framebuffer_info_t fbinfo;

#if MODEL_0 || MODEL_1
typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t vwidth;
    uint32_t vheight;
    uint32_t bytes;
    uint32_t depth;
    uint32_t ignorex;
    uint32_t ignorey;
    void    *pointer;
    uint32_t size;
} fb_init_t;

fb_init_t fbinit __attribute__((aligned(16)));

int framebuffer_init()
{
    mail_message_t msg;

    fbinit.width   = 640;
    fbinit.height  = 480;
    fbinit.vwidth  = fbinit.width;
    fbinit.vheight = fbinit.height;
    fbinit.depth   = COLORDEPTH;

    msg.data = ((uint32_t)&fbinit + 0x40000000) >> 4;

    mailbox_send(msg, FRAMEBUFFER_CHANNEL);
    msg = mailbox_read(FRAMEBUFFER_CHANNEL);

    if(!msg.data)
        return -1;

    fbinfo.width        = fbinit.width;
    fbinfo.height       = fbinit.height;
    fbinfo.chars_width  = fbinfo.width / CHAR_WIDTH;
    fbinfo.chars_height = fbinfo.height / CHAR_HEIGHT;
    fbinfo.chars_x      = 0;
    fbinfo.chars_y      = 0;
    fbinfo.pitch        = fbinit.bytes;
    fbinfo.buf          = fbinit.pointer;
    fbinfo.buf_size     = fbinit.size;

    return 0;
}

#elif MODEL_2 || MODEL_3 || MODEL_4

int framebuffer_init()
{
    property_message_tag_t tags[5];

    tags[0].property_tag                       = FB_SET_PHYSICAL_DIMENSIONS;
    tags[0].value_buffer.fb_screen_size.width  = 640;
    tags[0].value_buffer.fb_screen_size.height = 480;
    tags[1].property_tag                       = FB_SET_VIRTUAL_DIMENSIONS;
    tags[1].value_buffer.fb_screen_size.width  = 640;
    tags[1].value_buffer.fb_screen_size.height = 480;
    tags[2].property_tag                       = FB_SET_BITS_PER_PIXEL;
    tags[2].value_buffer.fb_bits_per_pixel     = COLORDEPTH;
    tags[3].property_tag                       = NULL_TAG;

    // Send over the initialization
    if(send_messages(tags) != 0)
    {
        return -1;
    }

    fbinfo.width        = tags[0].value_buffer.fb_screen_size.width;
    fbinfo.height       = tags[0].value_buffer.fb_screen_size.height;
    fbinfo.chars_width  = fbinfo.width / CHAR_WIDTH;
    fbinfo.chars_height = fbinfo.height / CHAR_HEIGHT;
    fbinfo.chars_x      = 0;
    fbinfo.chars_y      = 0;
    fbinfo.pitch        = fbinfo.width * BYTES_PER_PIXEL;

    // request a framebuffer
    tags[0].property_tag                       = FB_ALLOCATE_BUFFER;
    tags[0].value_buffer.fb_screen_size.width  = 0;
    tags[0].value_buffer.fb_screen_size.height = 0;
    tags[0].value_buffer.fb_allocate_align     = 16;
    tags[1].property_tag                       = NULL_TAG;

    if(send_messages(tags) != 0)
    {
        return -1;
    }

    fbinfo.buf      = tags[0].value_buffer.fb_allocate_res.fb_addr;
    fbinfo.buf_size = tags[0].value_buffer.fb_allocate_res.fb_size;

    return 0;
}

#endif