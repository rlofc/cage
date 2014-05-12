#ifndef TOOLBOX_H_W7RODJL2
#define TOOLBOX_H_W7RODJL2

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
    void*             data;
    /* top most game screen */
    struct screen*    screen;
    /* elapsed time since last frame ( in render-time only ) */
    uint32_t          stopwatch;
    /* last captured event ( in render-time only ) */
    struct keyboard*  keyboard;
    /* optionally set this to the next state ( in render-time only ) */
    struct gamestate* next;
};

#endif /* end of include guard: TOOLBOX_H_W7RODJL2 */