/* ## Wizard */
#include "cage.h"
#include <string.h>

/* This incomplete sample shows how **Cage** may be used
 * to write a small game.
 * We begin with defining a few constants that
 * we'll need to use later on.
 */
static const int BASE_Y = 57;
static float NO_SPEED     = 0;
static float PREP_SPEED   = 0.25f;
static float STOP_SPEED   = 0.1f;
static float NORMAL_SPEED = 0.5f;

/* We use a string to represent the level map.
 * Each character represents a 16x16 pixels tile.
 * Whitespaces are empty tiles, dashes are grass tiles
 * and dots are earth tiles.
 * Our game's logical size is 196x108 pixels, so we have
 * room for 12x7 tiles of 16x16 pixels.
 */
static const char* LEVEL = "            " 
                           "            "
                           "            "
                           "            "
                           "            "
                           "------------"
                           "............";

/* This struct holds the wizard sprite, animations
 * and other state fields that should be kept and
 * managed throughout a game level.
 */
struct wizard {
    struct sprite*     sprite;
    struct animation*  walk;
    struct animation*  stand;
    struct animation*  spell;
    struct point       pos;
    float              speed;
};

/* In this example, the wizard character is created
 * and destroyed within the scope of a single level.
 *
 * Creating a wizard means reading the sprite image
 * and creating a sprite with the proper frame dimentions
 * as well as creating the set of animations required
 * to animate the wizard. 
 *
 * Animations can be re-used for any number of 
 * sprites, however in this example the animations
 * are an integral part of the wizard data structure.
 *
 * Pay attention to the way we defined the walking
 * loop cycle. First, we associated the walking speed
 * by using the user data parameter in add_frame.
 * Then, we set the loop sequence starting frame to
 * the second frame ( index=1 ). This way, the 
 * first frame ( index=0 ) of the walking animation is
 * used as a transition frame from the standing pose.
 *
 * We finalize with setting the default pose and the
 * initial position.
 *
 */
static struct wizard* create_wizard( struct screen* screen )
{
    struct wizard* wizard = calloc(1, sizeof( struct wizard ) );

    wizard->sprite = create_sprite( create_image( "res/wizard.png", screen ) , 32, 32);

    wizard->walk = create_animation();
        add_frame(wizard->walk, 4, 200, &PREP_SPEED);
        add_frame(wizard->walk, 0, 200, &NORMAL_SPEED); /* <------+ */
        add_frame(wizard->walk, 1, 200, &NORMAL_SPEED); /*        | */
        add_frame(wizard->walk, 2, 200, &NORMAL_SPEED); /*        | */
        add_frame(wizard->walk, 3, 200, &NORMAL_SPEED); /* <--+   | */
        add_frame(wizard->walk, 4, 200, &STOP_SPEED);   /*    |   | */
    wizard->walk->loop_from = 1; /* --------------------------|---+ */
    wizard->walk->loop_to   = 4; /* --------------------------+     */

    wizard->stand = create_animation();
        add_frame(wizard->stand, 5, 100, &NO_SPEED); /* <---+ */
    wizard->stand->mode = FREEZE_LAST_FRAME; /* ------------+ */

    wizard->spell = create_animation();
        add_frame(wizard->spell, 5, 200, &NO_SPEED);
        add_frame(wizard->spell, 6, 200, &NO_SPEED);
        add_frame(wizard->spell, 7, 100, &NO_SPEED); /* <--+ */
        add_frame(wizard->spell, 6, 200, &NO_SPEED); /*    | */ 
    wizard->spell->loop_from = 2; /* ----------------------+ */
    wizard->spell->loop_to   = 2; /* ----------------------+ */

    play_animation( wizard->sprite, wizard->stand );

    wizard->pos.x = 0;
    wizard->pos.y = BASE_Y;

    return wizard;
}

/* Destroying a wizard means destroying each and every 
 * created resource in the create_wizard function,
 * otherwise, we will have a leak.
 */
