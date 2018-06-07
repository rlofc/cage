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
#ifndef NGX_H_F8WRBKFT
#define NGX_H_F8WRBKFT

#include "utils.h"
#include "vec.h"
#include "geometry.h"
#include "screen.h"
#include "image.h"
#include "sprite.h"
#include "keyboard.h"
#include "mouse.h"
#include "font.h"
#include "sound.h"
#include "animate.h"
#include "timeline.h"
#include "toolbox.h"
#include "easing.h"
#include "file.h"
#include "begin_prefix.h"

/**
 * This is the prototype of the create function:
 *
 *     void* create_game(void)
 *     {
 *         // Put any level, menu or other game state setup code here
 *         // and return a pointer to your level data or NULL
 *         // in case of a failure.
 *     }
 *
 * You may provide a create function to create and set up a game state.
 * A game state will usually be a struct, holding sprites, images, fonts
 * or any other assert required to run a level, a game menu or other game
 * states.
 * You pass a pointer to this function when
 * you call game_loop() or game_state().
 *
 * @return pointer to your game state data or NULL on failure
 */
typedef void* (*create_func_t)(void);

/**
 * This is the prototype of the update function:
 *
 *     void update_game(void* data, float elapsed_ms)
 *     {
 *         // Update and draw your game
 *     }
 *
 * The update function is called each time Cage wants you to update a new game
 * frame. This is the place to change your game state, play or stop sound
 * effects and draw your graphics.
 *
 * You pass a pointer to this function when you
 * call game_loop() or game_state().
 *
 * @param data the pointer you returned from the create
 * function.
 * @param elapsed_ms time passed since last update in
 * milliseconds.
 */
typedef void (*update_func_t)(void* data, float elpased_ms);

/**
 * This is the prototype of the destroy function that may be provided
 * to Cage in order to free any allocated resources once a game state
 * is being dismissed.
 *
 *     void destroy_game(void* data)
 *     {
 *         // Put any cleanup code here...
 *     }
 *
 * You may pass a pointer to this function when you
 * call game_loop() or game_state().
 *
 * @param data the pointer you returned from the create function.
 */
typedef void (*destroy_func_t)(void* data);

/**
 * This is the prototype of the setup function:
 *
 */
struct settings {
    int window_width;
    int window_height;
    int logical_width;
    int logical_height;
    bool fullscreen;
};

typedef void (*setup_func_t)(struct settings*);

/**
 * Call this function to start your game.
 *
 *     int main(void)
 *     {
 *         return game_loop(create_game, update_game, destroy_game);
 *     }
 */
int game_loop(create_func_t create,
              update_func_t update,
              destroy_func_t destroy);

int game_setup_and_loop(setup_func_t setup,
                        create_func_t create,
                        update_func_t update,
                        destroy_func_t destroy);

/**
 * Call this function to change your game state functions.
 *
 *     void update_current_level(void* data, float elapsed_ms)
 *     {
 *         // Yay.. level was just completed, let's
 *         // change the game state to the next level.
 *         game_state(create_next_level,
 *                    update_next_level,
 *                    destroy_next_level);
 *     }
 */
void game_state(create_func_t create,
                update_func_t update,
                destroy_func_t destroy);

void exit_with_error_msg(const char* msg);
void message_box(const char* title, const char* message);

const char * get_error_msgs();

#include "end_prefix.h"
#endif /* end of include guard: NGX_H_F8WRBKFT */
