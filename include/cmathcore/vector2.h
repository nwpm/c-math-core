#ifndef CM_VEC2_H
#define CM_VEC2_H

#include <stdbool.h>

// NOTE: The module is designed to work in Euclidean 2D vector space.
// NOTE: Angles are measured in radians

typedef struct {
  double x, y;
} cm_vec2_t;

void cm_vec2_init(cm_vec2_t *v, double x, double y);
void cm_vec2_copy(const cm_vec2_t src, cm_vec2_t *dest);
void cm_vec2_fill(cm_vec2_t *v, double val);
void cm_vec2_set_zero(cm_vec2_t *v);

void cm_vec2_add(const cm_vec2_t a, const cm_vec2_t b, cm_vec2_t *res);
void cm_vec2_sub(const cm_vec2_t a, const cm_vec2_t b, cm_vec2_t *res);
void cm_vec2_scale(const cm_vec2_t v, double s, cm_vec2_t *res);
void cm_vec2_abs(const cm_vec2_t v, cm_vec2_t *res);

void cm_vec2_add_inplace(cm_vec2_t *a, const cm_vec2_t b);
void cm_vec2_sub_inplace(cm_vec2_t *a, const cm_vec2_t b);
void cm_vec2_scale_inplace(cm_vec2_t *v, double s);
void cm_vec2_abs_inplace(cm_vec2_t *v);

double cm_vec2_dot(const cm_vec2_t a, const cm_vec2_t b);
double cm_vec2_dot_angle(const cm_vec2_t a, const cm_vec2_t b, double angle);
// NOTE: Pseudo-scalar product
double cm_vec2_cross(const cm_vec2_t a, const cm_vec2_t b);
double cm_vec2_dist_squared(const cm_vec2_t a, const cm_vec2_t b);
double cm_vec2_dist(const cm_vec2_t a, const cm_vec2_t b);

void cm_vec2_normalize(const cm_vec2_t v, cm_vec2_t *res);
void cm_vec2_normalize_inplace(cm_vec2_t* v);

double cm_vec2_angle_between(const cm_vec2_t a, const cm_vec2_t b);
double cm_vec2_norm(const cm_vec2_t v);
double cm_vec2_norm_squared(const cm_vec2_t v);

bool cm_vec2_is_zero(const cm_vec2_t v);
bool cm_vec2_is_equal(const cm_vec2_t a, const cm_vec2_t b);

static inline double cm_vec2_get_x(const cm_vec2_t v) { return v.x; }
static inline double cm_vec2_get_y(const cm_vec2_t v) { return v.y; }

static inline void cm_vec2_set_x(cm_vec2_t *v, double val) { v->x = val; }
static inline void cm_vec2_set_y(cm_vec2_t *v, double val) { v->y = val; }

#endif
