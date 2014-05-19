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
#include "internals.h"
#include "keyboard.h"
#include <SDL.h>

static struct keyboard global_keyboard;
struct keyboard* keyboard = &global_keyboard;

uint8_t KB_SPACE = SDL_SCANCODE_SPACE;
uint8_t KB_RIGHT = SDL_SCANCODE_RIGHT;
uint8_t KB_LEFT  = SDL_SCANCODE_LEFT;
uint8_t KB_UP    = SDL_SCANCODE_UP;
uint8_t KB_DOWN  = SDL_SCANCODE_DOWN;
uint8_t KB_ESC   = SDL_SCANCODE_ESCAPE;
uint8_t KB_W     = SDL_SCANCODE_W;
uint8_t KB_S     = SDL_SCANCODE_S;
uint8_t KB_A     = SDL_SCANCODE_A;
uint8_t KB_D     = SDL_SCANCODE_D;

int key_pressed( uint8_t key ) {
    if ( keyboard->keys[ key ] ) {
        if ( keyboard->states[ key ] == 0 ) {
            keyboard->states[ key ] = 1;
            return 1;
        }
    } else {
        keyboard->states[ key ] = 0;
    }
    return 0;
}

int key_down( uint8_t key ) {
    return ( keyboard->keys[ key ] );
}
