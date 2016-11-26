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
#ifndef UTILS_H_EZIL3YD2
#define UTILS_H_EZIL3YD2

#include <math.h>

#include "begin_prefix.h"
/*
 * M A T H
 */

/** 1 second is 1000 milliseconds */
#define SECOND 1000
/** n seconds are n*1000 milliseconds */
#define SECONDS 1000

static const double Pi = 3.14159265358979323846264338328;
static const double Pi_2 = 3.14159265358979323846264338328 * 2;

static __inline float max(float x, float y)
{
    return x > y ? x : y;
}

static __inline float min(float x, float y)
{
    return x < y ? x : y;
}

static __inline float clamp(float x, float bottom, float top)
{
    x = max(x, bottom);
    x = min(x, top);
    return x;
}

/*
 * D E B U G G I N G
 */

/* Set an error message
 */
#define STRINGIFY(val) #val
#define TOSTRING(val) STRINGIFY(val)
#define AT __FILE__ ":" TOSTRING(__LINE__)

/**
 * error_msg() will append an error message to the error
 * string. Cage will display the list of error messages
 * if the game state create() function fails.
 */
void error_msg(const char* msg);

/**
 * Using the ERROR() macro will add the filename and
 * line number to an error message.
 */
#define ERROR(msg) error_msg(msg " @ " AT)

/*
 * M I S C
 */

#define UNUSED(x) (void)(x)

#include "end_prefix.h"
#endif /* end of include guard: UTILS_H_EZIL3YD2 */
