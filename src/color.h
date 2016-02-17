/* Copyright (c) 2014-2016 Ithai Levi @RLofC
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */
#ifndef COLOR_H_5S0TOI9O
#define COLOR_H_5S0TOI9O

#include <stdint.h>

/* Color using the RGBA representation
 */
struct color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

/**
 * Create a new color using Red Green Blue and Alpha
 * values.
 *
 * @param red 0-255 intensity of red
 * @param green 0-255 intensity of blue
 * @param blue 0-255 intensity of green
 * @param alpha 0-255 alpha value 
 *
 * @return new color struct by value
 */
static struct color color_from_RGBA(uint8_t red,
                                    uint8_t green,
                                    uint8_t blue,
                                    uint8_t alpha)
{
    struct color c;
    c.red = red;
    c.green = green;
    c.blue = blue;
    c.alpha = alpha;
    return c;
}

/**
 * Create a new color using Red Green and Blue
 * values.
 * The color will be opaque with a default alpha
 * value of 255.
 *
 * @param red 0-255 intensity of red
 * @param green 0-255 intensity of blue
 * @param blue 0-255 intensity of green
 *
 * @return new color struct by value
 */
static struct color color_from_RGB(uint8_t red,
                                   uint8_t green,
                                   uint8_t blue)
{
    return color_from_RGBA(red, green, blue, UINT8_MAX);
}

#endif /* end of include guard: COLOR_H_5S0TOI9O */
