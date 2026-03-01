#ifndef CM_VEC3_H
#define CM_VEC3_H

#include <stdbool.h>

// NOTE: The module is designed to work in Euclidean 3D vector space.
// NOTE: Angles are measured in radians

typedef struct {
  double x, y, z;
} cm_vec3_t;

void cm_vec3_init(cm_vec3_t *v, double x, double y, double z);
void cm_vec3_copy(const cm_vec3_t src, cm_vec3_t *dest);
void cm_vec3_fill(cm_vec3_t *v, double val);
void cm_vec3_set_zero(cm_vec3_t *v);

void cm_vec3_add(const cm_vec3_t a, const cm_vec3_t b, cm_vec3_t *res);
void cm_vec3_sub(const cm_vec3_t a, const cm_vec3_t b, cm_vec3_t *res);
void cm_vec3_scale(const cm_vec3_t v, double s, cm_vec3_t *res);
void cm_vec3_abs(const cm_vec3_t v, cm_vec3_t *res);

void cm_vec3_add_inplace(cm_vec3_t *a, const cm_vec3_t b);
void cm_vec3_sub_inplace(cm_vec3_t *a, const cm_vec3_t b);
void cm_vec3_scale_inplace(cm_vec3_t *v, double s);
void cm_vec3_abs_inplace(cm_vec3_t *v);

double cm_vec3_dot(const cm_vec3_t a, const cm_vec3_t b);
double cm_vec3_dot_angle(const cm_vec3_t a, const cm_vec3_t b, double angle);
void cm_vec3_cross(const cm_vec3_t a, const cm_vec3_t b, cm_vec3_t* res);
double cm_vec3_dist_squared(const cm_vec3_t a, const cm_vec3_t b);
double cm_vec3_dist(const cm_vec3_t a, const cm_vec3_t b);

void cm_vec3_normalize(const cm_vec3_t v, cm_vec3_t *res);
void cm_vec3_normalize_inplace(cm_vec3_t* v);

double cm_vec3_angle_between(const cm_vec3_t a, const cm_vec3_t b);
double cm_vec3_norm(const cm_vec3_t v);
double cm_vec3_norm_squared(const cm_vec3_t v);

bool cm_vec3_is_zero(const cm_vec3_t v);
bool cm_vec3_is_equal(const cm_vec3_t a, const cm_vec3_t b);

static inline double cm_vec3_get_x(const cm_vec3_t v) { return v.x; }
static inline double cm_vec3_get_y(const cm_vec3_t v) { return v.y; }
static inline double cm_vec3_get_z(const cm_vec3_t v) { return v.z; }

static inline void cm_vec3_set_x(cm_vec3_t *v, double val) { v->x = val; }
static inline void cm_vec3_set_y(cm_vec3_t *v, double val) { v->y = val; }
static inline void cm_vec3_set_z(cm_vec3_t *v, double val) { v->z = val; }

#endif
