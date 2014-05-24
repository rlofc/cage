/* Copyright (c) 2014 Ithai Levi @RLofC
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */
#include "cage.h"
#include "internals.h"
#include "image.h"
#include "sound.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* global toolbox so we can 
 * cleanup using atexit()
 */
static struct toolbox* toolbox;

struct settings {
    int window_width;
    int window_height;
    int logical_width;
    int logical_height;
};

struct gamestate
{
    prepare_func_t prepare;
    update_func_t update;
    teardown_func_t teardown;
} state = { NULL, NULL, NULL };

static int read_conf_file( struct settings* settings )
{
    FILE* fp;
    char *token1; char *token2; char *str;

    char bufr[1024];
    char empty[1];
    empty[0] = 0;
    if ((fp = fopen("res/game.conf", "r")) == NULL) return -1;
    while (fgets(bufr, 1024, fp) != NULL)
    {
        if (bufr[0] == '#' || bufr[0] == '\n') continue;
        token2 = empty;
        for (str = bufr; (token1 = strtok(str, " \n\t")) != 0; str = NULL) {
            if (strcmp(token2, "window_width") == 0) {
                settings->window_width = atoi(token1);
            }
            if (strcmp(token2, "window_height") == 0) {
                settings->window_height = atoi(token1);
            }
            if (strcmp(token2, "logical_width") == 0) {
                settings->logical_width = atoi(token1);
            }
            if (strcmp(token2, "logical_height") == 0) {
                settings->logical_height = atoi(token1);
            }
            token2 = token1;
            if (str == NULL) break;
        }
    }
    fclose(fp);
    return 0;
}

static void prepare_sdl(void)
{
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    IMG_Init( IMG_INIT_PNG );
}

static void teardown_sdl(void)
{
    IMG_Quit();
    SDL_Quit();
}

static void prepare_audio_device(void)
{
    int    audio_rate     = 22050;
    Uint16 audio_format   = AUDIO_S16; /* 16-bit stereo */
    int    audio_channels = 2;
    int    audio_buffers  = 4096;
    if ( Mix_OpenAudio( audio_rate, audio_format, audio_channels, audio_buffers ) ) {
        printf( "Unable to open audio!\n" );
        exit(1);
    }
}

static void teardown_audio_device(void)
{
    Mix_CloseAudio();
}

static void prepare_screen( const struct settings* settings )
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    window = SDL_CreateWindow( "CAGE",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings->window_width,
        settings->window_height, 0 );
    renderer = SDL_CreateRenderer( window, -1, 0 );
    SDL_RenderSetLogicalSize( renderer, settings->logical_width, settings->logical_height );
    SDL_RenderClear( renderer );

    screen->impl = renderer;
    screen->window = window;
    screen->offset_x = 0;
    screen->offset_y = 0;
}

static void teardown_screen( void )
{
    SDL_DestroyWindow( screen->window );
    SDL_DestroyRenderer( screen->impl );
}

static void message_box( const char* title, const char* message )
{
    SDL_ShowSimpleMessageBox( 0, title, message, screen->window );
}

void exit_with_error_msg( const char* msg )
{
    message_box( "Cage", msg );
    exit(1);
}

#define ERROR_BUF_SIZE 1024*32
static char error_msgs_buffer[ERROR_BUF_SIZE];

void error_msg( const char* msg )
{
    strncat( error_msgs_buffer, "\n", ERROR_BUF_SIZE-1 );
    strncat( error_msgs_buffer, msg , ERROR_BUF_SIZE-1 );
}

static void cleanup(void)
{
    toolbox->state->teardown(toolbox->data);
    teardown_audio_device();
    teardown_screen();
    free( toolbox );
    teardown_sdl();
}

void game_state( prepare_func_t prepare, update_func_t update, teardown_func_t teardown )
{
    if ( toolbox->state->teardown != NULL ) toolbox->state->teardown( toolbox->data );
    toolbox->state->prepare = prepare;
    toolbox->state->update = update;
    toolbox->state->teardown = teardown;
    toolbox->stopwatch = 0;
    toolbox->data = toolbox->state->prepare();
    if ( toolbox->data == NULL ) {
        error_msg( "Game state initialization failed!" );
        message_box( "Cage broke!", error_msgs_buffer );
        exit(1);
    }
}


int game_loop( prepare_func_t prepare, update_func_t update, teardown_func_t teardown )
{
    bool quit = false;

    struct settings  settings = { 640, 360, 192, 108 };

    Uint32 start;
    Uint32 now ;

    SDL_Event event;
    read_conf_file( &settings );

    prepare_sdl();
    prepare_screen( &settings );
    prepare_audio_device();

    toolbox = malloc( sizeof( struct toolbox ) );
    if ( toolbox == NULL ) {
        exit(1);
    }

    atexit(cleanup);
    toolbox->state = &state;
    toolbox->data = NULL;

    game_state( prepare, update, teardown );

    start = SDL_GetTicks();

    while (!quit) {

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
        SDL_RenderClear(screen->impl);

        /* limit framerate to ~60FPS */
        now = SDL_GetTicks();
        if ( now-start < 16 ) SDL_Delay( 16 - (now-start) );
        now = SDL_GetTicks();

        toolbox->stopwatch = now - start;

        keyboard->keys = SDL_GetKeyboardState(NULL);

        toolbox->state->update( toolbox->data, toolbox->stopwatch );
        start = now;
        
        SDL_RenderPresent(screen->impl);
    }

    return 0;
}
