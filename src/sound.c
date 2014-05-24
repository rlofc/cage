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
#include "sound.h"
#include <stdlib.h>

struct sound* create_sound( const char* filepath )
{
    struct sound* sound = malloc( sizeof( struct sound ) );
    if ( sound != NULL ) {
        load_sound( sound, filepath );
        sound->channel = -1;
    }
    return sound;
}

void destroy_sound( struct sound* sound )
{
    cleanup_sound( sound );
    free( sound );
}

int load_sound( struct sound* sound, const char* pathname )
{
    sound->sound = Mix_LoadWAV( pathname );
    return 0;
}

int play_sound( struct sound* sound, int loops )
{
    if ( is_playing( sound ) ) stop_sound( sound );
    sound->channel = Mix_PlayChannel( -1, sound->sound, loops );
    return 0;
}

void stop_sound( struct sound* sound )
{
    Mix_HaltChannel( sound->channel );
    sound->channel = -1;
}

void cleanup_sound( struct sound* sound )
{
    Mix_FreeChunk( sound->sound );
}

void set_volume( struct sound* sound, float volume )
{
    Mix_Volume( sound->channel, volume*MIX_MAX_VOLUME );
}

int is_playing( struct sound* sound )
{
    return ( sound->channel != -1 );
}
