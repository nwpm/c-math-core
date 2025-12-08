#ifndef CM_GEOMETRY2D_INTERNAL_H
#define CM_GEOMETRY2D_INTERNAL_H

#include "../vectors/cm_vec2_double_internal.h"

// TODO: cm_ray_intersect_aabb
// TODO: cm_segment_intersect_aabb
// TODO: cm_circle_distance_point
// TODO: cm_circle_aabb
// TODO: cm_triangle_aabb
// TODO: cm_triangle_intersect_circle
// TODO: cm_triangle_intersect_segment
// TODO: cm_aabb_intersect_aabb
// TODO: cm_aabb_intersect_circle
// TODO: cm_aabb_merge

typedef struct CmLine2D {

  CmVec2Double origin;
  CmVec2Double direction;

} CmLine2D;

typedef struct CmRay2D {

  CmVec2Double origin;
  CmVec2Double direction;

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

#endif
