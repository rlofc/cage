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
#include "file.h"
#include "SDL.h"

#define MAX_PATH_LEN 1024

static void make_game_path(char* full_path, struct file_spec file_spec)
{
    char* perf_path = SDL_GetPrefPath(file_spec.company, file_spec.game);
    strncat(full_path, perf_path, MAX_PATH_LEN);
    strncat(full_path, "/", MAX_PATH_LEN);
    strncat(full_path, file_spec.filename, MAX_PATH_LEN);
    SDL_free(perf_path);
}

bool is_file_exists(struct file_spec file_spec)
{
    char full_path[MAX_PATH_LEN + 1] = "";
    make_game_path(full_path, file_spec);
    SDL_RWops* rw = SDL_RWFromFile(full_path, "r");
    if (rw == NULL) return false;
    SDL_RWclose(rw);
    return true;
}

int read_file(char** buf, struct file_spec file_spec)
{
    char full_path[MAX_PATH_LEN + 1] = "";
    make_game_path(full_path, file_spec);
    SDL_RWops* rw = SDL_RWFromFile(full_path, "r");
    if (rw == NULL) return -1;

    Sint64 res_size = SDL_RWsize(rw);
    *buf = (char*)malloc(res_size + 1);

    Sint64 nb_read_total = 0, nb_read = 1;
    char* buf_ = *buf;
    while (nb_read_total < res_size && nb_read != 0) {
        nb_read = SDL_RWread(rw, buf_, 1, (res_size - nb_read_total));
        nb_read_total += nb_read;
        buf_ += nb_read;
    }
    SDL_RWclose(rw);
    if (nb_read_total != res_size) {
        free(*buf);
        return -1;
    }

    *buf[nb_read_total] = '\0';
    return nb_read_total;
}

int write_file(struct file_spec file_spec, const char* buf)
{
    char full_path[MAX_PATH_LEN + 1] = "";
    make_game_path(full_path, file_spec);
    SDL_RWops* rw = SDL_RWFromFile(full_path, "w");
    if (rw != NULL) {
        size_t len = SDL_strlen(buf);
        if (SDL_RWwrite(rw, buf, 1, len) != len) {
            SDL_RWclose(rw);
            return -1;
        }
        SDL_RWclose(rw);
        return len;
    } else
        return -1;
}
