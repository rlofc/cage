#ifndef INTERNALS_H_G9CYEQL6
#define INTERNALS_H_G9CYEQL6

#include "SDL.h"

#include "begin_prefix.h"
/* The game drawing surface
 * A screen is you drawing surface for you to draw on
 * your game images, sprites and text.
 *
 * Your <gamestate> functions will get a screen
 * to work with inside the <toolbox> parameter.
 */
struct screen {
    /* internal SDL renderer */
    SDL_Renderer* impl;
    /* internal SDL window */
    SDL_Window* window;
    /* Rendering X offset, for scrolling or shaking */
    float offset_x;
    /* Rendering Y offset, for scrolling or shaking */
    float offset_y;
};
extern struct screen* screen;

struct keyboard {
    const uint8_t* keys;
    int states[256];
};
extern struct keyboard* keyboard;

#include "end_prefix.h"
#endif /* end of include guard: INTERNALS_H_G9CYEQL6 */
