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
#ifndef VEC_H_NQUPRW4D
#define VEC_H_NQUPRW4D

/**
 * 2D vector type for geometric calculation
 * and collision detection.
 */
typedef struct {
    float x;
    float y;
} vec;

/* make a new vector using x and y values */
vec xy_vec(float x, float y);
/* break a vector into x and y components */
#define VEC_XY(vec) vec.x, vec.y
/* make a new vector with x = y = 0 */
vec zero_vec(void);
/* make a new vector with x = y = 1 */
vec unit_vec(void);
/* make a new vector using a heading angle */
vec hdg_vec(float a);

/* add two vectors, returns the resulting vec */
vec add_vec(vec v1, vec v2);
/* subtract two vectors, return the resulting vec */
vec sub_vec(vec v1, vec v2);
/* multiply a vector by a factor, return the resulting vec */
vec mul_vec(vec v, float f);
/* divide a vector by a factor, return the resulting vec */
vec div_vec(vec v, float f);

/* raw (sqrd) vector length */
float vec_len_sqrd(vec v);
/* vector length (norm) */
float vec_len(vec v);
/* distance between two vectors */
float vec_dist(vec v1, vec v2);
/* squared distance between two vectors */
float vec_dist_sqrd(vec v1, vec v2);
/* Manhattan distance between two vectors, meaning */
/* the distance between the two vectors when following */
/* only axis-aligned directions */
float vec_dist_mntn(vec v1, vec v2);
/* normalize a vector */
vec norm_vec(vec v);
/* swap two vectors.. */
void swap_vecs(vec* a, vec* b);

#endif /* end of include guard: VEC_H_NQUPRW4D */
