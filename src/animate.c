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
#include "animate.h"
#include <stdlib.h>

struct animation* create_animation(void)
{
    struct animation* ret = (struct animation*)calloc(1, sizeof(struct animation));
    if (ret != NULL) {
        ret->mode = LOOP_FRAMES;
        ret->loop_from = -1;
        ret->loop_to = -1;
        ret->n_frames = 0;
    }
    return ret;
}

void add_frame(struct animation* animation,
               int index_in_sprite,
               int duration,
               void* userdata)
{
    if (animation->n_frames < MAX_FRAMES_PER_ANIMATION) {
        animation->frames[animation->n_frames].frame = index_in_sprite;
        animation->frames[animation->n_frames].duration = duration;
        animation->frames[animation->n_frames].userdata = userdata;
        if (animation->mode == LOOP_FRAMES) {
            if (animation->loop_from == -1) {
                animation->loop_from = 0;
            }
            if (animation->loop_to == -1 ||
                animation->loop_to == animation->n_frames - 1) {
                animation->loop_to = animation->n_frames;
            }
        }
        animation->n_frames++;
    }
}

void add_frames(struct animation* animation, int nframes, struct frame frames[])
{
    int i;
    for (i = 0; i < nframes; i++) {
        add_frame(animation, frames[i].frame, frames[i].duration,
                  frames[i].userdata);
    }
}

void destroy_animation(struct animation* animation)
{
    free(animation);
}
