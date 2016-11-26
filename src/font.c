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
#include "font.h"
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_surface.h"

#include "begin_prefix.h"
/* -----------------------------------------------
 * Thanks to the Lazy Foo' Production tutorial at
 * http://lazyfoo.net/SDL_tutorials/lesson30/
 * -----------------------------------------------
 */
static uint32_t get_pixel32(uint32_t* pixels, int pitch, int x, int y)
{
    return pixels[(y * (pitch / 4)) + x];
}

int load_font(struct font* font, const char* filepath, int ncols, int nrows)
{
    uint32_t* pixels = NULL;
    int pitch = 0;
    uint32_t bg_color;
    int cell_w, cell_h, top, base_a, curr_char;
    int rows;
    int i;

    if (init_image_from_file(&font->image, filepath) == -1) return -1;
    if ((font->image.width / ncols) * (font->image.height / nrows) >
        MAX_FONT_CHARS)
        return -1;
    if (lock_image(&font->image, (void**)&pixels, &pitch) == -1) return -1;

    bg_color = pixels[0];

    cell_w = font->image.width / ncols;
    cell_h = font->image.height / nrows;

    top = cell_h;
    base_a = cell_h;

    curr_char = 0;

    for (rows = 0; rows < nrows; ++rows) {
        int cols;
        for (cols = 0; cols < ncols; ++cols) {
            int p_col, p_row;
            font->chars_rects[curr_char].x = cell_w * cols;
            font->chars_rects[curr_char].y = cell_h * rows;

            font->chars_rects[curr_char].w = cell_w;
            font->chars_rects[curr_char].h = cell_h;

            for (p_col = 0; p_col < cell_w; ++p_col) {
                for (p_row = 0; p_row < cell_h; ++p_row) {
                    int px = (cell_w * cols) + p_col;
                    int py = (cell_h * rows) + p_row;

                    if (get_pixel32(pixels, pitch, px, py) != bg_color) {
                        font->chars_rects[curr_char].x = px;
                        p_col = cell_w;
                        p_row = cell_h;
                    }
                }
            }

            for (p_col = cell_w - 1; p_col >= 0; --p_col) {
                for (p_row = 0; p_row < cell_h; ++p_row) {
                    int px = (cell_w * cols) + p_col;
                    int py = (cell_h * rows) + p_row;

                    if (get_pixel32(pixels, pitch, px, py) != bg_color) {
                        font->chars_rects[curr_char].w =
                        (px - font->chars_rects[curr_char].x) + 1;
                        p_col = -1;
                        p_row = cell_h;
                    }
                }
            }

            for (p_row = 0; p_row < cell_h; ++p_row) {
                for (p_col = 0; p_col < cell_w; ++p_col) {
                    int px = (cell_w * cols) + p_col;
                    int py = (cell_h * rows) + p_row;

                    if (get_pixel32(pixels, pitch, px, py) != bg_color) {
                        if (p_row < top) {
                            top = p_row;
                        }
                        /* Break the loops */
                        p_col = cell_w;
                        p_row = cell_h;
                    }
                }
            }

            if (curr_char == 'A') {
                for (p_row = cell_h - 1; p_row >= 0; --p_row) {
                    for (p_col = 0; p_col < cell_w; ++p_col) {
                        int px = (cell_w * cols) + p_col;
                        int py = (cell_h * rows) + p_row;

                        if (get_pixel32(pixels, pitch, px, py) != bg_color) {
                            base_a = p_row;
                            p_col = cell_w;
                            p_row = -1;
                        }
                    }
                }
            }

            ++curr_char;
        }
    }

    font->space_width = cell_w / 2;
    font->line_height = base_a - top + 2;
    font->char_spacing = 0;
    font->line_spacing = 0;

    for (i = 0; i < ncols * nrows; ++i) {
        font->chars_rects[i].y += top;
        font->chars_rects[i].h -= top;
    }

    unlock_image(&font->image);
    return 0;
}

struct font* create_font(const char* filepath, int cols, int rows)
{
    struct font* f = (struct font*)malloc(sizeof(*f));
    if (f != NULL && load_font(f, filepath, cols, rows) == -1) {
        free(f);
        return NULL;
    }
    return f;
}

int cleanup_font(struct font* font)
{
    return cleanup_image(&font->image);
}

void destroy_font(struct font* font)
{
    if (font != NULL) {
        cleanup_font(font);
        free(font);
    }
}

void draw_text(struct font* font, const char* text, int x, int y)
{
    int curX = x, curY = y;
    unsigned int i;
    for (i = 0; i < strlen(text); ++i) {
        switch (text[i]) {
            case ' ':
                curX += font->space_width;
                break;
            case '\n':
                curY += font->line_height + font->line_spacing;
                curX = x;
                break;
            default: {
                int ascii = (unsigned char)text[i];
                draw_image(&font->image, curX, curY, &font->chars_rects[ascii],
                           0.0);
                curX += font->chars_rects[ascii].w + font->char_spacing;
            }
        }
    }
}

void measure_text(struct font* font, const char* text, int* width, int* height)
{
    unsigned int i;
    int ascii;
    int w = *width = *height = 0;
    for (i = 0; i < strlen(text); ++i) {
        switch (text[i]) {
            case ' ':
                w += font->space_width;
                break;
            case '\n':
                if (*width < w) *width = w;
                w = 0;
                *height += font->line_height + font->line_spacing;
                break;
            default:
                ascii = (unsigned char)text[i];
                w += font->chars_rects[ascii].w + font->char_spacing;
        }
    }
    if (*width < w) *width = w;
    *height += font->line_height;
}
#include "end_prefix.h"
