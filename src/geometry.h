#ifndef MATH_H_NQUPRW4D
#define MATH_H_NQUPRW4D

/**
 * 2D vector type for geometric calculation
 * and collision detection.
 */
typedef struct {
    float x;
    float y;
} vec;

/* make a new vector using x and y values */
vec xy_vec( float x, float y );
/* break a vector into x and y components */
#define VEC_XY(vec) vec.x, vec.y
/* make a new vector with x = y = 0 */
vec zero_vec( void );
/* make a new vector with x = y = 1 */
vec unit_vec( void );
/* make a new vector using a heading angle */
vec hdg_vec( float a );

/* add two vectors, returns the resulting vec */
vec add_vec( vec v1, vec v2 );
/* subtract two vectors, return the resulting vec */
vec sub_vec( vec v1, vec v2 );
/* multiply a vector by a factor, return the resulting vec */
vec mul_vec( vec v, float f );
/* divide a vector by a factor, return the resulting vec */
vec div_vec( vec v, float f ); 

/* raw (sqrd) vector length */
float vec_len_sqrd( vec v );
/* vector length (norm) */
float vec_len( vec v );
/* distance between two vectors */
float vec_dist( vec v1, vec v2 );
/* squared distance between two vectors */
float vec_dist_sqrd( vec v1, vec v2 );
/* Manhattan distance between two vectors, meaning */
/* the distance between the two vectors when following */
/* only axis-aligned directions */
float vec_dist_mntn( vec v1, vec v2 );
/* normalize a vector */
vec norm_vec( vec v );
/* swap two vectors.. */
void swap_vecs( vec* a, vec* b );

/* point is a kind of a vec */
typedef vec point;

/* bounding box is made of two points,
 * p1 - upper left
 * p2 - lower right
 */
typedef struct {
    point p1;
    point p2;
} bbox;

/* test if point is inside a bbox */
int point_in_bbox( point p, bbox b );
/* test if a bbox is inside another bbox */
int bbox_in_bbox( bbox i, bbox o );
/* test if bboxes intersect each other */
/* and return the intersection bbox */
int bbox_intersect( bbox b1, bbox b2, bbox* r );
/* move a bbox to a new position, while preserving its
 * dimensions
 */
bbox translate_bbox( bbox b, vec t );
/* returns the rectangle of an inner bbox */
struct rectangle rect_from_sub_bbox( bbox outer, bbox inner );

#endif /* end of include guard: MATH_H_NQUPRW4D */
