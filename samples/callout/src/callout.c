/* samples / callout.c
 * ===================
 * This not so short sample will pop-up a callout bubble with
 * some text in it. It will demonstrate how to use image as a
 * user interface skin, how to draw text and how to use
 * an the timeline and easing functions for animations.
 */
#include "cage.h"

/* Sample preparation code
 * -----------------------
 *
 * For this sample we'll need a background image, a font
 * to draw text with, a stencil image that holds the skin
 * of our callout box and a timeline to animate the pop-up
 * effect of the callout.
 */
static struct sample_data {
    struct timeline* timeline;
    struct image* stencil;
    struct font* font;
    struct image* background;
} sample_data = { NULL, NULL, NULL, NULL };

/*
 * This is going to be the callout text:
 */
static const char* CO_TEXT = "Welcome to Cage,\nthe elementary"
                             " game\ndevelopment library for\n"
                             "the C programming\nlanguage.";

/*
 * And, this is where the callout will originate from,
 * the callout arrow head position:
 */
static const struct point CO_ORIGIN = { 20, 40 };
static const struct point CO_TIP_OFFSET = { 10, 0 };

/*
 * These callback functions will be the events on
 * the animation timeline. wait() will create a short
 * pause when starting the sample, popup() will animate
 * the appearance of the callout and show will simply
 * draw the static callout.
 */
void* popup( void* data, float elapsed_ms, float progress );
void* show( void* data, float elapsed_ms, float progress );

/*
 * These are going to be the sample timeline
 * events. The program will draw the background,
 * wait for a second, then animate the callout
 * during 1 second and finally, just draw the callout
 * for 10 seconds. Easy peasy:
 */
#define N_CO_EVENTS  2
static struct timeline_event CO_EVENTS[N_CO_EVENTS] = {
    { 1*SECOND, popup, 1*SECOND }, { 0, show, 10*SECONDS }
};

/* Creating the state data
 * -----------------------
 *
 * We use the game state create() function to initialize
 * the state data structure: the background image,
 * the callout stencil, the font and the timeline.
 */
#define SAFELY(c) \
    if ( (c) == NULL ) goto error
#define IF_NEEDED(f,p) \
    if ( p != NULL ) f(p)
static void* create_sample( void )
{
    SAFELY( sample_data.background = create_image("res/bg.png" ) );
    SAFELY( sample_data.stencil = create_image( "res/callout.png" ) );
    SAFELY( sample_data.font = create_font( "res/font.png", 16, 16 ) );
    sample_data.font->line_spacing = 1;
    sample_data.font->char_spacing = 1;
    SAFELY( sample_data.timeline = create_timeline() );
    if ( append_events( sample_data.timeline, N_CO_EVENTS, CO_EVENTS ) == -1 ) {
        ERROR( "unable to append timeline events" ); goto error;
    }
    return &sample_data;

error:
    IF_NEEDED( destroy_image, sample_data.background );
    IF_NEEDED( destroy_image, sample_data.stencil );
    IF_NEEDED( destroy_font, sample_data.font );
    IF_NEEDED( destroy_timeline, sample_data.timeline );
    return NULL;
}

/* Drawing a callout box
 * ---------------------
 *
 * The callout Stencil has the following
 * skin components:
 */
enum {
    TOP_LEFT = 0, TOP = 1, TOP_EX = 2, TOP_RIGHT = 3,
    LEFT = 4, FILL = 5, FILL_COL_EX = 6,  RIGHT = 7,
    LEFT_EX = 8, FILL_ROW_EX = 9, FILL_COL_ROW_EX = 10, RIGHT_EX = 11,
    BOTTOM_LEFT = 12, BOTTOM = 13, BOTTOM_EX = 14, BOTTOM_RIGHT = 15
};

/*
 * Each tile of the callout stencil has a 16x16 pixel size
 */
#define GSIZE 16
#define GRID(X,Y) GSIZE*X, GSIZE*Y, GSIZE, GSIZE

/*
 * The stencil has each component in these grid positions:
 */
static struct rectangle rects[16] = {
    { GRID(0,0) }, { GRID(2,0) }, { GRID(2,0) }, { GRID(4,0) },
    { GRID(0,1) }, { GRID(1,1) }, { GRID(1,1) }, { GRID(4,1) },
    { GRID(0,1) }, { GRID(1,1) }, { GRID(1,1) }, { GRID(4,1) },
    { GRID(0,2) }, { GRID(2,2) }, { GRID(2,2) }, { GRID(4,2) }
};

/*
 * This is how we draw the border tiles (corners and lines)
 * of the callout.
 */
static void draw_border( struct image* stencil, int x, int y, int w, int h )
{
    int r,c;
    int inner_cols;
    int inner_rows;

    inner_cols = w > GSIZE*2 ? ( w - (GSIZE*2) ) / GSIZE : 0;
    inner_rows = h > GSIZE*2 ? ( h - (GSIZE*2) ) / GSIZE : 0;

    /* draw corners */
    draw_image( stencil, x, y, &rects[TOP_LEFT] ,0 );
    draw_image( stencil, x+w-GSIZE, y, &rects[TOP_RIGHT] ,0 );
    draw_image( stencil, x, y+h-GSIZE, &rects[BOTTOM_LEFT] ,0 );
    draw_image( stencil, x+w-GSIZE, y+h-GSIZE, &rects[BOTTOM_RIGHT] ,0 );

    /* draw borders */
    for ( r = 0 ; r <= inner_rows ; r++ ) {
        struct rectangle* left = &rects[ LEFT ];
        struct rectangle* right = &rects[ RIGHT ];
        if ( r == inner_rows ) {
            left = &rects[ LEFT_EX ];
            right = &rects[ RIGHT_EX ];
        }
        draw_image( stencil, x, y+GSIZE+r*GSIZE, left,0 );
        draw_image( stencil, x+w-GSIZE, y+GSIZE+r*GSIZE, right,0 );
    }

    for ( c = 0 ; c <= inner_cols ; c++ )
    {
        struct rectangle* top = &rects[ TOP ];
        struct rectangle* bottom = &rects[ BOTTOM ];
        if ( c == inner_cols ) {
            top = &rects[ TOP_EX ];
            bottom = &rects[ BOTTOM_EX ];
        }
        draw_image( stencil, x+GSIZE+c*GSIZE,y, top,0 );
        draw_image( stencil, x+GSIZE+c*GSIZE,y+h-GSIZE, bottom,0 );
    }
}

