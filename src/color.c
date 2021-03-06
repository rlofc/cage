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
#include "color.h"
#include "begin_prefix.h"
struct color color_from_RGBA(uint8_t red,
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

struct color color_from_RGB(uint8_t red,
                            uint8_t green,
                            uint8_t blue)
{
    return color_from_RGBA(red, green, blue, UINT8_MAX);
}
#include "end_prefix.h"
