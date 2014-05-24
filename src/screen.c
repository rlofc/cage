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
#include "screen.h"
#include "internals.h"
#include "utils.h"
#include <stdlib.h>

static struct screen global_screen;
struct screen* screen = &global_screen;

struct cam {
    float progress;
    float tgt;
};

static struct cam cam_x = { 0.0f, 0.0f };
static struct cam cam_y = { 0.0f, 0.0f };

static float animate_shake( struct cam* cam, float stopwatch, float rate )
{
    float offset;
    offset = cam->tgt*-1+fabs(cosine_interp( cam->tgt* -1.0f, cam->tgt ,cam->progress)); 
    cam->progress= clamp( cam->progress+( stopwatch / rate ), 0.0f, 1.0f );;
    if (cam->progress== 1.0f) { cam->progress= 0.0f; }
    return offset;
}

void shake_screen( float stopwatch )
{
    if ( cam_x.progress== 0.0f) { cam_x.tgt= (rand() % 2)+2; }
    screen->offset_x = animate_shake( &cam_x, stopwatch, 100.0f);
    if ( cam_y.progress== 0.0f) { cam_y.tgt= (rand() % 2)+2; }
    screen->offset_y = animate_shake( &cam_y, stopwatch, 100.0f);
}

void relax_screen( float stopwatch )
{
    if ( cam_x.progress != 0.0f)
        screen->offset_x = animate_shake( &cam_x, stopwatch, 500.0f);
    if ( cam_y.progress != 0.0f)
        screen->offset_y = animate_shake( &cam_y, stopwatch, 500.0f);
}

void screen_color( struct color bg )
{
    SDL_SetRenderDrawColor( screen->impl , bg.red, bg.green, bg.blue, bg.alpha );
}

void screen_size( int width, int height )
{
    SDL_SetWindowSize( screen->window, width, height );
}

void draw_on_screen( void )
{
    int ret = SDL_SetRenderTarget( screen->impl, NULL );
    if (ret !=0 ) exit(1);
}

