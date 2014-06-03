/* samples / collisions.c
 * ======================
 *
 * This sample demonstrates a method for pixel-perfect
 * collision detection. While this may not be the most
 * optimized way to do this, it is clear and effective.
 *
 */
#include "cage.h"

/* Sample setup
 * ------------
 *
 * For this demo we will use a star image.
 * Each star will have its own position, 
 * motion vector and bounding box.
 */
#define MAX_STARS 12

struct star
{
    vec star_pos;
    vec star_vec;
    bbox star_bbox;
};

struct state
{
    struct image* star_img;
    struct star stars[MAX_STARS];
};

/*
 * Web begin by creating, positioning
 * and propelling the stars.
 */
static void* create_sample( void )
{
    int i;
    struct state* state = malloc( sizeof( struct state ) );
    state->star_img = create_image( "res/star.png" );
    for ( i = 0; i < MAX_STARS; i++ ) {
        state->stars[i].star_pos = xy_vec( i * 16, i * 16 );
        state->stars[i].star_vec = xy_vec( 2 - rand() % 4, 2 - rand() % 4 );
        state->stars[i].star_bbox.p1 = state->stars[i].star_pos;
        state->stars[i].star_bbox.p2 =
            add_vec( state->stars[i].star_pos, xy_vec( 16, 16 ) );
    }
    return state;
}

/* Moving the stars
 * ----------------
 *
 * update_star() moves a star on the screen using the star
 * motion vector and tests for screen bounds collisions.
 */
static void update_star( struct star* star, float elapsed_ms )
{
    bbox screen_bbox = {{0, 0}, {192, 108}};
    vec speed = star->star_vec;
    elapsed_ms;
    star->star_pos = add_vec( star->star_pos, speed );
    star->star_bbox = translate_bbox( star->star_bbox, star->star_pos );
    if ( bbox_in_bbox( star->star_bbox, screen_bbox ) == 0 ) {
        if ( star->star_bbox.p1.x < screen_bbox.p1.x ) star->star_vec.x = 1;
        if ( star->star_bbox.p1.y < screen_bbox.p1.y ) star->star_vec.y = 1;
        if ( star->star_bbox.p2.x > screen_bbox.p2.x ) star->star_vec.x = -1;
        if ( star->star_bbox.p2.y > screen_bbox.p2.y ) star->star_vec.y = -1;
    }
}

/* Collision detection
 * -------------------
 *
 * When updating a frame, we traverse the star pairs
 * graph and test for a bounding box intersection.
 * To detect pixel-level collisions, we us pixels_collide()
 * using the portion of intersection as a test area.
 * If we detect a collision, we swap the star pair
 * motion vectors to create a deflection effect.
 * 
 * When done, we update and draw the stars.
 */
static void update_sample( void* data, float elapsed_ms )
{
    struct state* state = data;
    int visited[MAX_STARS][MAX_STARS] = {{0}};
    int i, j;
    for ( i = 0; i < MAX_STARS; i++ ) {
        for ( j = 0; j < MAX_STARS; j++ ) {
            if ( i != j && visited[i][j] == 0 && visited[j][i] == 0 ) {
                struct star* a = &state->stars[i];
                struct star* b = &state->stars[j];
                bbox sub;
                if ( bbox_intersect( a->star_bbox, b->star_bbox, &sub ) ) {
                    struct rectangle r1, r2;
                    r1 = rect_from_sub_bbox( a->star_bbox, sub );
                    r2 = rect_from_sub_bbox( b->star_bbox, sub );

                    if ( pixels_collide( state->star_img, &r1, state->star_img,
                                         &r2 ) )
                        swap_vecs( &a->star_vec, &b->star_vec );
                }
                visited[i][j] = 1;
            }
        }
    }

    screen_color( color_from_RGB( 10, 20, 50 ) );
    for ( i = 0; i < MAX_STARS; i++ ) {
        update_star( &state->stars[i], elapsed_ms );
        draw_image( state->star_img, VEC_XY( state->stars[i].star_pos ), NULL,
                    0 );
    }
}

/* Cleanup
 * -------
 *
 * Clean up is simple enough. Just destroy the star
 * image and free the state structure memory.
 */
static void destroy_sample( void* data )
{
    struct state* state = data;
    destroy_image( data->star_img );
    free( data );
}

/* Main
 * ----
 *
 * The usual game_loop call, using the usual state
 * functions.
 */
int main( void )
{
    return game_loop( create_sample, update_sample, destroy_sample );
}
