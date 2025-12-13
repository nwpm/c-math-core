#ifndef CM_VEC2_H
#define CM_VEC2_H

#include <stdbool.h>
#include "cm_types.h"

typedef struct cm_vec2_t cm_vec2_t;

void cm_vec2_copy(cm_vec2_t v, cm_vec2_t dest);
void cm_vec2_zero(cm_vec2_t v);
void cm_vec2_add(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);
void cm_vec2_sub(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);
void cm_vec2_scale(cm_vec2_t v, cm_real_t s, cm_vec2_t dest);
void cm_vec2_fill(cm_vec2_t v, cm_real_t val);
void cm_vec2_abs(cm_vec2_t v, cm_vec2_t dest);
void cm_vec2_max(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);
void cm_vec2_min(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);
void cm_vec2_rotate(cm_vec2_t vec, cm_real_t angle, cm_vec2_t dest);
void cm_vec2_normalize(cm_vec2_t vec, cm_vec2_t dest);
void cm_vec2_project(cm_vec2_t proj_from, cm_vec2_t proj_to, cm_vec2_t dest);

cm_real_t cm_vec2_dot(cm_vec2_t a, cm_vec2_t b);
cm_real_t cm_vec2_cross(cm_vec2_t a, cm_vec2_t b);
cm_real_t cm_vec2_dist_squared(cm_vec2_t a, cm_vec2_t b);
cm_real_t cm_vec2_dist(cm_vec2_t a, cm_vec2_t b);

cm_real_t cm_vec2_angle(cm_vec2_t vec_a, cm_vec2_t vec_b);
cm_real_t cm_vec2_norm(cm_vec2_t vec);
cm_real_t cm_vec2_norm_squared(cm_vec2_t vec);

bool cm_vec2_is_zero(cm_vec2_t vec);
bool cm_vec2_is_equal(cm_vec2_t vec_a, cm_vec2_t vec_b);

#endif
