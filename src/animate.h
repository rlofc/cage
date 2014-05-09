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
#ifndef ANIMATE_H_QVL0GFIR
#define ANIMATE_H_QVL0GFIR

#define MAX_FRAMES_PER_ANIMATION 256

/* Animation frames and durations for a sprite.
 * You may use the same animation definition
 * for any number of sprites:
 *
 *     struct animation* walk = create_animation();
 *
 *     add_frame( walk, 0, 50, NULL );
 *     add_frame( walk, 1, 100, NULL );
 *     add_frame( walk, 2, 50,NULL );
 *
 *     ...
 *     play_animation( zombie, walk );
 *     ...
 *     play_animation( robot, walk );
 *
 *
 * You may also associate custom data with specific
 * key frames. 
 *
 */
struct animation {
    /* frames */
    struct {
        /* frame number (top-left frame is 0) */
        int frame;
        /* duration of frame in milliseconds */
        int duration;
        /* user data */
        void* userdata;
    } frames[MAX_FRAMES_PER_ANIMATION];
    /* number of frames for this animation */
    int n_frames;

    /* Animation playback mode */
    enum animation_mode {
        /* Loop back to <loop_from> */
        LOOP_FRAMES,
        /* go back in reverse and then return endlessly */
        PINGPONG_FRAMES,
        /* stop at the last frame */
        FREEZE_LAST_FRAME
    } mode;

    /* when mode is LOOP_FRAMES, where to loop from */
    int loop_from;
    int loop_to;
};



/* Create a new animation
 */
struct animation* create_animation(void);

/* Destory a previously created animation
 */
void destroy_animation(struct animation* animation);

/* Add a new frame to an animation
 */
void add_frame( struct animation* animation, int index_in_sprite, int duration, void* userdata);

#endif /* end of include guard: ANIMATE_H_QVL0GFIR */
