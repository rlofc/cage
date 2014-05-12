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
#ifndef UTILS_H_EZIL3YD2
#define UTILS_H_EZIL3YD2

#include <math.h>

/* Just a simple rectangle shape for image operations
 */
struct rectangle {
    float x;
    float y;
    float h;
    float w;
};

/* Point in sub-pixel space
 */
struct point {
    float x;
    float y;
};

#define xy(X,Y) X,Y

/* cldoc:begin-category(Utilities) */
/* 1 second is 1000 milliseconds */
static int   SECOND       = 1000; 
/* n seconds are n*1000 milliseconds */
static int   SECONDS      = 1000; 

static const double Pi = 3.14159265358979323846264338328;

static __inline float max(float x, float y) {
    return x > y ? x : y;
}

static __inline float min(float x, float y) {
    return x < y ? x : y;
}

static __inline float clamp(float x, float bottom, float top) {
    x = max(x, bottom);
    x = min(x, top);
    return x;
}

static __inline float cosine_interp(float p1, float p2, float amount) {
    float m = (1-cos(amount*Pi))/2;
    return (p1*(1-m)+p2*m);
}
/* cldoc:end-category() */

#endif /* end of include guard: UTILS_H_EZIL3YD2 */
