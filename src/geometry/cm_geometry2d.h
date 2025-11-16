#ifndef CM_GEOMETRY2D_H
#define CM_GEOMETRY2D_H

#include "../utils/cm_constants.h"
#include "../vectors/cm_vec2_double.h"

// TODO: aabb intersect

/* Line defined by 2 radius vectors */
typedef struct CmLine2D {

  CmVec2Double a;
  CmVec2Double b;

} CmLine2D;

typedef struct CmRay2D {

  CmVec2Double a;
  CmVec2Double b;

} CmRay2D;

typedef struct CmSegment2D {

  CmVec2Double a;
  CmVec2Double b;

} CmSegment2D;

typedef struct CmCircle2D {

  CmVec2Double center;
  double radius;

} CmCircle2D;

typedef struct CmAABB2D {

  CmVec2Double min;
  CmVec2Double max;

} CmAABB2D;

typedef struct CmTriangle2D {

  CmVec2Double a;
  CmVec2Double b;
  CmVec2Double c;
} CmTriangle2D;

/* Line */

/* Create 2d line from two points */
CmLine2D cm_line2d_from_points(CmVec2Double a, CmVec2Double b);

/* Get distance from 2d line to point */
double cm_line2d_distance_point(CmLine2D l, CmVec2Double p);

/* Get direction of current line */
CmVec2Double cm_line2d_direction(CmLine2D l);

/* Get the intersection point of a perpendicular and a line */
CmVec2Double cm_line2d_project_point(CmLine2D l, CmVec2Double p);

/* Get intersection point of 2 lines */
bool cm_line2d_intersect_line(CmLine2D l1, CmLine2D l2, CmVec2Double *out);

/* Get intersection points of line and circle */
bool cm_line2d_intersect_circle(CmLine2D l, CmCircle2D c, CmVec2Double *out1,
                                CmVec2Double *out2);

/* TODO: Get intersection points of line and aabb */
bool cm_line2d_intersect_aabb(CmAABB2D box, CmLine2D line, CmVec2Double *out1,
                              CmVec2Double *out2);

/* Ray */

/* Create 2d ray by origin and direction */
CmRay2D cm_ray2d_from_points(CmVec2Double origin, CmVec2Double through);

/*
 * Get point on the ray
 * t >= 0
 */
CmVec2Double cm_ray2d_point(CmRay2D r, double t);

/* Get distance from 2d line to point */
double cm_ray2d_distance_point(CmRay2D r, CmVec2Double p);

/* Get intersection point of ray and line */
bool cm_ray2d_intersect_line(CmRay2D r, CmLine2D l, CmVec2Double *out);

/* Get intersection point of ray and segment */
bool cm_ray2d_intersect_segment(CmRay2D r, CmSegment2D s, CmVec2Double *out);

/* Get intersection point of circle and ray */
bool cm_ray2d_intersect_circle(CmRay2D r, CmCircle2D c, CmVec2Double *out1,
                               CmVec2Double *out2);

/* TODO: Get intersection points of ray and aabb */
bool cm_ray2d_intersect_aabb(CmAABB2D box, CmRay2D r, CmVec2Double *out1,
                             CmVec2Double *out2);

/* Segment */

/* Create 2d segment from 2 points */
CmSegment2D cm_segment2d_from_points(CmVec2Double a, CmVec2Double b);

/* Get distance from 2d segment to point */
double cm_segment2d_distance_point(CmSegment2D s, CmVec2Double p);

/* Get midpoint of segment */
CmVec2Double cm_segment2d_midpoint(CmSegment2D s);

/* Get segment length */
double cm_segment2d_length(CmSegment2D s);

/* Get intersection point of 2 segments */
bool cm_segment2d_intersect_segment(CmSegment2D s1, CmSegment2D s2,
                                    CmVec2Double *out);

/* Get intersection point of circle and segment */
bool cm_segment2d_intersect_circle(CmSegment2D s, CmCircle2D c,
                                   CmVec2Double *out1, CmVec2Double *out2);

/* TODO: Get intersection points of segment and aabb */
bool cm_segment2d_intersect_aabb(CmAABB2D box, CmSegment2D s,
                                 CmVec2Double *out1, CmVec2Double *out2);

/* Circle */

/* Create circle from center and radius */
CmCircle2D cm_circle2d_make(CmVec2Double center, double r);

/* Check is point belongs to the circle */
bool cm_circle2d_contains_point(CmCircle2D c, CmVec2Double p);

/* Get area of circle */
static inline double cm_circle2d_area(CmCircle2D c) {
  return CM_PI * (c.radius * c.radius);
}

/* Get circumference */
static inline double cm_circle2d_circumference(CmCircle2D c) {
  return 2 * CM_PI * c.radius;
}

bool cm_circle2d_intersect_circle(CmCircle2D c1, CmCircle2D c2,
                                  CmVec2Double *out1, CmVec2Double *out2);

/* Triangle */

/* Axis-aligned bounding box */

#endif
