#ifndef CM_GEOMETRY2D_INTERNAL_H
#define CM_GEOMETRY2D_INTERNAL_H

#include "../vectors/cm_vec2_internal.h"

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

typedef struct cm_line2d_t {

  cm_vec2_t origin;
  cm_vec2_t direction;

} cm_line2d_t;

typedef struct cm_ray2d_t {

  cm_vec2_t origin;
  cm_vec2_t direction;

} cm_ray2d_t;

typedef struct cm_segment2d_t {

  cm_vec2_t a;
  cm_vec2_t b;

} cm_segment2d_t;

typedef struct cm_circle2d_t {

  cm_vec2_t center;
  double radius;

} cm_circle2d_t;

typedef struct cm_aabb2d_t {

  cm_vec2_t min;
  cm_vec2_t max;

} cm_aabb2d_t;

typedef struct cm_triangle2d_t {

  cm_vec2_t a;
  cm_vec2_t b;
  cm_vec2_t c;
} cm_triangle2d_t;

#endif
