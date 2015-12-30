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
#ifndef MOUSE_H_UQ7XHW8V
#define MOUSE_H_UQ7XHW8V

#include <stdint.h>

static const int BUTTON_LEFT = 0x01;
static const int BUTTON_RIGHT = 0x02;
static const int BUTTON_MIDDLE = 0x04;

struct mouse {
    int buttons;
    float x;
    float y;
};

struct mouse mouse_state(void);

#endif /* end of include guard: MOUSE_H_UQ7XHW8V */
