/* samples / timeline.c
 * ====================
 * In this example we will learn how to use the timeline.
 */
#include "cage.h"

/* The sample data struct
 * ----------------------
 *
 * We use a struct to hold the sample resources:
 * a timeline and a font.
 *
 */
struct sample_data {
    struct timeline* timeline;
    struct font* font;
};

/* Timeline event callbacks
 * ------------------------
 *
 * The following functions are timeline event callbacks. These
 * functions will be called by the timeline based on its registered
 * events.
 * Each function gets call on every frame update during its duration.
 * The **data** argument will hold any data you pass to **update_timeline**.
 * The **progress** argument will range from 0 to 1 based on the event
 * duration.
 */
static void* fade_in( void* data, float elapsed_ms, float progress )
{
    struct sample_data* sd = data;
    screen_color( make_RGB( 255*progress, 255*progress, 255*progress ) );
    UNUSED( elapsed_ms ); return NULL;
}

static void* caption_1( void* data, float elapsed_ms, float progress )
{
    struct sample_data* sd = data;
    draw_text( sd->font, "Once upon a time,", 10, 10 );
    UNUSED( elapsed_ms ); UNUSED( progress ); return NULL;
}

static void* caption_2( void* data, float elapsed_ms, float progress )
{
    struct sample_data* sd = data;
    draw_text( sd->font, "in a land far, far away...", 10, 10 );
    UNUSED( elapsed_ms ); UNUSED( progress ); return NULL;
}

static void* quit( void* data, float elapsed_ms, float progress )
{
    exit(0);
    UNUSED( data ); UNUSED( elapsed_ms ); UNUSED( progress ); return NULL;
}

/* Prepare
 * -------
 *
 * We use the game state prepare function to create the sample data
 * struct instance that holds the timeline and a font.
 * Once we have a new timeline, we use append_event() to add events.
 */
static void* prepare_sample( void )
{
    struct sample_data* sd = malloc( sizeof( struct sample_data ) );
    if ( sd == NULL ) return NULL;

    sd->timeline = create_timeline();
    if ( sd->timeline ) {
        append_event( sd->timeline, 0, 1000, fade_in );
        append_event( sd->timeline, 0, 1000, caption_1 );
        append_event( sd->timeline, 0, 1000, caption_2 );
        append_event( sd->timeline, 0, 1000, quit );
    } else return NULL;

    sd->font = create_font( "res/font.png", 32, 4 );
    if ( sd->font == NULL ) return NULL;
    return sd;
}
 
/* Update
 * ------
 *
 * For each frame, the update state function will update the timeline,
 * resulting event callbacks invocation.
 * The data and elapsed_ms arguments we pass along will eventually end 
 * up getting to the timeline callbacks.
 */
static void update_sample( void* data, float elapsed_ms )
{
    struct sample_data* sd = data;
    update_timeline( sd->timeline, sd, elapsed_ms ); 
}

/* Teardown
 * --------
 *
 * In the teardown function we destroy the timeline, 
 * destroy the font and free the memory we allocated for
 * the sample data struct.
 */
static void teardown_sample( void* data )
{
    struct sample_data* sd = data;
    destroy_timeline( sd->timeline );
    destroy_font( sd->font );
    free( data );
}

/* Main
 * ----
 *
 * Finally, the game's main function delegates the
 * execution to Cage's game_loop() function together with
 * the 3 state functions we wrote.
 */
int main( void )
{
    return game_loop( prepare_sample, update_sample, teardown_sample );
}
