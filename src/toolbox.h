#ifndef TOOLBOX_H_W7RODJL2
#define TOOLBOX_H_W7RODJL2

#include <stdint.h>


#include "begin_prefix.h"
struct gamestate;

/* Game toolbox passed to state callbacks
 * The toolbox contains a set of utilities
 * to help the state functions work.
 * Additionally, you can store a custom
 * data structure inside the <data>
 * field:
 *
 *     struct my_data {
 *         struct sprite* my_sprite;
 *     };
 *
 *     int prepare_my_level( struct toolbox* toolbox )
 *     {
 *        toolbox->data = malloc( sizeof( struct my_data ) );
 *     }
 *
 *     int teardown_my_level( struct toolbox* toolbox )
 *     {
 *        free( toolbox->data );
 *     }
 *
 */
struct toolbox {
    /* user data; set as you like */
    void* data;
    /* elapsed time since last frame ( in render-time only ) */
    float stopwatch;
    /* optionally set this to the next state ( in render-time only ) */
    struct gamestate* state;
    struct gamestate* next_state;
};

#include "end_prefix.h"
#endif /* end of include guard: TOOLBOX_H_W7RODJL2 */
