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

/* A set of state functions (callbacks ) for the game loop
 * Games will usually have different levels, menus, high score
 * displays and the likes. These are represented as different
 * gamestate entities.
 * A composition of alternating gamestates make for a complete
 * game.
 *
 *     // These are the level stat functions
 *     int prepare_level( struct toolbox* tb )
 *     {
 *         // Put any level setup and preparation code here...
 *         return 0
 *     }
 *
 *     void update_level( struct toolbox* tb )
 *     {
 *         // Update and draw your game
 *     }
 *
 *     void teardown_level( struct toolbox* tb )
 *     {
 *         // Put any cleanup code here...
 *     }
 *
 *     // These are the game menu state functions
 *     int prepare_menu( struct toolbox* tb )
 *     {
 *         // Put any menu setup and preparation code here...
 *         return 0
 *     }
 *
 *     void update_menu( struct toolbox* tb )
 *     {
 *         // Handle the menu behavior.
 *         // When ready, switch to the level game state:
 *         tb->next->prepare  = prepare_level;
 *         tb->next->update   = update_level;
 *         tb->next->teardown = teardown_level;
 *     }
 *
 *     void teardown_menu( struct toolbox* tb )
 *     {
 *         // Put any cleamup code here...
 *     }
 *
 *     // This is your game!
 *     int main(int argc, char ** argv)
 *     {
 *         // Set up the initial game state
 *         struct gamestate menu = { prepare_menu, update_menu, teardown_menu };
 *         return gameloop( &menu );
 *     }
 */
struct gamestate
{
    /* callback to setup your state before rendering */
    int ( *prepare )( struct toolbox* c );
    /* callback for each frame */
    void ( *frame )( struct toolbox* c );
    /* callback to tear down your state */
    void ( *teardown )( struct toolbox* c );
};

/* game loop
 */
int gameloop(struct gamestate* state);

#endif /* end of include guard: NGX_H_F8WRBKFT */
