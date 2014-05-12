/* ## Wizard */
#include "cage.h"
#include <string.h>
#include <stdio.h>
#include <stdio.h>

/* This (still incomplete) sample shows how **Cage** may be used
 * to write a small 2D game.
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
static const char* LEVEL = "             "
                           "             "
                           "             "
                           "             "
                           "             "
                           "-------------"
                           ".............";

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
 * and creating a sprite with the proper frame size
 * as well as creating the set of animations required
 * to animate the wizard. 
 *
 * Animations can be re-used by any number of 
 * sprites, however in this example the animations
 * are an integral part of the wizard data-structure.
 *
 * Pay attention to the way we defined the walking
 * loop cycle. First, we associated the walking speed
 * by using the user data parameter in add_frame.
 * Then, we set the loop sequence starting frame to
 * the second frame ( index=1 ). This way, the 
 * first frame ( index=0 ) of the walking animation is
 * used as a transition frame from the standing pose.
 * We also limit the loop to the fifth frame ( index=4)
 * allowing the last frame to translate the wizard
 * back to the standing pose.
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
 * created resource in the **create\_wizard** function,
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

/* The wizard is controlled using the keyboard (for now).
 * **animate\_wizard()** sets the wizard animation
 * based on the player keypresses and the animation user-data
 * as it was set up in the **create\_wizard()** function.
 */
static void animate_wizard( struct wizard* wizard, struct toolbox* tbox )
{
    const void* px;
    /* set wizard animation according to keyboard */
    struct animation* active_anim;
    active_anim = key_down( tbox->keyboard, KB_SPACE ) ? wizard->spell :
                  key_down( tbox->keyboard, KB_RIGHT ) ? wizard->walk :
                                                      wizard->stand;
    play_animation( wizard->sprite, active_anim );
    /* animate the wizard */
    if (( px = animate_sprite( wizard->sprite, tbox->stopwatch ) ) != NULL) {
        wizard->speed = *((const float*)px);
    }
    wizard->pos.x += wizard->speed;
}


/* At the beginning of the main game state, a title
 * sprite will show up with a shining effect.
 * **game\_title** struct encapsulate both the sprite
 * and the shine animation.
 */
struct game_title {
    struct sprite* sprite;
    struct animation* bling;
};

static void prepare_title( struct game_title* title, struct screen* screen )
{
    int f;
    title->sprite = create_sprite( create_image( "res/title.png", screen ), 70, 15 );
    title->bling = create_animation();
        add_frame( title->bling, 0, SECOND/2, NULL );
        for ( f = 5 ; f >= 0 ; f-- )
            add_frame( title->bling, f, SECOND/10 , NULL );
        title->bling->mode = FREEZE_LAST_FRAME;
}

static void cleanup_title( struct game_title* title )
{
    destroy_sprite( title->sprite );
    destroy_animation( title->bling );
}

/* I just added another sprite to use as an 
 * animated scenery element, for fun..
 */
struct tree {
    struct sprite* sprite;
    struct animation* windblow;
};

static void prepare_tree( struct tree* tree, struct screen* screen )
{
    tree->sprite = create_sprite( create_image("res/tree.png", screen ) , 32,32 );
    tree->windblow = create_animation();
        add_frame( tree->windblow, 0, 1*SECOND, NULL );
        add_frame( tree->windblow, 1, 1*SECOND, NULL );
    tree->windblow->loop_from = 0;
    tree->windblow->loop_to = 1;
}

static void cleanup_tree( struct tree* tree )
{
    destroy_sprite( tree->sprite );
    destroy_animation( tree->windblow );
}

/* **level\_data** is stored inside
 * toolbox->data and as such, is made
 * available to the game state functios.
 * This is the place to store anything we
 * need to work with: characters, sprites, tiles,
 * timelines and the likes.
 */
struct level_data {
    struct game_title title;
    struct wizard* wizard;
    struct image* grass_tile;
    struct image* earth_tile;
    struct tree tree;
    struct timeline* timeline;
};

/* **slide\_title\_in()**, **slide\_title\_out()** and
 * **bling\_title()** are used by the level
 * timeline to animate the title.
 *
 * We use cosine interpolation to slide the title in
 * and out, creating a smoother effect.
 *
 * **progress** will hold a value between 0 to 1
 * based on the event progess/duration, making it ideal
 * for use with interpolation functions.
 */
static void* slide_title_in( struct toolbox* tbox, float progress )
{
    struct level_data* ldata = tbox->data;
    draw_sprite( tbox->screen, ldata->title.sprite, cosine_interp(-100,20,progress),10);
    return NULL;
}

static void* slide_title_out( struct toolbox* tbox, float progress )
{
    struct level_data* ldata = tbox->data;
    draw_sprite( tbox->screen, ldata->title.sprite, cosine_interp(20,200,progress),10);
    return NULL;
}

static void* bling_title( struct toolbox* tbox, float progress )
{
    struct level_data* ldata = tbox->data;
    draw_sprite( tbox->screen, ldata->title.sprite, 20,10);
    if ( progress < 0.1 )
        play_animation( ldata->title.sprite, ldata->title.bling );
    animate_sprite( ldata->title.sprite, tbox->stopwatch );
    return NULL;
}

