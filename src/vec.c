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
#include "vec.h"
#include <math.h>

vec xy_vec(float x, float y)
{
    vec v;
    v.x = x;
    v.y = y;
    return v;
}

vec zero_vec(void)
{
    return xy_vec(0, 0);
}

vec unit_vec(void)
{
    return xy_vec(1, 1);
}

vec hdg_vec(float a)
{
    return xy_vec(cos(a), sin(a));
}

vec add_vec(vec v1, vec v2)
{
    vec v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

vec sub_vec(vec v1, vec v2)
{
    vec v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

vec mul_vec(vec v, float f)
{
    v.x *= f;
    v.y *= f;
    return v;
}

vec div_vec(vec v, float f)
{
    v.x /= f;
    v.y /= f;
    return v;
}

float vec_len_sqrd(vec v)
{
    float len = 0.0;
    len += v.x * v.x;
    len += v.y * v.y;
    return len;
}

float vec_len(vec v)
{
    return sqrt(vec_len_sqrd(v));
}

float vec_dist(vec v1, vec v2)
{
    return sqrt(vec_dist_sqrd(v1, v2));
}

float vec_dist_sqrd(vec v1, vec v2)
{
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

float vec_dist_mntn(vec v1, vec v2)
{
    return fabs(v1.x - v2.x) + fabs(v1.y - v2.y);
}

vec norm_vec(vec v)
{
    float len = vec_len(v);
    return div_vec(v, len);
}

void swap_vecs(vec* a, vec* b)
{
    vec tmp = *a;
    a->x = b->x;
    a->y = b->y;
    b->x = tmp.x;
    b->y = tmp.y;
}
