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
#include "internals.h"
#include "keyboard.h"
#include "SDL.h"
#include "begin_prefix.h"

static struct keyboard global_keyboard;
struct keyboard* keyboard = &global_keyboard;

int KB_SPACE = SDL_SCANCODE_SPACE;
int KB_RIGHT = SDL_SCANCODE_RIGHT;
int KB_LEFT = SDL_SCANCODE_LEFT;
int KB_UP = SDL_SCANCODE_UP;
int KB_DOWN = SDL_SCANCODE_DOWN;
int KB_ESC = SDL_SCANCODE_ESCAPE;
int KB_W = SDL_SCANCODE_W;
int KB_S = SDL_SCANCODE_S;
int KB_A = SDL_SCANCODE_A;
int KB_D = SDL_SCANCODE_D;
int KB_BACK = SDL_SCANCODE_AC_BACK;

int key_pressed(int key)
{
    if (keyboard->keys[key]) {
        if (keyboard->states[key] == 0) {
            keyboard->states[key] = 1;
            return 1;
        }
    } else {
        keyboard->states[key] = 0;
    }
    return 0;
}

int key_down(int key)
{
    return (keyboard->keys[key]);
}
#include "end_prefix.h"
