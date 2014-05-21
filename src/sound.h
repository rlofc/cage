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
#ifndef AUDIO_H_IJ4N19XA
#define AUDIO_H_IJ4N19XA
#include <SDL_mixer.h>
#include <stdbool.h>
/**
 * sound effect
 */
struct sound
{
    Mix_Chunk *sound;
    int        channel;
};

/**
 * Create a new sound resource from an OGG, WAV or MP3 file
 */
struct sound* create_sound( const char* filepath );

/**
 * Cleanup and deallocate a sound resource
 */
void destroy_sound( struct sound* sound );

/**
 * Initialize an already allocated sound resource
 * @param pathname file path to the sound file in ogg, wav or mp3 format
 *
 * The sound file in pathname will be loaded and stored
 * for use in /ref resource
 *
 * @return 0 or higher means success
 *         -1 or lower means failure
 */
int load_sound( struct sound* sound, const char* filepath );

/**
 * Play sound Resource
 * @param sound resource to play
 *
 * Will play a valid sound resource
 * 
 * @return 0 or higher means success
 *         -1 or lower means failure
 */
int play_sound( struct sound* sound );

/**
 * Stop playing a sound
 */
void stop_sound( struct sound* sound );

/**
 * cleanup a loaded sound resource
 */
void cleanup_sound( struct sound* sound );

bool is_playing( struct sound* sound );

#endif /* end of include guard: AUDIO_H_IJ4N19XA */
