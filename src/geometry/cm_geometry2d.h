#ifndef CM_GEOMETRY2D_H
#define CM_GEOMETRY2D_H

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
CmLine2D cm_line2d_from_points(CmVec2Double v1, CmVec2Double v2);

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

/* Get intersection points of line and aabb */
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


/* Circle */

/* Triangle */

/* Axis-aligned bounding box */

#endif
