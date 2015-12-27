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
#ifndef KEYBOARD_H_UQ7XHW8V
#define KEYBOARD_H_UQ7XHW8V

#include <stdint.h>

/**
 * Checks if a specific key has been pressed.
 * @param key Key to test
 *
 *     void update_super_cool_level(void* data, float elapsed_ms)
 *     {
 *         if (key_pressed(KB_SPACE)) {
 *             // do something once per key click
 *         }
 *      }
 *
 * This will return 0 after the first positive test, so 
 * you will get 1 only once.
 *
 * @return 1 if the key was pressed or 0 otherwise
 */
int key_pressed( uint8_t key );

/** 
 * Check if a specific key is being held down.
 * @param key Key to test
 *
 *     void update_super_cool_level(void* data, float elapsed_ms)
 *     {
 *         if (key_down(KB_RIGHT)) {
 *             // do something
 *         }
 *      }
 *
 * This will return 1 as long as the key is being held down.
 *
 * @return 1 if the key is being held down or 0 otherwise
 */
int key_down( uint8_t key );

/* Key symbols
 */
extern uint8_t KB_SPACE;
extern uint8_t KB_RIGHT;
extern uint8_t KB_LEFT;
extern uint8_t KB_UP;
extern uint8_t KB_DOWN;
extern uint8_t KB_ESC;
extern uint8_t KB_W;
extern uint8_t KB_S;
extern uint8_t KB_A;
extern uint8_t KB_D;

#endif /* end of include guard: KEYBOARD_H_UQ7XHW8V */
