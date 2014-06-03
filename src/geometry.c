#include "geometry.h"
#include "utils.h"
#include <math.h>

vec xy_vec( float x, float y )
{
    vec v;
    v.x = x; v.y = y;
    return v;
}

vec zero_vec( void )
{
    return xy_vec( 0, 0 );
}

vec unit_vec( void )
{
    return xy_vec( 1, 1 );
}

vec hdg_vec( float a )
{
    return xy_vec( cos( a ), sin( a ) ); 
}

vec add_vec( vec v1, vec v2 )
{
    vec v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    return v;
}

vec sub_vec( vec v1, vec v2 )
{
    vec v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    return v;
}

vec mul_vec( vec v, float f )
{
    v.x *= f;
    v.y *= f;
    return v;
}

vec div_vec( vec v, float f )
{
    v.x /= f;
    v.y /= f;
    return v;
}

float vec_len_sqrd(vec v) {
    float len = 0.0;
    len += v.x * v.x;
    len += v.y * v.y;
    return len;
}

float vec_len( vec v )
{
    return sqrt( vec_len_sqrd( v ) );
}

float vec_dist( vec v1, vec v2 )
{
    return sqrt(vec_dist_sqrd(v1, v2));
}

float vec_dist_sqrd( vec v1, vec v2 )
{
    return (v1.x - v2.x) * (v1.x - v2.x) +
           (v1.y - v2.y) * (v1.y - v2.y);
}

float vec_dist_mntn( vec v1, vec v2 )
{
    return fabs(v1.x - v2.x) + fabs(v1.y - v2.y);
}

vec norm_vec( vec v )
{
    float len = vec_len( v );
    return div_vec( v, len );
}

int point_in_bbox( point p, bbox b )
{
    return ( ( p.x >= b.p1.x && p.x <= b.p2.x ) &&
             (  p.y >= b.p1.y && p.y <= b.p2.y) );
}

int bbox_in_bbox( bbox i, bbox o ) {
    return point_in_bbox( i.p1, o ) &&
           point_in_bbox( i.p2, o );
}

int bbox_intersect( bbox b1, bbox b2, bbox* r )
{
    r->p1.x = max( b1.p1.x, b2.p1.x );
    r->p1.y = max( b1.p1.y, b2.p1.y );
    r->p2.x = min( b1.p2.x, b2.p2.x );
    r->p2.y = min( b1.p2.y, b2.p2.y );

    return r->p2.x > r->p1.x && r->p2.y > r->p1.y;
}

struct rectangle rect_from_sub_bbox( bbox outer, bbox inner )
{
    struct rectangle r;
    r.x = inner.p1.x - outer.p1.x;
    r.y = inner.p1.y - outer.p1.y;
    r.w = inner.p2.x - inner.p1.x;
    r.h = inner.p2.y - inner.p1.y;
    return r;
}

