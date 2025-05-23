#ifndef MC_LINEAR_ALGEBRA_H
#define MC_LINEAR_ALGEBRA_H

#include "../types/mc_point2d_double.h"
#include "../types/mc_point2d_float.h"

#include "../types/mc_vector2d_float.h"
#include "../types/mc_vector2d_double.h"

static inline float mc_dot2d_f(mc_vector2d_float v1, mc_point2d_float v2){
  return v1.x * v2.x + v1.y * v2.y;
}

static inline double mc_dot2d_d(mc_vector2d_double v1, mc_point2d_double v2){
  return v1.x * v2.x + v1.y * v2.y;
}


#endif // MC_LINEAR_ALGEBRA_H
