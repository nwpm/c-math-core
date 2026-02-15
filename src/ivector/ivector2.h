#ifndef CM_IVEC2_H
#define CM_IVEC2_H

#define CM_GET_ZERO_IVEC2 ((cm_ivec2_t){0, 0})
#define CM_GET_E1_IVEC2 ((cm_ivec2_t){1, 0})
#define CM_GET_E2_IVEC2 ((cm_ivec2_t){0, 1})

#include <stdint.h>

// TODO: SIMD optimization for module
// TODO: support all int and float types(templates C++?)
// TODO: min, max compare without if

typedef struct {
  int64_t x, y;
} cm_ivec2_t;

void cm_ivec2_init(cm_ivec2_t *v, int64_t x, int64_t y);
void cm_ivec2_copy(const cm_ivec2_t v, cm_ivec2_t *dest);
void cm_ivec2_zero(cm_ivec2_t *v);
void cm_ivec2_add(const cm_ivec2_t x, const cm_ivec2_t y, cm_ivec2_t *dest);
void cm_ivec2_sub(const cm_ivec2_t x, const cm_ivec2_t y, cm_ivec2_t *dest);

void cm_ivec2_scale(const cm_ivec2_t v, int64_t s, cm_ivec2_t *dest);
void cm_ivec2_fill(int64_t val, cm_ivec2_t *dest);
void cm_ivec2_abs(const cm_ivec2_t v, cm_ivec2_t *dest);

void cm_ivec2_max(const cm_ivec2_t x, const cm_ivec2_t y, cm_ivec2_t *dest);
void cm_ivec2_min(const cm_ivec2_t x, const cm_ivec2_t y, cm_ivec2_t *dest);

int64_t cm_ivec2_dot(const cm_ivec2_t x, const cm_ivec2_t y);
int64_t cm_ivec2_cross(const cm_ivec2_t x, const cm_ivec2_t y);

int64_t cm_ivec2_dist_squared(const cm_ivec2_t x, const cm_ivec2_t y);
float cm_ivec2_dist(const cm_ivec2_t x, const cm_ivec2_t y);

#endif