/* **level\_data** is created and populated with
 * level specific entities. Some entities require further
 * initialization, such as the timeline.
 * A timeline allows creating a sequence of events
 * on a, well.. time line. Each event has a start time
 * ,duration and callback function the will get called
 * each time the timeline is updated, if the event
 * is active.
 * We use a timeline to animate the title, creating 3
 * events: (1) slide the title into the screen (2)
 * make the title "bling" and (3) slide the title out
 * of the screen.
 * Using the SECOND and SECONDS constant is for
 * the sake of readability only.
 */
static struct level_data* create_level_data( struct screen* screen )
{
    struct level_data* ldata = calloc( 1, sizeof ( struct level_data ) );
    ldata->wizard = create_wizard( screen );

    prepare_title( &ldata->title, screen );
    prepare_tree( &ldata->tree, screen );

    ldata->grass_tile = create_image( "res/grass_tile.png", screen );
    ldata->earth_tile = create_image( "res/earth_tile.png", screen );
    play_animation( ldata->tree.sprite, ldata->tree.windblow );

    ldata->timeline = create_timeline();
        append_event( ldata->timeline, 1*SECOND, 1*SECOND,  slide_title_in );
        append_event( ldata->timeline, 0,        4*SECONDS, bling_title );
        append_event( ldata->timeline, 0,        1*SECOND,  slide_title_out );
    return ldata;
}

/* Even good things come to an end, and
 * just like after a fine dinner, someone has to do
 * the dishes.
 */
static void destroy_level_data( struct level_data* ldata )
{
    cleanup_title( &ldata->title );
    cleanup_tree( &ldata->tree );
    destroy_image( ldata->grass_tile );
    destroy_image( ldata->earth_tile );
    destroy_wizard( ldata->wizard );
    destroy_timeline( ldata->timeline );
    free( ldata );
}

/* **prepare\_level()** is called by Cage before the level is
 * requested to update frames. This is the place
 * to prepare the level and its data.
 */
static int prepare_level( struct toolbox* tbox )
{
    /* screen_size( tbox->screen, 1024/5, 576/5 ) ; */
    screen_size( tbox->screen, 1024, 576 ) ;
    screen_color( tbox->screen, make_RGB( 170,210,250 ) );
    tbox->data = create_level_data( tbox->screen );
    return tbox->data == 0 ? -1 : 0;
}

/* **draw\_level()** is called for every frame and draws
 * the content of the level (the wizard, level tiles, monsters, etc..).
 * It uses the level_data stored inside the toolbox as well
 * as the LEVEL string that represents the level map using
 * characters for tile selection.
 */
static void draw_level( struct toolbox* tbox )
{
    struct level_data* ldata = tbox->data;
    struct rectangle tile_size = { 0,0,16,16 };
    unsigned int i;

    if ( ldata->wizard->sprite->active_animation == ldata->wizard->spell ) {
        if ( ldata->wizard->sprite->current_frame > 1 )
            shake_screen( tbox->screen, tbox->stopwatch );
    } else {
        relax_screen( tbox->screen, tbox->stopwatch );
    }

    for ( i = 0 ; i < strlen(LEVEL) ; i++ ) {
        /* draw tiles from level map string */
        if ( LEVEL[i] != ' ' ) {
            int x = 16 * ( i%13 );
            int y = 16 * ( i/13 );
            draw_image( tbox->screen, 
                        LEVEL[i] == '-' ? ldata->grass_tile : ldata->earth_tile, 
                        x, y, &tile_size, 0 ); 
        }
    }
    draw_sprite( tbox->screen, ldata->tree.sprite, 100,56);
    draw_sprite( tbox->screen, 
                 ldata->wizard->sprite, 
                 xy( ldata->wizard->pos.x, ldata->wizard->pos.y) );
}


/* **update\_level()** is called by the Cage game loop for every frame
 * and has to update the game state ( animations, positions, etc..)
 * as well as redraw the frame using **draw\_level()**.
 */
static void update_level( struct toolbox* tbox )
{
    struct level_data* ldata = tbox->data;
    animate_wizard( ldata->wizard, tbox );
    animate_sprite( ldata->tree.sprite, tbox->stopwatch );
    draw_level( tbox );
    update_timeline( ldata->timeline, tbox ); 
    if ( key_pressed( tbox->keyboard, KB_ESC ) ) exit(0);
}

/* **teardown\_level()** is called by the Cage game loop once the state
 * is invalidated (by setting a different game state) or when the 
 * game exits.
 */
static void teardown_level( struct toolbox* tbox )
{
    struct level_data* ldata = tbox->data;
    destroy_level_data( ldata );
}

/* Nothing much in here, just a setting the
 * initial game state and starting the 
 * game loop.
 */
int main( void )
{
    struct gamestate root = { prepare_level, update_level, teardown_level };
    return gameloop( &root );
}
