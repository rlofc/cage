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

/* Use images to draw on screen, or as basis for sprites and fonts.
 * Images can be read from a file or created empty and can be used to draw
 * or to provide frames for sprites or characters for fonts.
 *
 * The simplest form of creating an image is by using <create_image>:
 *
 *     struct image* image;
 *     image = create_image("path/to/image.png" );
 *
 * Images can also be used to draw **on** instead of the screen:
 *
 *     draw_on_image( image );
 *     ...
 *     draw_on_screen();
 *
 * Images don't just disappear. You will have to explicitly
 * get rid of any image you create using <create_image> by calling
 * <destroy_image>:
 *
 *     destroy_image( image );
 *
 *  Otherwise, you will have a memory leak.
 */
struct image
{
    /* internal sdl representation */
    SDL_Texture* impl;
    /* texture width */
    int width;
    /* texture height */
    int height;
};

/* cldoc:begin-category(Constants) */
/* Image blending mode
 * Setting the blend mode changes how an image
 * is being drawn on the screen on or another image.
 * This is similar to the way Gimp or Photoshop apply layers
 * one on the other.
 */
enum blend_mode {
    NONE,
    ADD,
    MULTIPLY
};
/* cldoc:end-category() */

/* Create a ready to use image
 * @filepath The full path of the image file
 *
 * @return <image> pointer or NULL on failure
 */
struct image* create_image( const char* filepath );

/* Create a blank image
 * @width The width of the blank image
 * @height The height of the blank image
 * @color The default color of the blank image
 *
 * @return <image> pointer or NULL on failure
 */
struct image* create_blank_image( int width, int height, struct color color );

/* Destroy a created image
 * @image A valid <image> pointer created using <create_image>
 */
void destroy_image( struct image* image );

/* Load a image from an image file (PNG, JPG, etc..)
 * @image Already allocated image resource
 * @filepath The full path of the image file
 *
 * @return -1 on error
 */
int load_image( struct image* image, const char* filepath );

/* Cleanup an initialized image resource
 * @image Loaded image to cleanup
 *
 * Cleanup will free all internally allocated resources
 * for this image.
 * 
 * @return -1 on error
 */
int cleanup_image ( struct image* image );

/* Lock a image to get pixel level access
 * @image Image to lock
 * @pixels pointer to update with the pixels pointer
 * @pitch pointer to update with the pixel pitch 
 *
 * @return 0 on success or -1 on error
 */
int lock_image ( struct image* image, void** pixels, int* pitch );

/* Unlock a locked image once your done with it
 * @image Locked image to unlock
 *
 * @return 0 on success or -1 on error
 */
int unlock_image ( struct image* image );

/* Draw an image on the screen
 * @image Image to draw
 * @x X position
 * @y Y position
 * @clip Rectangle to draw
 * @angle Rotate image in degrees
 *
 */
void draw_image ( struct image* image, 
                  int x, int y, 
                  struct rectangle* clip, 
                  double angle );

/* Switch to draw on an image instead of the actual screen
 * @image Image to draw on to
 */
void draw_on_image( struct image* image );

/* Set the method to use when drawing an image
 * @image <image> The blend method will work for
 * @blend_mode The blend method to apply
 */
void set_blend_mode( struct image* image, enum blend_mode blend_mode );

/* Fills the entire image with a color
 * @image Image to clear
 * @color Color the use as fill
 */
void clear_image( struct image* image, struct color color );

#endif /* end of include guard: image */
