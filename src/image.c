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
#include "image.h"
#include <memory.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>

int load_image( struct image* image, struct screen* screen, const char* filepath) 
{
    int ret = -1;
    SDL_Surface* s = NULL;
    SDL_Surface* fs = NULL;
    uint32_t *pixels;
    int pitch;
    int npixels;
    uint32_t colorKey;  
    uint32_t transparent;
    int i;


    s = IMG_Load( filepath ) ;
    if ( s == NULL ) goto exit;

    fs = SDL_ConvertSurfaceFormat( s, SDL_PIXELFORMAT_RGBA8888, 0 );
    if ( fs == NULL ) goto free_s;

    image->impl = SDL_CreateTexture( screen->impl, SDL_PIXELFORMAT_RGBA8888, 
                                      SDL_TEXTUREACCESS_STREAMING, fs->w, fs->h );
    if ( image->impl == NULL ) goto free_fs;

    image->width = fs->w;
    image->height = fs->h;

    SDL_SetTextureBlendMode( image->impl, SDL_BLENDMODE_BLEND );

    lock_image( image, (void*) &pixels, &pitch);
    memcpy( (void*) pixels, fs->pixels, fs->pitch * fs->h );

    npixels = ( pitch / 4 ) * fs->h;

    colorKey = SDL_MapRGB( fs->format, 0, 0xFF, 0xFF );
    transparent = SDL_MapRGBA( fs->format, 0x00, 0xFF, 0xFF, 0x00 );

    for( i = 0; i < npixels; ++i ) {
        if( pixels[ i ] == colorKey ) {
            pixels[ i ] = transparent;
        }
    }

    unlock_image( image );
    ret = 0;

free_fs:
    SDL_FreeSurface( fs );
free_s:
    SDL_FreeSurface( s );
exit:
    return ret;
}


int cleanup_image( struct image* image ) 
{
    SDL_DestroyTexture( image->impl );
    image->impl = NULL;
    return 0;
}


int lock_image( struct image* image, void** pixels, int* pitch )
{
    if ( SDL_LockTexture( image->impl, NULL, pixels, pitch ) != 0 )
        return -1;
    return 0;
}


int unlock_image( struct image* image )
{
    SDL_UnlockTexture( image->impl );
    return 0;
}


void draw_image( struct screen*  screen,
                 struct image*   image, 
                           int   x, 
                           int   y, 
             struct rectangle*   clip, 
                        double   angle ) 
{
	SDL_Rect render_quad; 
    SDL_Rect sdl_clip;

    render_quad.x = x;
    render_quad.y = y;
    render_quad.w = image->width;
    render_quad.h = image->height;

	if( clip != NULL ) {
		render_quad.w = clip->w;
		render_quad.h = clip->h;
        sdl_clip.x = clip->x;
        sdl_clip.y = clip->y;
        sdl_clip.w = clip->w;
        sdl_clip.h = clip->h;
	}

	SDL_RenderCopyEx( screen->impl, image->impl, &sdl_clip, &render_quad, angle, NULL, SDL_FLIP_NONE );
}

struct image* create_image( const char* filepath, struct screen* screen ) 
{
    struct image* image = malloc( sizeof (struct image) );
    load_image( image, screen, filepath );
    return image;
}

void destroy_image( struct image* image )
{
    free( image );
}
