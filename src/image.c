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
#include "image.h"
#include "screen.h"
#include "internals.h"
#include <memory.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>

int load_image(struct image* image, const char* filepath)
{
    int ret = -1;
    SDL_Surface* s = NULL;
    SDL_Surface* fs = NULL;
    uint32_t* pixels;
    int pitch;
    int npixels;
    uint32_t colorKey;
    uint32_t transparent;
    int i;

    s = IMG_Load(filepath);
    if (s == NULL) {
        ERROR("Unable to load image into an SDL surface");
        goto exit;
    }

    fs = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_RGBA8888, 0);
    if (fs == NULL) {
        ERROR("Unable to convert the image surface format");
        goto free_s;
    }

    image->impl = SDL_CreateTexture(screen->impl, SDL_PIXELFORMAT_RGBA8888,
                                    SDL_TEXTUREACCESS_STREAMING, fs->w, fs->h);
    if (image->impl == NULL) {
        ERROR("Unable to create an SDL texture from surface");
        goto free_fs;
    }

    image->width = fs->w;
    image->height = fs->h;

    SDL_SetTextureBlendMode(image->impl, SDL_BLENDMODE_BLEND);

    lock_image(image, (void*)&pixels, &pitch);
    memcpy((void*)pixels, fs->pixels, fs->pitch * fs->h);

    npixels = (pitch / 4) * fs->h;

    colorKey = SDL_MapRGB(fs->format, 0, 0xFF, 0xFF);
    transparent = SDL_MapRGBA(fs->format, 0x00, 0xFF, 0xFF, 0x00);

    for (i = 0; i < npixels; ++i) {
        if (pixels[i] == colorKey) {
            pixels[i] = transparent;
        }
    }

    unlock_image(image);
    ret = 0;

free_fs:
    SDL_FreeSurface(fs);
free_s:
    SDL_FreeSurface(s);
exit:
    return ret;
}

int cleanup_image(struct image* image)
{
    SDL_DestroyTexture(image->impl);
    image->impl = NULL;
    return 0;
}

int lock_image(struct image* image, void** pixels, int* pitch)
{
    if (SDL_LockTexture(image->impl, NULL, pixels, pitch) != 0) return -1;
    return 0;
}

int unlock_image(struct image* image)
{
    SDL_UnlockTexture(image->impl);
    return 0;
}

void draw_image(struct image* image,
                int x,
                int y,
                struct rectangle* clip,
                double angle)
{
    SDL_Rect render_quad;
    SDL_Rect sdl_clip;
    SDL_Rect* sdl_clip_ref = NULL;

    x += screen->offset_x;
    y += screen->offset_y;

    render_quad.x = x;
    render_quad.y = y;
    render_quad.w = image->width;
    render_quad.h = image->height;

    if (clip != NULL) {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
        sdl_clip.x = clip->x;
        sdl_clip.y = clip->y;
        sdl_clip.w = clip->w;
        sdl_clip.h = clip->h;
        sdl_clip_ref = &sdl_clip;
    }

    SDL_RenderCopyEx(screen->impl, image->impl, sdl_clip_ref, &render_quad,
                     angle, NULL, SDL_FLIP_NONE);
}

struct image* create_image(const char* filepath)
{
    struct image* image = malloc(sizeof(struct image));
    if (image != NULL && load_image(image, filepath) == -1) {
        free(image);
        image = NULL;
    }
    return image;
}

static struct image* _create_image(int w, int h, int access)
{
    SDL_Rect r;
    struct image* image = malloc(sizeof(struct image));
    if (image != NULL) {
        r.x = 0; r.y = 0; r.w = w; r.h = h;
        image->impl = SDL_CreateTexture(screen->impl,
                                        SDL_PIXELFORMAT_RGBA8888,
                                        access,
                                        w,
                                        h);
        if (image->impl == NULL) {
            free(image);
            image = NULL;
            ERROR("Unable to create SDL texture for blank image");
        } else {
            image->width = w;
            image->height = h;
        }
    }
    return image;
}

