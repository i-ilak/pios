#include <stdint.h>
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

/**
 * @file framebuffer.h
 * @brief Provides functions to initialize the framebuffer and draw pixels.
 */

#define COLORDEPTH 24                  /**< Number of bits per pixel */
#define BYTES_PER_PIXEL COLORDEPTH / 8 /**< Number of bytes per pixel */

/**
 * @brief Struct to store information about the framebuffer.
 *
 * The framebuffer is a memory region that stores the pixels of the screen. The
 * GPU writes the pixels to the framebuffer and the pixels are then displayed
 * on the screen.
 *
 * The framebuffer is a contiguous memory region. The pixels are stored in
 * raster order, with the first pixel being the top left pixel, and the last
 * pixel being the bottom right pixel.
 */
typedef struct framebuffer_info
{
    uint32_t width;        /**< Width of the framebuffer in pixels */
    uint32_t height;       /**< Height of the framebuffer in pixels */
    uint32_t pitch;        /**< Number of bytes per row */
    void *buf;             /**< Pointer to the framebuffer */
    uint32_t buf_size;     /**< Size of the framebuffer in bytes */
    uint32_t chars_width;  /**< Width of the framebuffer in characters */
    uint32_t chars_height; /**< Height of the framebuffer in characters */
    uint32_t chars_x;      /**< X position of the cursor in characters */
    uint32_t chars_y;      /**< Y position of the cursor in characters */
} framebuffer_info_t;      /**< Typedef for framebuffer_info */

extern framebuffer_info_t
    fbinfo; /**< Global variable to store framebuffer information */

int framebuffer_init(); /**< Initializes the framebuffer */

#endif // FRAMEBUFFER_H