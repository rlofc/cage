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
#ifndef SPRITE_H_XF4APTCE
#define SPRITE_H_XF4APTCE

#include "image.h"
#include "animate.h"


/* An animatable game sprite
 * A sprite is an animatable game actor.
 * It is usually built from an image containing
 * a set of frames. 
 * To animate a sprite, you need to define
 * animations with frames and durations.
 */
struct sprite {
    /* image used to draw sprite frames */
    struct image*  image;
    /* width of each frame of the sprite */
    int            frame_width;
    /* height of each frame of the sprite */
    int            frame_height;
    /* the animation currently being played */
    struct animation* active_animation;
    /* the animation pending to be played in the next frame */
    struct animation* next_animation;
    /* currenlty played frame in the active animation */
    int current_frame;
    /* time the current frame is in display in milliseconds */
    int elapsed_frame;
};

/* allocate and initialize a new sprite
 * @screen rendering context to use
 * @pathname sprite image file
 * @w sprite frame width
 * @h sprite frame height
 *
 * @return valid sprite pointer or NULL on error
 */
struct sprite* create_sprite( struct image* image, int w, int h );


/* destroy an allocated sprite
 * @resource sprite created using <create_sprite>
 */
void destroy_sprite( struct sprite* resource );

/* Build a sprite from a sprite image file containing frame tiles.
 * @resource sprite resource to generate
 * @pathname sprite image to load
 * @frame_width width of each frame tile
 * @frame_height height of each frame tile
 *
 * @return -1 on error
 */
int prepare_sprite ( struct sprite* resource, 
                     struct image* image, int frame_width, int frame_height );

/* Free any internally allocated resources for the sprite
 * @resource sprite to cleanup
 *
 * @return -1 on error
 */
void cleanup_sprite ( struct sprite* resource );


/* Render the active frame of the sprite on the <screen>
 * @screen Rendering context
 * @resource sprite to use
 * @x x coordinates
 * @y y coordinates
 * @text text to render
 *
 * If no sprite @animation is active, the first frame will
 * be drawn.
 * If an <animation> is active, the animation animation state
 * will determine the frame to draw.
 *
 * @return -1 on error
 */
void draw_sprite ( struct screen* screen, struct sprite* resource,  int x, int y );


/* Update the sprite animation state
 * @resource sprite to animate
 * @elapsed time since last rendered frame (usually from the <context>)
 */
void* animate_sprite( struct sprite* resource, uint32_t elapsed );


/* Play a any binded sprite animation
 * @animation_id animation id, as returned from
 * <append_animation>
 *
 * **Note:** If a previous animation keyframe is not through
 * playing, the requested animation will be defered
 * until the previous keyframe is completed.
 */
void play_animation( struct sprite* resource, struct animation* animation);

#endif /* end of include guard: SPRITE_H_XF4APTCE */
