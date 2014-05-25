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
 * This is the prototype of the update function:
 *
 *     void* prepare_game( void )
 *     {
 *         // Put any level setup and preparation code here
 *         // and return a pointer to your level data or NULL
 *         // in case of a failure.
 *     }
 *
 * You may provide a preparation function to set up any required assets for the
 * activated game state.  The preparation function is a good place to load
 * resources or initialize your data.  You pass a pointer to this function when
 * you call game_loop() or game_state().
 *
 * @return pointer to your game state data or NULL on failure
 */
typedef void* ( *prepare_func_t )( void ) ;

/**
 * This is the prototype of the update function:
 *
 *     void update_gane( void* data, float elapsed_ms )
 *     {
 *         // Update and draw your game
 *     }
 *
 * The update function is called each time Cage wants you to create a new game
 * frame. This is the place to update your game state, play or stop sound
 * effects and draw your graphics.  
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
 * active state run:
 *
 *     void teardown_gane( void* data )
 *     {
 *         // Put any cleanup code here...
 *     }
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
 *         return gameloop( prepare_game, update_game, teardown_game );
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


#endif /* end of include guard: NGX_H_F8WRBKFT */
