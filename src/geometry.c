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
#include "geometry.h"
#include "utils.h"
#include <math.h>

#include "begin_prefix.h"
int point_in_bbox(point p, bbox b)
{
    return ((p.x >= b.p1.x && p.x <= b.p2.x) &&
            (p.y >= b.p1.y && p.y <= b.p2.y));
}

int bbox_in_bbox(bbox i, bbox o)
{
    return point_in_bbox(i.p1, o) && point_in_bbox(i.p2, o);
}

int bbox_intersect(bbox b1, bbox b2, bbox* r)
{
    r->p1.x = max(b1.p1.x, b2.p1.x);
    r->p1.y = max(b1.p1.y, b2.p1.y);
    r->p2.x = min(b1.p2.x, b2.p2.x);
    r->p2.y = min(b1.p2.y, b2.p2.y);

    return r->p2.x > r->p1.x && r->p2.y > r->p1.y;
}

bbox translate_bbox(bbox b, vec t)
{
    vec d = sub_vec(b.p2, b.p1);
    b.p1 = t;
    b.p2 = add_vec(t, d);
    return b;
}

struct rectangle rect_from_sub_bbox(bbox outer, bbox inner)
{
    struct rectangle r;
    r.x = inner.p1.x - outer.p1.x;
    r.y = inner.p1.y - outer.p1.y;
    r.w = inner.p2.x - inner.p1.x;
    r.h = inner.p2.y - inner.p1.y;
    return r;
}
#include "end_prefix.h"
