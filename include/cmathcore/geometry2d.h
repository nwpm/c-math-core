#ifndef CM_GEOMETRY2D_H
#define CM_GEOMETRY2D_H

#include "cm_vec2.h"

typedef struct cm_line2d_t cm_line2d_t;
typedef struct cm_ray2d_t cm_ray2d_t;
typedef struct cm_segment2d_t cm_segment2d_t;
typedef struct cm_circle2d_t cm_circle2d_t;
typedef struct CmAABB2D CmAABB2D;
typedef struct CmTriangle2D CmTriangle2D;

/* Line */

/* Create 2d line from two points */
cm_line2d_t cm_line2d_from_points(cm_vec2_t a, cm_vec2_t b);

/* Get distance from 2d line to point */
double cm_line2d_distance_point(cm_line2d_t l, cm_vec2_t p);

/* Get the intersection point of a perpendicular and a line */
cm_vec2_t cm_line2d_project_point(cm_line2d_t l, cm_vec2_t p);

/* Get intersection point of 2 lines */
bool cm_line2d_intersect_line(cm_line2d_t l1, cm_line2d_t l2, cm_vec2_t *out);

/* Get intersection points of line and circle */
bool cm_line2d_intersect_circle(cm_line2d_t l, cm_circle2d_t c, cm_vec2_t *out1,
                                cm_vec2_t *out2);

/* TODO: Get intersection points of line and aabb */
bool cm_line2d_intersect_aabb(CmAABB2D box, cm_line2d_t line, cm_vec2_t *out1,
                              cm_vec2_t *out2);

/* Ray */

/* Create 2d ray by origin and direction */
cm_ray2d_t cm_ray2d_from_points(cm_vec2_t origin, cm_vec2_t through);

/* Get point on the ray */
cm_vec2_t cm_ray2d_point(cm_ray2d_t r, double t);

/* Get distance from 2d line to point */
double cm_ray2d_distance_point(cm_ray2d_t r, cm_vec2_t p);

/* Get intersection point of ray and line */
bool cm_ray2d_intersect_line(cm_ray2d_t r, cm_line2d_t l, cm_vec2_t *out);

/* Get intersection point of ray and segment */
bool cm_ray2d_intersect_segment(cm_ray2d_t r, cm_segment2d_t s, cm_vec2_t *out);

/* Get intersection point of circle and ray */
bool cm_ray2d_intersect_circle(cm_ray2d_t r, cm_circle2d_t c, cm_vec2_t *out1,
                               cm_vec2_t *out2);

/* TODO: Get intersection points of ray and aabb */
bool cm_ray2d_intersect_aabb(CmAABB2D box, cm_ray2d_t r, cm_vec2_t *out1,
                             cm_vec2_t *out2);

/* Segment */

/* Create 2d segment from 2 points */
cm_segment2d_t cm_segment2d_from_points(cm_vec2_t a, cm_vec2_t b);

/* Get distance from 2d segment to point */
double cm_segment2d_distance_point(cm_segment2d_t s, cm_vec2_t p);

/* Get midpoint of segment */
cm_vec2_t cm_segment2d_midpoint(cm_segment2d_t s);

/* Get segment length */
double cm_segment2d_length(cm_segment2d_t s);

/* Get intersection point of 2 segments */
bool cm_segment2d_intersect_segment(cm_segment2d_t s1, cm_segment2d_t s2,
                                    cm_vec2_t *out);

/* Get intersection point of circle and segment */
bool cm_segment2d_intersect_circle(cm_segment2d_t s, cm_circle2d_t c,
                                   cm_vec2_t *out1, cm_vec2_t *out2);

/* TODO: Get intersection points of segment and aabb */
bool cm_segment2d_intersect_aabb(CmAABB2D box, cm_segment2d_t s,
                                 cm_vec2_t *out1, cm_vec2_t *out2);

/* Circle */

/* Create circle from center and radius */
cm_circle2d_t cm_circle2d_make(cm_vec2_t center, double r);

/* Check is point belongs to the circle */
bool cm_circle2d_contains_point(cm_circle2d_t c, cm_vec2_t p);

/* Get area of circle */
double cm_circle2d_area(cm_circle2d_t c);

/* Get circumference */
double cm_circle2d_circumference(cm_circle2d_t c);

/* Get intersection point of two circles */
bool cm_circle2d_intersect_circle(cm_circle2d_t c1, cm_circle2d_t c2,
                                  cm_vec2_t *out1, cm_vec2_t *out2);

/* TODO: Get intersection point of circle and aabb */
bool cm_circle2d_intersect_aabb(cm_circle2d_t c, CmAABB2D ab, cm_vec2_t *out1,
                                cm_vec2_t *out2);

/* Triangle */

/* Create triangle */
CmTriangle2D cm_triangle2d_make(cm_vec2_t p1, cm_vec2_t p2,
                                cm_vec2_t p3);

/* Get area of triangle */
double cm_triangle2d_area(CmTriangle2D t);

/* Get triangle centroid */
cm_vec2_t cm_triangle2d_centroid(CmTriangle2D t);

/* Check if a given point belongs to a triangle */
bool cm_triangle2d_contains_point(CmTriangle2D t, cm_vec2_t p);

/* Get circumcircle of triangle */
cm_circle2d_t cm_triangle2d_circumcircle(CmTriangle2D t);

/* Get incircle of triangle */
cm_circle2d_t cm_triangle2d_incircle(CmTriangle2D t);

/* Axis-aligned bounding box */

/* Create AABB from min - a and max - b points */
CmAABB2D cm_aabb2d_from_points(cm_vec2_t a, cm_vec2_t b);

/* Check if a given point belongs to a AABB */
bool cm_aabb2d_contains_point(CmAABB2D b, cm_vec2_t p);

/* Get AABB area */
double cm_aabb2d_area(CmAABB2D b);

/* Get AABB edge */
cm_segment2d_t cm_aabb2d_edge(CmAABB2D b, int index);

/* Get AABB center */
cm_vec2_t cm_aabb2d_center(CmAABB2D b);

/* Expand AABB border */
void cm_aabb2d_expand(CmAABB2D b, cm_vec2_t new_max);

#endif