static void destroy_wizard( struct wizard* wizard )
{
    destroy_animation( wizard->walk );
    destroy_animation( wizard->spell );
    destroy_animation( wizard->stand );
    destroy_image( wizard->sprite->image );
    destroy_sprite( wizard->sprite );
    free( wizard );
}

/* The wizard is controlled using the keyboard (for now)
 * and this function sets the animations and motion
 * based on the player key presses and the animation user data
 * as it was set up in the create_wizard function.
 */
static void animate_wizard( struct wizard* wizard, struct toolbox* t )
{
    const void* px;
    /* set wizard animation according to keyboard */
    struct animation* active_anim;
    active_anim = key_down( t->keyboard, KB_SPACE ) ? wizard->spell :
                  key_down( t->keyboard, KB_RIGHT ) ? wizard->walk :
                                                      wizard->stand;

    play_animation( wizard->sprite, active_anim );

    /* animate the wizard */
    if (( px = animate_sprite( wizard->sprite, t->stopwatch ) ) != NULL) {
        wizard->speed = *((const float*)px);
    }
    wizard->pos.x += wizard->speed;
}

/* The level data stores the wizard 
 * and level tiles and is being stored inside
 * the toolbox->data of the game state functions.
 */
struct level_data {
    struct wizard* wizard;
    struct image* grass_tile;
    struct image* earth_tile;
};

static struct level_data* create_level_data( struct screen* screen )
{
    struct level_data* ld = calloc( 1, sizeof ( struct level_data ) );
    ld->wizard = create_wizard( screen );
    ld->grass_tile = create_image( "res/grass_tile.png", screen );
    ld->earth_tile = create_image( "res/earth_tile.png", screen );
    return ld;
}

static void destroy_level_data( struct level_data* level_data )
{
    destroy_image( level_data->grass_tile ); 
    destroy_image( level_data->earth_tile ); 
    destroy_wizard( level_data->wizard );
    free( level_data );
}

/* prepare_level() is called by Cage before the level is
 * requested to update frames. This is the place
 * to prepare the level and its data.
 */
static int prepare_level( struct toolbox* tbox )
{
    screen_size( tbox->screen, 1024, 576 ) ;
    screen_color( tbox->screen, make_RGB( 170,210,250 ) );
    tbox->data = create_level_data( tbox->screen );
    return tbox->data == 0 ? -1 : 0;
}

/* draw_level() is called for every frame and draws
 * the content of the level (the wizard, level tiles, monsters, etc..).
 * It uses the level_data stored inside the toolbox as well
 * as the LEVEL string that represents the level map using
 * characters for tile selection.
 */
static void draw_level( struct toolbox* tbox )
{
    struct level_data* ld = tbox->data;
    struct rectangle tile_size = { 0,0,16,16 };
    unsigned int i;
    for ( i = 0 ; i < strlen(LEVEL) ; i++ ) {
        /* draw tiles from level map string */
        if ( LEVEL[i] != ' ' ) {
            int x = 16 * ( i%12 );
            int y = 16 * ( i/12 );
            draw_image( tbox->screen, 
                        LEVEL[i] == '-' ? ld->grass_tile : ld->earth_tile, 
                        x, y, &tile_size, 0 ); 
        }
    }
    draw_sprite( tbox->screen, 
                 ld->wizard->sprite, 
                 xy( ld->wizard->pos.x, ld->wizard->pos.y ) );
}

/* update_level is called by the Cage game loop for every frame
 * and has to update the game state ( animations, positions, etc..)
 * as well as redraw the frame using draw_level().
 */
static void update_level( struct toolbox* toolbox )
{
    struct level_data* ld = toolbox->data;
    animate_wizard( ld->wizard, toolbox );
    draw_level( toolbox );
    if ( key_pressed( toolbox->keyboard, KB_ESC ) ) exit(0);
}

/* teardown_level() is called by the Cage game loop once the state
 * is invalidated (by setting a different game state) or when the 
 * game exits.
 */
static void teardown_level( struct toolbox* tbox )
{
    struct level_data* ld = tbox->data;
    destroy_level_data( ld );
}

int main( void )
{
    struct gamestate root = { prepare_level, update_level, teardown_level };
    return gameloop( &root );
}
