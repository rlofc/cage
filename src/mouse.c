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
#include "mouse.h"
#include "internals.h"
#include "SDL.h"

#include "begin_prefix.h"
void update_mouse(struct mouse* mouse)
{
    int x, y, w, h;
    Uint32 ms = SDL_GetMouseState(&x, &y);
    SDL_GetWindowSize(screen->window, &w, &h);
    mouse->x_position = x / (w * 1.0);
    mouse->y_position = y / (h * 1.0);
    mouse->left_click = ms & SDL_BUTTON(SDL_BUTTON_LEFT);
    mouse->right_click = ms & SDL_BUTTON(SDL_BUTTON_RIGHT);
    mouse->middle_click = ms & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}
#include "end_prefix.h"
