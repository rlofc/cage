/* samples / collisions.c
 * ======================
 *
 */
#include "cage.h"

#define MAX_STARS 4

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

static bbox translate_bbox( bbox b, vec t )
{
    vec d = sub_vec( b.p2, b.p1 );
    b.p1 = t;
    b.p2 = add_vec( t, d );
    return b;
}

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

static void swap_vecs( vec* a, vec* b )
{
    vec tmp = *a;
    a->x = b->x; a->y = b->y; b->x = tmp.x; b->y = tmp.y;
}

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

static void destroy_sample( void* data )
{
    UNUSED( data );
}

int main( void )
{
    return game_loop( create_sample, update_sample, destroy_sample );
}
