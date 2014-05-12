/* Copyright (c) 2014 Ithai Levi @RLofC
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

#include <SDL.h>
#include "color.h"

/* The game drawing surface
 * A screen is you drawing surface for you to draw on
 * your game images, sprites and text.
 * 
 * Your <gamestate> functions will get a screen 
 * to work with inside the <toolbox> parameter.
 */
struct screen
{
    /* internal SDL renderer */
    SDL_Renderer* impl;
    /* internal SDL window */
    SDL_Window* window;
    /* Rendering X offset, for scrolling or shaking */
    float offset_x;
    /* Rendering Y offset, for scrolling or shaking */
    float offset_y;
};

/* Change screen background color
 */
void screen_color( struct screen* screen, struct color background );

/* Change screen size
 */
void screen_size( struct screen* screen, int width, int height );

/* Shake the "camera". Works well for explosions and blows.
 * The screen will keep shaking as long as you call <shake_screen>.
 * To return the screen to its normal state, you should complement
 * with calling <relax_screen>.
 */
void shake_screen( struct screen* screen, float stopwatch );

/* Undo the screen shake effect.
 */
void relax_screen( struct screen* screen, float stopwatch );

#endif /* end of include guard: SCREEN_H_PCFZWLG4 */
