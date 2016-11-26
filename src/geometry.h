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
#ifndef GEOMETRY_H_NQUPRW4D
#define GEOMETRY_H_NQUPRW4D
#include "vec.h"
#include "begin_prefix.h"
/* point is a kind of a vec */
typedef vec point;
/**
 * Just a simple rectangle shape for image operations
 */
struct rectangle {
    int x;
    int y;
    int w;
    int h;
};

/**
 * Point in sub-pixel space
 */
struct coords {
    int x;
    int y;
};

#define xy(X, Y) X, Y

/* bounding box is made of two points,
 * p1 - upper left
 * p2 - lower right
 */
typedef struct {
    point p1;
    point p2;
} bbox;

/* test if point is inside a bbox */
int point_in_bbox(point p, bbox b);
/* test if a bbox is inside another bbox */
int bbox_in_bbox(bbox i, bbox o);
/* test if bboxes intersect each other */
/* and return the intersection bbox */
int bbox_intersect(bbox b1, bbox b2, bbox* r);
/* move a bbox to a new position, while preserving its
 * dimensions
 */
bbox translate_bbox(bbox b, vec t);
/* returns the rectangle of an inner bbox */
struct rectangle rect_from_sub_bbox(bbox outer, bbox inner);

#include "end_prefix.h"
#endif /* end of include guard: GEOMETRY_H_NQUPRW4D */