struct image* create_blank_image(int w, int h)
{
    return _create_image(w, h, SDL_TEXTUREACCESS_STREAMING);
}

struct image* create_target_image(int w, int h, struct color color)
{
    struct image* image;

    image = _create_image(w, h, SDL_TEXTUREACCESS_TARGET);
    if (image != NULL) {
        SDL_SetRenderTarget(screen->impl, image->impl);
        SDL_SetRenderDrawColor(screen->impl, color.red, color.green, color.blue,
                               color.alpha);
        SDL_RenderClear(screen->impl);
        SDL_SetRenderTarget(screen->impl, NULL);
    }

    return image;
}

void draw_on_image(struct image* image)
{
    int ret = SDL_SetRenderTarget(screen->impl, image->impl);
    if (ret != 0) exit(1);
}

void set_blend_mode(struct image* image, enum blend_mode blend_mode)
{
    int sdl_mode = SDL_BLENDMODE_NONE;
    switch (blend_mode) {
        case NONE:
            sdl_mode = SDL_BLENDMODE_NONE;
            break;
        case BLEND:
            sdl_mode = SDL_BLENDMODE_BLEND;
            break;
        case ADD:
            sdl_mode = SDL_BLENDMODE_ADD;
            break;
        case MULTIPLY:
            sdl_mode = SDL_BLENDMODE_MOD;
            break;
    }
    SDL_SetTextureBlendMode(image->impl, sdl_mode);
}

void clear_image(struct image* image, struct color color)
{
    int ret;
    Uint8 r, g, b, a;
    SDL_Rect rect;
    rect.x = 0; rect.y = 0; rect.w = image->width; rect.h = image->height;
    SDL_GetRenderDrawColor(screen->impl, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(screen->impl, color.red, color.green, color.blue,
                           color.alpha);
    draw_on_image(image);
    ret = SDL_RenderFillRect(screen->impl, &rect);
    if (ret != 0) exit(1);
    draw_on_screen();
    SDL_SetRenderDrawColor(screen->impl, r, g, b, a);
}

void set_image_alpha(struct image* image, uint8_t alpha)
{
    SDL_SetTextureAlphaMod(image->impl, alpha);
}

uint8_t get_image_alpha(struct image* image)
{
    Uint8 a;
    SDL_GetTextureAlphaMod(image->impl, &a);
    return a;
}

void destroy_image(struct image* image)
{
    free(image);
}

static uint32_t get_pixel32(uint32_t* pixels, int pitch, int x, int y)
{
    return pixels[(y * (pitch / 4)) + x];
}

int pixels_collide(struct image* img1,
                   struct rectangle* rect1,
                   struct image* img2,
                   struct rectangle* rect2)
{
    uint32_t* pixels1;
    uint32_t* pixels2;
    int pitch1, pitch2;
    int x1, y1, x2, y2;
    int collide = 0;
    if (lock_image(img1, (void**)&pixels1, &pitch1) == -1) {
        ERROR("Unable to lock img1");
        collide = -1;
        goto done;
    }
    if (lock_image(img2, (void**)&pixels2, &pitch2) == -1) {
        ERROR("Unable to lock img2");
        collide = -1;
        goto done;
    }
    for (y1 = rect1->y, y2 = rect2->y; y1 < rect1->y + rect1->h; y1++, y2++) {
        for (x1 = rect1->x, x2 = rect2->x; x1 < rect1->x + rect1->w;
             x1++, x2++) {
            uint32_t pix1 = get_pixel32(pixels1, pitch1, x1, y1);
            uint32_t pix2 = get_pixel32(pixels2, pitch2, x2, y2);
            pix1 = pix1 & 0x000000ff;
            pix2 = pix2 & 0x000000ff;
            if (pix1 > 0 && pix2 > 0) {
                collide = 1;
                goto done;
            }
        }
    }
done:
    unlock_image(img1);
    unlock_image(img2);
    return collide;
}
