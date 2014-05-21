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
#ifndef FONT_H_XYTHJIBT
#define FONT_H_XYTHJIBT

#include "utils.h"
#include "image.h"

/**
 * Use bitmap fonts to draw text 
 * Bitmap fonts are made from images with a
 * matrix of characters in ascii order.
 */
struct font {
    /** font characters image */
    struct image     image;
    /** SDL character boundries */
    struct rectangle chars[ 256 ];
    /** size of new line */
    int              newline;
    /** size of space */
    int              space;
};

/**
 * Create a new font from an image file
 * @param filepath Image to use for font
 * @param cols Number of columns in the font bitmap image.
 * @param rows Number of rows in the font bitmap image.
 *
 * @return New font, ready to use
 */
struct font* create_font( const char* filepath, int cols, int rows );

/**
 * Destory an existing font
 * @param font Font to cleanup and deallocate
 */
void destroy_font( struct font* font );

/**
 * Build a font from a font image file containing 16x16 (256) characters
 * @param font Font resource to generate
 * @param filepath font image to load
 * @param cols Number of columns in the font bitmap
 * @param rows Number of rows in the font bitmap
 *
 * @return -1 on error
 */
int load_font ( struct font* font, const char* filepath, int cols, int rows );

/**
 * Free any internally allocated resources for the font
 * @param font Font to cleanup
 *
 * @return -1 on error
 */
int cleanup_font ( struct font* font );

/**
 * Use font to render text
 * @param font Font to use
 * @param text text to render
 * @param x x coordinates
 * @param y y coordinates
 *
 * @return -1 on error
 */
void draw_text ( struct font* font, const char* text, int x, int y);

#endif /* end of include guard: FONT_H_XYTHJIBT */
