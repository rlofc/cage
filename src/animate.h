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

/* Animation playback mode */
enum animation_mode {
    /* Loop back to <loop_from> */
    LOOP_FRAMES,
    /* go back in reverse and then return endlessly */
    PINGPONG_FRAMES,
    /* stop at the last frame */
    FREEZE_LAST_FRAME
};

/** Animation frame */
struct frame {
    /** frame number (top-left frame is 0) */
    int frame;
    /** duration of frame in milliseconds */
    int duration;
    /** user data */
    void* userdata;
};

/** Animation frames and durations for a sprite.
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
    struct frame frames[MAX_FRAMES_PER_ANIMATION];
    /* number of frames for this animation */
    int n_frames;
    /* Animation playback mode */
    enum animation_mode mode;
    /* when mode is LOOP_FRAMES, where to loop from */
    int loop_from;
    int loop_to;
};

/**
 * Create a new animation.
 *
 * @return New animation instance, ready to have frames
 * added using add_frame().
 */
struct animation* create_animation(void);

/**
 * Destory a previously created animation.
 * @param animation A previously created /ref animation to deallocate.
 */
void destroy_animation(struct animation* animation);

/**
 * Add a new frame to an \ref animation
 * @param animation Animation to add the frame to
 * @param index_in_sprite The frame index in the sprite frames image
 * @param duration The time in milliseconds to play this frame
 * @param userdata Any data you would like to associate with this frame
 *        You will get this data pointer back when this frame gets played
 */
void add_frame( struct animation* animation, int index_in_sprite, int duration, void* userdata);

/**
 * Add a new set of frames to an \ref animation.
 * @param animation Animation to add the frame to
 * @param nframes Number of frames to add
 * @param frames The frames to add as an array of \ref frame structs 
 */
void add_frames( struct animation* animation, int nframes, struct frame frames[] );

#endif /* end of include guard: ANIMATE_H_QVL0GFIR */
