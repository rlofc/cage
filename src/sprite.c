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
#include "sprite.h"
#include "utils.h"

int prepare_sprite(struct sprite* sprite,
                   struct image* image,
                   int frame_width,
                   int frame_height)
{
    if (image == NULL || sprite == NULL) {
        ERROR("Sprite initialization failed, pointer is NULL");
        return -1;
    }
    if (frame_width > image->width || frame_height > image->height) {
        ERROR("Sprite frame size is bigger than the image size");
        return -1;
    }
    sprite->image = image;
    sprite->frame_width = frame_width;
    sprite->frame_height = frame_height;
    sprite->active_animation = NULL;
    sprite->next_animation = NULL;
    return 0;
}

void cleanup_sprite(struct sprite* sprite)
{
    sprite->active_animation = NULL;
}

void draw_sprite_frame(struct sprite* sprite, int x, int y, int frame)
{
    struct rectangle r;
    r.w = sprite->frame_width;
    r.h = sprite->frame_height;
    int cols = sprite->image->width / sprite->frame_width;

    int col = frame % cols;
    int row = frame / cols;

    r.x = col * sprite->frame_width;
    r.y = row * sprite->frame_height;
    draw_image(sprite->image, x, y, &r, 0.0);
}

int draw_sprite(struct sprite* sprite, int x, int y)
{
    int frame;
    frame = sprite->active_animation == NULL ? 0
        : sprite->active_animation->frames[sprite->current_frame].frame;
    draw_sprite_frame(sprite, x, y, frame);
    return frame;
}

struct sprite* create_sprite(struct image* image, int w, int h)
{
    struct sprite* sprite = malloc(sizeof(struct sprite));
    if (sprite != NULL && prepare_sprite(sprite, image, w, h) == -1) {
        free(sprite);
        return NULL;
    }
    return sprite;
}

void destroy_sprite(struct sprite* sprite)
{
    if (sprite != NULL) {
        cleanup_sprite(sprite);
        free(sprite);
    }
}

static void consume_elapsed_time(struct sprite* sprite,
                                 void (*progression)(struct sprite*))
{
    struct animation* animation = sprite->active_animation;
    int cfd = animation->frames[sprite->current_frame].duration;
    while (sprite->elapsed_frame >= cfd && cfd > 0) {
        sprite->elapsed_frame -= cfd;
        progression(sprite);
        cfd = animation->frames[sprite->current_frame].duration;
    }
}

static void progress_current_animation(struct sprite* sprite)
{
    struct animation* animation = sprite->active_animation;
    switch (sprite->active_animation->mode) {
        case LOOP_FRAMES:
            sprite->current_frame = sprite->current_frame == animation->loop_to
                                    ? animation->loop_from
                                    : sprite->current_frame + 1;
            break;
        case FREEZE_LAST_FRAME:
            sprite->current_frame =
            sprite->current_frame + 1 == animation->n_frames
            ? sprite->current_frame
            : sprite->current_frame + 1;
        case PINGPONG_FRAMES:
        default:
            sprite->current_frame = sprite->current_frame;
    }
}

static void consume_current_animation(struct sprite* sprite)
{
    struct animation* animation = sprite->active_animation;
    switch (sprite->active_animation->mode) {
        case LOOP_FRAMES:
            if (sprite->current_frame <= animation->loop_to)
                sprite->current_frame = animation->loop_to + 1;
            else
                sprite->current_frame += 1;
            break;
        case FREEZE_LAST_FRAME:
        case PINGPONG_FRAMES:
        default:
            break;
    }
}

void* animate_sprite(struct sprite* sprite, uint32_t elapsed)
{
    void* ret = NULL;
    struct animation* animation = sprite->active_animation;
    if (animation != NULL) {
        sprite->elapsed_frame += elapsed;
        if (sprite->elapsed_frame >=
            animation->frames[sprite->current_frame].duration) {
            if (sprite->next_animation == NULL) {
                consume_elapsed_time(sprite, progress_current_animation);
            } else {
                if (sprite->current_frame + 1 < animation->n_frames) {
                    consume_elapsed_time(sprite, consume_current_animation);
                }
                if (sprite->current_frame + 1 >= animation->n_frames) {
                    sprite->active_animation = sprite->next_animation;
                    sprite->next_animation = NULL;
                    sprite->current_frame = 0;
                    sprite->elapsed_frame = 0;
                }
            }
            ret =
            sprite->active_animation->frames[sprite->current_frame].userdata;
        }
    }
    return ret;
}

void play_animation(struct sprite* sprite, struct animation* animation)
{
    if (sprite->active_animation != animation &&
        sprite->next_animation != animation) {
        if (sprite->active_animation != NULL) {
            sprite->next_animation = animation;
        } else {
            sprite->active_animation = animation;
            sprite->next_animation = NULL;
            sprite->current_frame = 0;
            sprite->elapsed_frame = 0;
        }
    }
}

void stop_animation(struct sprite* sprite)
{
    sprite->next_animation = NULL;
    sprite->active_animation = NULL;
    sprite->current_frame = 0;
    sprite->elapsed_frame = 0;
}
