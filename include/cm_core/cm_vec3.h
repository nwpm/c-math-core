#ifndef CM_VEC3_DOUBLE_H
#define CM_VEC3_DOUBLE_H

#include <stdbool.h>
#include "cm_types.h"

typedef struct cm_vec3_t cm_vec3_t;

void cm_vec3_copy(cm_vec3_t v, cm_vec3_t dest);
void cm_vec3_zero(cm_vec3_t v);
void cm_vec3_add(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest);
void cm_vec3_sub(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest);
void cm_vec3_scale(cm_vec3_t v, cm_real_t s, cm_vec3_t dest);
void cm_vec3_fill(cm_vec3_t v, cm_real_t val);
void cm_vec3_abs(cm_vec3_t v, cm_vec3_t dest);
void cm_vec3_max(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest);
void cm_vec3_min(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest);
void cm_vec3_rotate_x(cm_vec3_t vec, cm_real_t angle, cm_vec3_t dest);
void cm_vec3_rotate_y(cm_vec3_t vec, cm_real_t angle, cm_vec3_t dest);
void cm_vec3_rotate_z(cm_vec3_t vec, cm_real_t angle, cm_vec3_t dest);
void cm_vec3_normalize(cm_vec3_t vec, cm_vec3_t dest);
void cm_vec3_project(cm_vec3_t proj_from, cm_vec3_t proj_to, cm_vec3_t dest);
void cm_vec3_cross(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest);

cm_real_t cm_vec3_dot(cm_vec3_t a, cm_vec3_t b);
cm_real_t cm_vec3_dist_squared(cm_vec3_t a, cm_vec3_t b);
cm_real_t cm_vec3_dist(cm_vec3_t a, cm_vec3_t b);

cm_real_t cm_vec3_angle(cm_vec3_t vec_a, cm_vec3_t vec_b);
cm_real_t cm_vec3_norm(cm_vec3_t vec);
cm_real_t cm_vec3_norm_squared(cm_vec3_t vec);

bool cm_vec3_is_zero(cm_vec3_t vec);
bool cm_vec3_is_equal(cm_vec3_t vec_a, cm_vec3_t vec_b);

#endif
