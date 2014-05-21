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
#ifndef NGX_H_F8WRBKFT
#define NGX_H_F8WRBKFT

#include "screen.h"
#include "image.h"
#include "sprite.h"
#include "keyboard.h"
#include "font.h"
#include "sound.h"
#include "animate.h"
#include "timeline.h"
#include "toolbox.h"

/**
 * This is the prototype of the preparation
 * function that may be provided to Cage in order
 * to set up any required assets for the activated
 * game state.
 * You pass a pointer to this function when you
 * call game_loop() or game_state().
 *
 * @return something
 */
typedef void* ( *prepare_func_t )( void ) ;

/**
 * This is the prototype of the update function that
 * must be provided to Cage in order to update the game
 * in the game loop, for the activated state.
 *
 * You pass a pointer to this function when you
 * call game_loop() or game_state().
 *
 * @param data the pointer you returned from the preparation
 * function.
 * @param elapsed_ms time passed since last update in
 * milliseconds.
 */
typedef void ( *update_func_t )( void* data, float elpased_ms ) ;

/**
 * This is the prototype of the teardown function that may be provided
 * to Cage in order to free any allocated resources during the
 * active state run.
 *
 * You may pass a pointer to this function when you
 * call game_loop() or game_state().
 *
 * @param data the pointer you returned from the preparation function.
 */
typedef void ( *teardown_func_t )( void* data ) ;

/**
 * Call this function to start your game.
 *
 *     int main( void )
 *     {
 *         return game_loop(...);
 *     }
 */
int game_loop(
    prepare_func_t prepare,
    update_func_t update,
    teardown_func_t teardown
    );

void game_state(
    prepare_func_t prepare,
    update_func_t update,
    teardown_func_t teardown
    );

void exit_with_error_msg( const char* msg );

/* Set an error message
 */
void error_msg( const char* msg );

#endif /* end of include guard: NGX_H_F8WRBKFT */
