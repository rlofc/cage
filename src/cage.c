/* Copyright (c) 2014-2016 Ithai Levi @RLofC
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "internals.h"
#include "image.h"
#include "sound.h"
#include "types.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

/* global toolbox so we can
 * cleanup using atexit()
 */
static struct toolbox* toolbox;

struct gamestate {
    create_func_t create;
    update_func_t update;
    destroy_func_t destroy;
} state = { NULL, NULL, NULL };

static int read_conf_file(struct settings* settings)
{
    FILE* fp;
    char *token1, *token2, *str;

    char bufr[1024];
    char empty[1];
    empty[0] = 0;
    if ((fp = fopen("res/game.conf", "r")) == NULL) return -1;
    while (fgets(bufr, 1024, fp) != NULL) {
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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_OGG);
}

static void teardown_sdl(void)
{
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

static void prepare_audio_device(void)
{
    // int audio_rate = 22050;
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    // int audio_buffers = 4096;
    int audio_buffers = 1024;
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels,
                      audio_buffers)) {
        printf("Unable to open audio!\n");
        exit(1);
    }
    Mix_AllocateChannels(CAGE_NUM_OF_MIX_CHANNELS);
}

static void teardown_audio_device(void)
{
    Mix_CloseAudio();
}

static void prepare_screen(const struct settings* settings)
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    window =
    SDL_CreateWindow("CAGE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                     settings->window_width, settings->window_height,
                     settings->fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, settings->logical_width,
                             settings->logical_height);
    SDL_RenderClear(renderer);

    screen->impl = renderer;
    screen->window = window;
    screen->offset_x = 0;
    screen->offset_y = 0;
}

static void teardown_screen(void)
{
    SDL_DestroyRenderer(screen->impl);
    SDL_DestroyWindow(screen->window);
}

static void message_box(const char* title, const char* message)
{
    SDL_ShowSimpleMessageBox(0, title, message, screen->window);
}

void exit_with_error_msg(const char* msg)
{
    message_box("Cage", msg);
    exit(1);
}

#define ERROR_BUF_SIZE 1024 * 32
static char error_msgs_buffer[ERROR_BUF_SIZE];

void error_msg(const char* msg)
{
    strncat(error_msgs_buffer, "\n", ERROR_BUF_SIZE - 1);
    strncat(error_msgs_buffer, msg, ERROR_BUF_SIZE - 1);
}

static void cleanup(void)
{
    toolbox->state->destroy(toolbox->data);
    teardown_audio_device();
    teardown_screen();
    free(toolbox);
    teardown_sdl();
}

void game_state(create_func_t create,
                update_func_t update,
                destroy_func_t destroy)
{
    if (toolbox->state->destroy != NULL) toolbox->state->destroy(toolbox->data);
    toolbox->state->create = create;
    toolbox->state->update = update;
    toolbox->state->destroy = destroy;
    toolbox->stopwatch = 0;
    toolbox->data = toolbox->state->create();
    if (toolbox->data == NULL) {
        error_msg("Game state initialization failed!");
        message_box("Cage broke!", error_msgs_buffer);
        exit(1);
    }
}

static struct settings* g_settings;

static void init_game(struct settings* settings)
{
    g_settings = settings;
}

int game_setup_and_loop(setup_func_t setup,
                        create_func_t create,
                        update_func_t update,
                        destroy_func_t destroy)
{
    bool quit = false;
    Uint32 start;
    Uint32 now;
    SDL_Event event;
    prepare_sdl();
    struct settings settings;
    setup(&settings);
    prepare_screen(&settings);
    prepare_audio_device();
    toolbox = malloc(sizeof(struct toolbox));
    if (toolbox == NULL) {
        exit(1);
    }
    atexit(cleanup);
    toolbox->state = &state;
    toolbox->data = NULL;
    game_state(create, update, destroy);
    start = SDL_GetTicks();
    while (!quit) {
        SDL_PumpEvents();
        if (SDL_HasEvent(SDL_QUIT)) {
            quit = true;
            break;
        }
        SDL_RenderClear(screen->impl);
        /* limit framerate to ~60FPS */
        now = SDL_GetTicks();
        if (now - start < 16) SDL_Delay(16 - (now - start));
        now = SDL_GetTicks();

        toolbox->stopwatch = now - start;
        keyboard->keys = SDL_GetKeyboardState(NULL);
        toolbox->state->update(toolbox->data, toolbox->stopwatch);
        start = now;
        SDL_RenderPresent(screen->impl);
    }
    return 0;
}

static void default_setup_callback(struct settings* settings)
{
    settings->window_width = 1280;
    settings->window_height = 720;
    settings->logical_width = 192;
    settings->logical_height = 108;
    settings->fullscreen = false;
    read_conf_file(settings);
}

int game_loop(create_func_t create,
              update_func_t update,
              destroy_func_t destroy)
{
    return game_setup_and_loop(default_setup_callback, create, update, destroy);
}
