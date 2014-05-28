/* samples / image.c
 * =================
 * This short sample demonstrate how to use images in Cage
 */
#include "cage.h"

/* Create
 * ------
 *
 * We use the game state create() function to load the image resource
 * and return it as the state user data pointer.
 */
static void* create_sample( void )
{
    return create_image( "res/cage.png" ); 
}

/* Update
 * ------
 *
 * For each frame, the update state function will draw the image
 * using the image size as clipping boundries.
 * We explicitly eliminate the unused parameter warning using
 * the UNUSED macro.
 */
static void update_sample( void* data, float elapsed_ms )
{
    struct rectangle clip = { 0, 0, 144, 76 };
    draw_image( data, 4, 5, &clip ,0 );
    UNUSED( elapsed_ms );
}

/* Destroy
 * -------
 *
 * A create_image() call allocates the image and its
 * internal resources. To properly clean up our state we
 * need to use destroy_image() in the destroy state function.
 *
 */
static void destroy_sample( void* data )
{
    destroy_image( data );
}

/* Finally, the main
 * -----------------
 *
 * Finally, the game's main function delegates the
 * execution to Cage's game_loop() function together with
 * the 3 state functions we wrote.
 */
int main( void )
{
    return game_loop( create_sample, update_sample, destroy_sample );
}
