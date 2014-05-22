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
#ifndef TEXTURE_H_QHWZWS5P
#define TEXTURE_H_QHWZWS5P

#include <SDL.h>
#include "utils.h"
#include "color.h"

/**
 * Images are the visual building blocks of your game.  Use images to draw on
 * screen, or as basis for sprites and fonts.  Images can be read from a file or
 * created empty and can be used to draw with or to provide frames for sprites
 * or characters for fonts.
 *
 * The simplest form of creating an image is by using create_image():
 *
 *     struct image* image;
 *     image = create_image("path/to/image.png" );
 *
 * Images can also be used to draw **on** instead of the screen:
 *
 *     draw_on_image( image );
 *     // draw images, sprites or text
 *     draw_on_screen();
 *
 * Images don't just disappear. You will have to explicitly get rid of any image
 * you create using create_image() by calling destroy_image():
 *
 *     destroy_image( image );
 *
 *  If you fail to do so, you will have a memory leak.
 */
struct image
{
    /** 
     * Images reference SDL_Textures, so you can use it to work with SDL
     * directly, should you need any extra functionality that Cage does not
     * provide.
     */
    SDL_Texture* impl;
    /** Image width in pixels */
    int width;
    /** Image height in pixels */
    int height;
};

/**
 * The image blend mode changes how an image is being drawn on the screen on or
 * another image.  This is similar to the way Gimp or Photoshop apply layers one
 * on the other.
 */
enum blend_mode {
    NONE,
    ADD,
    MULTIPLY
};

/**
 * Create and load an image using a PNG file
 * @param filepath The full path of the image file
 *
 * @return \ref image pointer or NULL on failure
 */
struct image* create_image( const char* filepath );

/**
 * Create a blank image
 * @param width The width of the blank image
 * @param height The height of the blank image
 * @param color The default color of the blank image
 *
 * @return \ref image pointer or NULL on failure
 */
struct image* create_blank_image( int width, int height, struct color color );

/**
 * Destroy an image created using create_image() or create_blank_image()
 * @param image A valid \ref image pointer created using create_image()
 */
void destroy_image( struct image* image );

/**
 * Load a image from an image file (PNG, JPG, etc..)
 * @param image A preallocated image struct
 * @param filepath The full path of the image file
 *
 * @note You don't need to use load_image() if you already used create_image()
 *
 * @return -1 on error
 */
int load_image( struct image* image, const char* filepath );

/**
 * Cleanup any initialized image resources
 * @param image Existing image to cleanup
 *
 * Cleanup will free all internally allocated resources
 * for this image, making it ready for deallocation.
 *
 * @note You don't need to use cleanup_image() if you use destroy_image()
 * 
 * @return -1 on error
 */
int cleanup_image ( struct image* image );

/**
 * Lock a image to get pixel level access
 * @param image Image to lock
 * @param pixels pointer **reference** to the image pixels lock_image() will
 * provide you with
 * @param pitch pointer to update with the pixel pitch 
 *
 * @return 0 on success or -1 on error
 */
int lock_image ( struct image* image, void** pixels, int* pitch );

/**
 * Unlock a locked image once you are done with it
 * @param image Locked image to unlock
 *
 * @return 0 on success or -1 on error
 */
int unlock_image ( struct image* image );

/**
 * Draw an image on the screen
 * @param image Image to draw
 * @param x X position
 * @param y Y position
 * @param clip Rectangle to draw
 * @param angle Rotate image in degrees
 *
 */
void draw_image ( struct image* image, 
                  int x, int y, 
                  struct rectangle* clip, 
                  double angle );

/**
 * Switch to draw on an image instead of the actual screen
 * @param image Image to draw on to
 */
void draw_on_image( struct image* image );

/**
 * Set the method to use when drawing an image
 * @param image \ref image The blend method will work for
 * @param blend_mode The blend method to apply
 */
void set_blend_mode( struct image* image, enum blend_mode blend_mode );

/**
 * Fills the entire image with a color
 * @param image Image to clear
 * @param color Color the use as fill
 */
void clear_image( struct image* image, struct color color );

#endif /* end of include guard: image */
