#ifndef CM_VEC2_H
#define CM_VEC2_H

#include <stdbool.h>

typedef struct cm_vec2_t cm_vec2_t;

void cm_vec2_copy(cm_vec2_t v, cm_vec2_t dest);
void cm_vec2_zero(cm_vec2_t v);
void cm_vec2_add(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);
void cm_vec2_sub(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);

void cm_vec2_scale(cm_vec2_t v, float s, cm_vec2_t dest);
void cm_vec2_fill(cm_vec2_t v, float val);
void cm_vec2_abs(cm_vec2_t v, cm_vec2_t dest);
void cm_vec2_max(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);
void cm_vec2_min(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest);

float cm_vec2_dot(cm_vec2_t a, cm_vec2_t b);
float cm_vec2_cross(cm_vec2_t a, cm_vec2_t b);
float cm_vec2_dist_squared(cm_vec2_t a, cm_vec2_t b);
float cm_vec2_dist(cm_vec2_t a, cm_vec2_t b);

#endif
