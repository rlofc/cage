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
#ifndef SCREEN_H_PCFZWLG4
#define SCREEN_H_PCFZWLG4

#include "color.h"

#include "begin_prefix.h"
/**
 * Change the screen background color.
 */
void screen_color(struct color background);

/**
 * Shake the virtual camera (e.g. for explosions and hits).
 * The screen will keep shaking as long as you call shake_screen().
 * To return the screen to its normal state, you should complement
 * with calling relax_screen().
 */
void shake_screen(float stopwatch);

/**
 * Undo the screen shake effect.
 */
void relax_screen(float stopwatch);

/**
 * Switch back to draw on the actual screen following
 * a call to ``draw_on_image()`` on an \ref image.
 */
void draw_on_screen(void);

/**
 * Change the screen size.
 */
void set_screen_size(int width, int height);

/**
 * Get the screen size.
 */
void get_screen_size(int* width, int* height);

/**
 * Change the real window size.
 */
void set_window_size(int width, int height);

/**
 * Get the real window size.
 */
void get_window_size(int* width, int* height);


/* cldoc:end-category() */

#include "end_prefix.h"
#endif /* end of include guard: SCREEN_H_PCFZWLG4 */
