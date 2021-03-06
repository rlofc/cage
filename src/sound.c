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
#include "sound.h"
#include <stdlib.h>

#include "begin_prefix.h"
struct sound* create_sound(const char* filepath)
{
    struct sound* sound = (struct sound*)malloc(sizeof(struct sound));
    if (sound != NULL) {
        if (load_sound(sound, filepath) == -1) goto error;
        sound->channel = -1;
    }
    return sound;
error:
    free(sound);
    return NULL;
}

void destroy_sound(struct sound* sound)
{
    if (sound != NULL) {
        cleanup_sound(sound);
        free(sound);
    }
}

int load_sound(struct sound* sound, const char* pathname)
{
    if ((sound->sound = Mix_LoadWAV(pathname)) != NULL)
        return 0;
    else
        return -1;
}

int play_sound(struct sound* sound, int loops)
{
    static int channel = 0;
    if (is_playing(sound)) stop_sound(sound);
    sound->channel = Mix_PlayChannel(channel, sound->sound, loops);
    channel++;
    if (channel == CAGE_NUM_OF_MIX_CHANNELS) channel=0;
    return sound->channel;
}

void stop_sound(struct sound* sound)
{
    Mix_HaltChannel(sound->channel);
    sound->channel = -1;
}

void cleanup_sound(struct sound* sound)
{
    Mix_FreeChunk(sound->sound);
}

void set_volume(struct sound* sound, float volume)
{
    Mix_Volume(sound->channel, volume * MIX_MAX_VOLUME);
}

int is_playing(struct sound* sound)
{
    return (sound->channel != -1);
}
#include "end_prefix.h"
