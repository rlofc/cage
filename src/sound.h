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

/**
 * Sound effect
 */
struct sound
{
    /** Internal SDL2_Mixer sound chunk */
    Mix_Chunk *sound;
    /** When playing, channel number in SDL2_Mixer */
    int        channel;
};

/**
 * Create a new sound effect from an OGG, WAV or MP3 file
 *
 * @return a \ref sound effect resource or NULL on error
 */
struct sound* create_sound( const char* filepath );

/**
 * Cleanup and deallocate a sound effect
 * @param sound sound effect to cleanup and free
 */
void destroy_sound( struct sound* sound );

/**
 * Initialize an already allocated sound effect
 * @param sound \ref sound instance to use
 * @param filepath file path to the sound file in ogg, wav or mp3 format
 *
 * The sound file will be loaded and stored
 * for use in the \ref sound effect.
 *
 * @return 0 or higher on success or -1 or lower on failure
 */
int load_sound( struct sound* sound, const char* filepath );

/**
 * Play sound effect
 * @param sound sound effect to play
 * @param loops -1 - infinite, 0 - play once, 1 - twice and so on..
 *
 * Will play an initialized sound effect
 * 
 * @return 0 or higher means success
 *         -1 or lower means failure
 */
int play_sound( struct sound* sound, int loops );

/**
 * Stop playing a sound
 * @param sound sound effect to stop playing
 */
void stop_sound( struct sound* sound );

/**
 * Internally cleanup an initialized sound effect
 * @param sound sound effect to cleanup 
 */
void cleanup_sound( struct sound* sound );

/**
 * Set the volume of a sound effect
 * @param sound sound effect to modify
 * @param volume volume value between 0.0 and 1.0
 */
void set_volume( struct sound* sound, float volume );

/**
 * Test if a sound effect is playing
 * @param sound sound effect to test
 *
 * @return 1 if the sound effect is being played or 0 otherwise
 */
int is_playing( struct sound* sound );

#endif /* end of include guard: AUDIO_H_IJ4N19XA */
