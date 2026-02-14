#ifndef CM_NUMERICAL_H
#define CM_NUMERICAL_H

#include "cm_types.h"
#include <stdbool.h>
#include <stddef.h>

cm_real_t cm_abs(cm_real_t x);
cm_real_t cm_sign(cm_real_t x);
cm_real_t cm_clamp(cm_real_t x, cm_real_t min, cm_real_t max);
cm_real_t cm_min(cm_real_t x, cm_real_t y);
cm_real_t cm_max(cm_real_t x, cm_real_t y);
cm_real_t cm_lerp(cm_real_t a, cm_real_t b, cm_real_t t);
cm_real_t cm_sqr(cm_real_t x);
cm_real_t cm_sqrt(cm_real_t x);
cm_real_t cm_rsqrt(cm_real_t x);
cm_real_t cm_inv(cm_real_t x);

cm_real_t cm_sin(cm_real_t x);
cm_real_t cm_cos(cm_real_t x);
cm_real_t cm_tan(cm_real_t x);
cm_real_t cm_asin(cm_real_t x);
cm_real_t cm_acos(cm_real_t x);
cm_real_t cm_atan(cm_real_t x);
cm_real_t cm_atan2(cm_real_t y, cm_real_t x);

cm_real_t cm_safe_div(cm_real_t a, cm_real_t b, cm_real_t fallback);
cm_real_t cm_finite_diff(cm_real_t (*f)(cm_real_t), cm_real_t x, cm_real_t h);
cm_real_t cm_integrate_trap(cm_real_t (*f)(cm_real_t), cm_real_t a, cm_real_t b,
                            size_t n);
cm_real_t cm_integrate_simpson(cm_real_t (*f)(cm_real_t), cm_real_t a,
                               cm_real_t b, size_t n);
cm_real_t cm_root_bisection(cm_real_t (*f)(cm_real_t), cm_real_t a, cm_real_t b,
                            cm_real_t eps);
cm_real_t cm_root_newton(cm_real_t (*f)(cm_real_t),
                         cm_real_t (*fprime)(cm_real_t), cm_real_t x0,
                         cm_real_t eps, size_t max_iter);
cm_real_t cm_smoothstep(cm_real_t edge0, cm_real_t edge1, cm_real_t x);
cm_real_t cm_step(cm_real_t edge, cm_real_t x);

cm_real_t cm_exp(cm_real_t x);
cm_real_t cm_log(cm_real_t x);
cm_real_t cm_log10(cm_real_t x);
cm_real_t cm_pow(cm_real_t x, cm_real_t y);

bool cm_is_zero(cm_real_t x, cm_real_t eps);
bool cm_is_equal(cm_real_t a, cm_real_t b, cm_real_t eps);
cm_real_t cm_deg2rad(cm_real_t deg);
cm_real_t cm_rad2deg(cm_real_t rad);

#endif
