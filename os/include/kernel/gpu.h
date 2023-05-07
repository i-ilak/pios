#include <stdint.h>
#ifndef GPU_H
#define GPU_H

/**
 * @file gpu.h
 * @brief Definition of GPU functions.
 */

#define CHAR_WIDTH 8  /**< Character width */
#define CHAR_HEIGHT 8 /**< Character height */

/**
 * @brief Struct to store information about the GPU.
 *
 * The GPU is responsible for drawing pixels on the screen.
 */
typedef struct pixel
{
    uint8_t red;   /**< Red component of the pixel */
    uint8_t green; /**< Green component of the pixel */
    uint8_t blue;  /**< Blue component of the pixel */
} pixel_t;         /**< Typedef for pixel */

/**
 * @brief Initializes the GPU.
 *
 * - Calls the framebuffer_init() function in a loop until it returns a
 * non-zero value. Sometimes this does not work on the first time so we loop
 * until it works...
 * - framebuffer_init() is a separate function that initializes
 * the framebuffer, which is a portion of memory used to store the pixels that
 * are displayed on the screen.
 * - Once the framebuffer is initialized, we clear the screen by looping
 * through all the pixels in the framebuffer and setting their color to black.
 * This is done by calling the write_pixel() function.
 */
void gpu_init();

/**
 * @brief Writes a pixel to the screen.
 *
 * @param x X coordinate of the pixel
 * @param y Y coordinate of the pixel
 * @param pixel Pointer to the pixel to write
 */
void write_pixel(uint32_t x, uint32_t y, const pixel_t *pixel);

/**
 * @brief Writes a character to the screen.
 *
 * @param c Character to write
 */
void gpu_putc(char c);

#endif