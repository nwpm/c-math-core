#ifndef CM_IVEC3_H
#define CM_IVEC3_H

#define CM_GET_ZERO_IVEC3 ((cm_ivec3_t){0, 0, 0})
#define CM_GET_E1_IVEC3 ((cm_ivec3_t){1, 0, 0})
#define CM_GET_E2_IVEC3 ((cm_ivec3_t){0, 1, 0})
#define CM_GET_E3_IVEC3 ((cm_ivec3_t){0, 0, 1})

#include <stdint.h>

typedef struct cm_ivec3_t {
  int64_t x, y, z;
} cm_ivec3_t;

void cm_ivec3_init(cm_ivec3_t *v, int64_t x, int64_t y, int64_t z);
void cm_ivec3_copy(const cm_ivec3_t src, cm_ivec3_t *dest);
void cm_ivec3_fill(cm_ivec3_t *v, int64_t val);
void cm_ivec3_set_zero(cm_ivec3_t *v);

void cm_ivec3_add(const cm_ivec3_t a, const cm_ivec3_t b, cm_ivec3_t *res);
void cm_ivec3_sub(const cm_ivec3_t a, const cm_ivec3_t b, cm_ivec3_t *res);
void cm_ivec3_scale(const cm_ivec3_t v, int64_t s, cm_ivec3_t *res);
void cm_ivec3_abs(const cm_ivec3_t v, cm_ivec3_t *res);

void cm_ivec3_add_inplace(cm_ivec3_t *a, const cm_ivec3_t b);
void cm_ivec3_sub_inplace(cm_ivec3_t *a, const cm_ivec3_t b);
void cm_ivec3_scale_inplace(cm_ivec3_t *v, int64_t s);
void cm_ivec3_abs_inplace(cm_ivec3_t *v);

int64_t cm_ivec3_dot(const cm_ivec3_t a, const cm_ivec3_t b);
void cm_ivec3_cross(const cm_ivec3_t a, const cm_ivec3_t b, cm_ivec3_t *res);
int64_t cm_ivec3_dist_squared(const cm_ivec3_t a, const cm_ivec3_t b);

static inline int64_t cm_ivec3_get_x(const cm_ivec3_t v) { return v.x; }
static inline int64_t cm_ivec3_get_y(const cm_ivec3_t v) { return v.y; }
static inline int64_t cm_ivec3_get_z(const cm_ivec3_t v) { return v.z; }

static inline void cm_ivec3_set_x(cm_ivec3_t *v, int64_t val) { v->x = val; }
static inline void cm_ivec3_set_y(cm_ivec3_t *v, int64_t val) { v->y = val; }
static inline void cm_ivec3_set_z(cm_ivec3_t *v, int64_t val) { v->z = val; }

#endif
