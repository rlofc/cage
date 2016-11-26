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

#include "types.h"

#include "begin_prefix.h"
struct mouse {
    /** Set to true if left click was detected */
    bool left_click;
    /** Set to true if right click was detected */
    bool right_click;
    /** Set to true if middle click was detected */
    bool middle_click;
    /** Normalized value. 0.0 is the left edge of the screen. 1.0 is the
     * right edge of the screen. */
    float x_position;
    /** Normalized value. 0.0 is the top edge of the screen. 1.0 is the
     * bottom edge of the screen. */
    float y_position;
};

/**
 * Query the current mouse state and update the passed mouse struct.
 */
void update_mouse(struct mouse* mouse);

#include "end_prefix.h"
#endif /* end of include guard: MOUSE_H_UQ7XHW8V */