/*
 * This is how we fill the inner area of the callout.
 */
static void fill_box( struct image* stencil, int x, int y, int w, int h )
{
    int r,c;
    int inner_cols;
    int inner_rows;
    inner_cols = w > GSIZE*2 ? ( w - (GSIZE*2) ) / GSIZE : 0;
    inner_rows = h > GSIZE*2 ? ( h - (GSIZE*2) ) / GSIZE : 0;
    for ( r = 0 ; r <= inner_rows ; r++ ) {
        for ( c = 0 ; c <= inner_cols ; c++ ) {
            struct rectangle* rect = &rects[ FILL ];
            if ( r == inner_rows && c == inner_cols ) rect = &rects[ FILL_COL_ROW_EX ];
            else if ( r == inner_rows ) rect = &rects[ FILL_ROW_EX ];
            else if ( c == inner_cols ) rect = &rects[ FILL_COL_EX ];
            draw_image( stencil, x+GSIZE+c*GSIZE,y+GSIZE+r*GSIZE, rect,0 );
        }
    }
 }

/*
 * This will draw the callout box, without the callout tip
 */
static void draw_box( void* data, int x, int y, int w, int h )
{
    rects[ FILL_ROW_EX ].h = rects[ FILL_COL_ROW_EX ].h = ( ( h - GSIZE*2 ) % GSIZE );
    rects[ FILL_COL_EX ].w = rects[ FILL_COL_ROW_EX ].w = ( ( w - GSIZE*2 ) % GSIZE );

    rects[ LEFT_EX ].h = rects[ RIGHT_EX ].h =  ( ( h - GSIZE*2 ) % GSIZE );
    rects[ TOP_EX ].w  = rects[ BOTTOM_EX ].w   =  ( ( w - GSIZE*2 ) % GSIZE );

    draw_border( data, x, y, w, h );
    fill_box( data, x, y, w, h );
}

/*
 * This will draw the callout box and the callout tip
 */
static void draw_callout( void* data, int x, int y, int w, int h )
{
    struct rectangle callout = { GRID(1,2) };
    draw_box( data, x, y, w, h );
    draw_image( data, x+2*GSIZE,y+h-GSIZE, &callout,0 );
}

/* Updating the frames
 * -------------------
 *
 * For each frame, the update state function will draw the background
 * image and then use the timeline to activate the sample events
 * for pop-up the callback and continue drawing it for a few seconds.
 * We explicitly eliminate any unused parameter warning using
 * the UNUSED macro.
 */
static void update_sample( void* data, float elapsed_ms )
{
    struct rectangle clip = { 0, 0, 192, 108 };
    struct sample_data* sdata = data;
    screen_color( color_from_RGB( 120,120,120 ) );
    draw_image( sdata->background, 0, 0, &clip, 0 ); 
    update_timeline( sdata->timeline, sdata, elapsed_ms );
    UNUSED( elapsed_ms );
}

void* popup( void* data, float elapsed_ms, float progress )
{
    int x,y,tx,ty;
    struct sample_data* sdata = data;
    float bounce = (bounce_ease_out( progress ));
    int w,h; measure_text( sdata->font, CO_TEXT, &w, &h );
    x = w/2+CO_ORIGIN.x-((w/2-CO_TIP_OFFSET.x)*bounce);
    y = h/2+CO_ORIGIN.y-((h/2+h-CO_TIP_OFFSET.y)*bounce);
    draw_box( sdata->stencil, x, y, (w*bounce)+32, (h*bounce)+32 );
    UNUSED( elapsed_ms ); return NULL;
}

void* show( void* data, float elapsed_ms, float progress )
{
    int x,y,tx,ty;
    struct sample_data* sdata = data;
    int w,h; measure_text( sdata->font, CO_TEXT, &w, &h );
    x = w/2+CO_ORIGIN.x-((w/2-CO_TIP_OFFSET.x)*1.0f);
    y = h/2+CO_ORIGIN.y-((h/2+h-CO_TIP_OFFSET.y)*1.0f);
    draw_callout( sdata->stencil, x, y, w+32, h+32 );
    draw_text( sdata->font, CO_TEXT, x+16,y+16 );
    UNUSED( progress ); UNUSED( elapsed_ms ); return NULL;
}

/* Destroying and finalizing
 * -------------------------
 *
 * When exiting the sample, the destroy_sample()
 * function will destroy any allocated resources.
 *
 */
static void destroy_sample( void* data )
{
    struct sample_data* sdata = data;
    destroy_image( sdata->stencil );
    destroy_font( sdata->font );
    destroy_timeline( sdata->timeline );
    destroy_image( sdata->background );
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
