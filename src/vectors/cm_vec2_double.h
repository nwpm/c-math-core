#ifndef CM_VEC2_DOUBLE_H
#define CM_VEC2_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

#include "../utils/cm_err_codes.h"

// TODO: Hide struct
typedef struct CmVec2Double {
  double x;
  double y;
} CmVec2Double;

/* Allocation */
CmVec2Double *cm_vec2_double_alloc();
CmVec2Double *cm_vec2_double_init(double x, double y);
CmVec2Double *cm_vec2_double_create_from_vec(CmVec2Double *orig_vec);

void cm_vec2_double_free(CmVec2Double *vec);

/* Operations */
CmStatusCode cm_vec2_double_sum(CmVec2Double *vec_a, const CmVec2Double *vec_b);
CmStatusCode cm_vec2_double_sub(CmVec2Double *vec_a, const CmVec2Double *vec_b);
CmStatusCode cm_vec2_double_scale(CmVec2Double *vec, double scale);

CmStatusCode cm_vec2_double_dot(const CmVec2Double *vec_a,
                                const CmVec2Double *vec_b, double *res);
CmStatusCode cm_vec2_double_angle(const CmVec2Double *vec_a,
                                  const CmVec2Double *vec_b, double *angle);

bool cm_vec2_double_is_null(const CmVec2Double *vec);
bool cm_vec2_double_is_equal(const CmVec2Double *vec_a,
                             const CmVec2Double *vec_b);

CmVec2Double *cm_vec2_double_perpendicular(const CmVec2Double *vec);
CmVec2Double *cm_vec2_double_rotate(const CmVec2Double *vec, double angle);
CmVec2Double *cm_vec2_double_cross(const CmVec2Double *vec_a,
                                   const CmVec2Double *vec_b);

/* Norm */
double cm_vec2_double_norm(const CmVec2Double *vec);
double cm_vec2_double_norm_squared(const CmVec2Double *vec);
double cm_vec2_double_distance(const CmVec2Double *vec_a,
                               const CmVec2Double *vec_b);

/* Normalize */
CmVec2Double *cm_vec2_double_normalize(const CmVec2Double *vec);

/* Project */
CmVec2Double *cm_vec2_double_project(const CmVec2Double *proj_from,
                                     const CmVec2Double *proj_to);

/* Reflect */
CmVec2Double *cm_vec2_double_reflect(const CmVec2Double *vec);

/* Lerp */
CmVec2Double *cm_vec2_double_lerp(const CmVec2Double *start,
                                  const CmVec2Double *end, double t);

/* Setter */
static inline void cm_vec2_double_set_x(CmVec2Double *vec, double x_val) {
  vec->x = x_val;
}

static inline void cm_vec2_double_set_y(CmVec2Double *vec, double y_val) {
  vec->y = y_val;
}

/* Getter */
static inline double cm_vec2_double_get_x(CmVec2Double *vec) { return vec->x; }

static inline double cm_vec2_double_get_y(CmVec2Double *vec) { return vec->y; }

#endif
