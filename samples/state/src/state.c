/* samples / state.c
 * =================
 * This sample demonstrates how to use state functions
 * to alternate game states.
 *
 * We begin with including Cage:
 */
#include "cage.h"

/* State prototypes
 * ----------------
 *
 * The following function prototypes are the sample 
 * state functions for an **intro** state and an **outro** state.
 */
static void* prepare_intro( void );
static void  update_intro( void* data, float elapsed_ms );
static void  teardown_intro( void* data );

static void* prepare_outro( void );
static void  update_outro( void* data, float elapsed_ms );
static void  teardown_outro( void* data );

/* Intro state
 * -----------
 *
 * The first state in the game is the intro state.
 * In this state we simply ask the user to press the space key.
 * When the key gets pressed, we switch to the outro state.
 */
static void* prepare_intro( void )
{
    screen_color( color_from_RGB( 255, 255, 255 ) );
    return create_font( "res/font.png", 32, 4 );
}

static void update_intro( void* data, float elapsed_ms )
{
    draw_text( data, "Press <SPACE> to continue...", 10, 10 );
    if ( key_pressed( KB_SPACE ) ) {
        game_state( prepare_outro, update_outro, teardown_outro );
    }
    UNUSED( elapsed_ms );
}

static void teardown_intro( void* data )
{
    destroy_font( data );
}

/* Outro state
 * -----------
 *
 * The second state in the game is the outro state. Once the player press space,
 * we use game_state() to change the state using the following three
 * state functions.
 */
static void* prepare_outro( void )
{
    screen_color( color_from_RGB( 255, 255, 255 ) );
    return create_font( "res/font.png", 32, 4 );
}

static void update_outro( void* data, float elapsed_ms )
{
    draw_text( data, "Press <ESC> to exit!", 60, 40 );
    if ( key_pressed( KB_ESC ) ) {
        exit( 0 );
    }
    UNUSED( elapsed_ms );
}

static void teardown_outro( void* data )
{
    destroy_font( data );
}

/* Sample's main
 * -------------
 *
 * Finally, the game's main function delegates the
 * execution to Cage's game_loop() function together with
 * the 3 state functions of the intro state.
 */
int main( void )
{
    return game_loop( prepare_intro, update_intro, teardown_intro );
}
