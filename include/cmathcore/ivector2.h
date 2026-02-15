#ifndef CM_IVEC2_H
#define CM_IVEC2_H

#define CM_GET_ZERO_IVEC2 ((cm_ivec2_t){0, 0})
#define CM_GET_E1_IVEC2 ((cm_ivec2_t){1, 0})
#define CM_GET_E2_IVEC2 ((cm_ivec2_t){0, 1})

#include <stdint.h>

// TODO: SIMD optimization for module
// TODO: support all int and float types(templates C++?)
// TODO: min, max compare without if
// TODO: documentation
// TODO: Square root without std math lib

typedef struct {
  int64_t x, y;
} cm_ivec2_t;

void cm_ivec2_init(cm_ivec2_t *v, int64_t x, int64_t y);
void cm_ivec2_copy(const cm_ivec2_t src, cm_ivec2_t *dest);
void cm_ivec2_fill(cm_ivec2_t *v, int64_t val);
void cm_ivec2_set_zero(cm_ivec2_t *v);

void cm_ivec2_add(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *res);
void cm_ivec2_sub(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *res);
void cm_ivec2_scale(const cm_ivec2_t v, int64_t s, cm_ivec2_t *res);
void cm_ivec2_abs(const cm_ivec2_t v, cm_ivec2_t *res);

void cm_ivec2_add_inplace(cm_ivec2_t *a, const cm_ivec2_t b);
void cm_ivec2_sub_inplace(cm_ivec2_t *a, const cm_ivec2_t b);
void cm_ivec2_scale_inplace(cm_ivec2_t *v, int64_t s);
void cm_ivec2_abs_inplace(cm_ivec2_t* v);

float cm_ivec2_norm(const cm_ivec2_t v);
float cm_ivec2_dot_angle(const cm_ivec2_t a, const cm_ivec2_t b, float angle);
int64_t cm_ivec2_dot(const cm_ivec2_t a, const cm_ivec2_t b);
int64_t cm_ivec2_cross(const cm_ivec2_t a, const cm_ivec2_t b);

int64_t cm_ivec2_dist_squared(const cm_ivec2_t a, const cm_ivec2_t b);
float cm_ivec2_dist(const cm_ivec2_t a, const cm_ivec2_t b);

#endif
