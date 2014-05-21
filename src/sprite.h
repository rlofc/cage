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

/** 
 * Sprites use images sliced into frames to play short animations.
 * Sprites can be used for game characters, props, tiles and titles.
 * To create a sprite, you will need to create an image containing 
 * a set of fixed-sized frames and then pass it to create_sprite():
 *
 *     struct sprite* wizard = NULL;
 *     wizard = create_sprite( create_image( "res/wizard.png", screen ) , 32, 32);
 *     
 * Note that by creating both the sprite and the image, you are
 * responsible to the clean-up once you're done:
 *
 *     destroy_image( wizard->image );
 *     destroy_sprite( wizard );
 * 
 * To animate a sprite, you need to create /ref animation instances,
 * indicating the frames to play. To actually play an animation,
 * use play_animation():
 *
 *     play_animation( wizard, walk );
 *
 * Finally, to update the sprite animation, call animate_sprite():
 *
 *     void *data;
 *     data = animate_sprite( wizard, toolbox->stopwatch );
 *
 * Once a frame that has a user-data associated with it is played,
 * you will get the data pointer back.
 *
 */
struct sprite {
    /** image used to draw sprite frames */
    struct image*  image;
    /** width of each frame of the sprite */
    int            frame_width;
    /** height of each frame of the sprite */
    int            frame_height;
    /** the animation currently being played */
    struct animation* active_animation;
    /** the animation pending to be played in the next frame */
    struct animation* next_animation;
    /** currenlty played frame in the active animation */
    int current_frame;
    /** time the current frame is in display in milliseconds */
    int elapsed_frame;
};

/**
 * allocate and initialize a new sprite
 * @param image sprite \ref image
 * @param w sprite frame width
 * @param h sprite frame height
 *
 * @return valid sprite pointer or NULL on error
 */
struct sprite* create_sprite( struct image* image, int w, int h );

/**
 * destroy an allocated sprite
 * @param sprite sprite created using create_sprite().
 */
void destroy_sprite( struct sprite* sprite );

/**
 * Build a sprite from a sprite image file containing frame tiles.
 * @param sprite sprite resource to generate
 * @param image image containing the sprite frames.
 * @param frame_width width of each frame tile
 * @param frame_height height of each frame tile
 *
 * @return -1 on error
 */
int prepare_sprite ( struct sprite* sprite, 
                     struct image* image, int frame_width, int frame_height );

/**
 * Free any internally allocated resources for the \ref sprite
 * @param sprite \ref sprite to cleanup
 *
 * @return -1 on error
 */
void cleanup_sprite ( struct sprite* sprite );

/**
 * Draw the active frame of the sprite.
 * @param sprite sprite to use
 * @param x x coordinates
 * @param y y coordinates
 *
 * If no sprite \ref animation is active, the first frame will
 * be drawn.
 * If an \ref animation is active, the animation state
 * will determine the frame to draw.
 *
 * @return -1 on error
 */
void draw_sprite ( struct sprite* sprite,  int x, int y );

/**
 * Update the sprite animation state
 * @param sprite sprite to animate
 * @param elapsed_ms time since last rendered frame (usually elapsed_ms)
 */
void* animate_sprite( struct sprite* sprite, uint32_t elapsed_ms );

/**
 * Play a any binded sprite animation
 * @param sprite /ref sprite to use the animation for.
 * @param animation /ref animation to play. 
 *
 * @note If a previous animation keyframe is not through
 * playing, the requested animation will be defered
 * until the previous keyframe is completed.
 */
void play_animation( struct sprite* sprite, struct animation* animation);

#endif /* end of include guard: SPRITE_H_XF4APTCE */
