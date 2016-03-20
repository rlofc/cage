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
#ifndef FILE_H_KV23ASZC
#define FILE_H_KV23ASZC
#include "types.h"
/**
 * You can use files to store your players score, progress and settings.
 * Various platforms have restrictions on where you can store your game
 * files and SDL (and so, CAGE as well) has the functionality to handle this.
 */
struct file_spec
{
    /**
     * Use file_spec to provide CAGE with the information required to read
     * and write files: Your company name (or any other identifier you use),
     * your game name and the filename.
     */
    const char* company;
    const char* game;
    const char* filename;
};

/**
 * Read the full file content and store in a new buffer. Buffer is allocated
 * by the read_file and must be freed by the caller.
 * @param buf a buffer that will hold the entire file content. To be freed
 * by the caller.
 * @param file_spec the file specifier to use for reading.
 *
 * @return number of bytes read or -1 on error.
 */
int read_file(char** buf,
              struct file_spec file_spec);

/**
 * Write the full content of buf to a file. File will be rewritten.
 * @param file_spec file specifier to use for writing.
 * @param buf buf with the content to write.
 *
 * @return number of bytes written or -1 on error.
 */
int write_file(struct file_spec file_spec,
               const char* buf);

/**
 * Check is a file already exists.
 * @param file_spec file specifier to check.
 *
 * @return true if the file is there or false if it isn't.
 */
bool is_file_exists(struct file_spec file_spec);

#endif /* end of include guard: FILE_H_KV23ASZC*/
