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

#include "begin_prefix.h"
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
int key_pressed( int key );

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
int key_down( int key );

/* Key symbols
 */
extern int KB_SPACE;
extern int KB_RIGHT;
extern int KB_LEFT;
extern int KB_UP;
extern int KB_DOWN;
extern int KB_ESC;
extern int KB_W;
extern int KB_S;
extern int KB_A;
extern int KB_D;
extern int KB_BACK;

#include "end_prefix.h"
#endif /* end of include guard: KEYBOARD_H_UQ7XHW8V */
