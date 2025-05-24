#ifndef MC_LINEAR_ALGEBRA_H
#define MC_LINEAR_ALGEBRA_H

#include "../types/mc_point2d_double.h"
#include "../types/mc_point2d_float.h"

#include "../types/mc_vector2d_double.h"
#include "../types/mc_vector2d_float.h"

/**
 * @brief Compute dot product of two 2d vectors by their coordinates
 * @param v1 Float 2d vector
 * @param v2 Float 2d vector
 * @return Dot product of vector v1 and vector v2
 */
static inline float mc_dot2d_f(mc_vector2d_float v1, mc_point2d_float v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

/**
 * @brief Compute dot product of two 2d vectors by their coordinates
 * @param v1 Double 2d vector
 * @param v2 Double 2d vector
 * @return Dot product of vector v1 and vector v2
 */
static inline double mc_dot2d_d(mc_vector2d_double v1, mc_point2d_double v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

/**
 * @brief Scale vector
 * @param v Float 2d vector
 * @param scale Scaling factor
 * @return Vector scaled by float value
 */
static inline mc_vector2d_float mc_scale_v2d_f(mc_vector2d_float v,
                                               float scale) {

  v.x *= scale;
  v.y *= scale;

  return v;
}

/**
 * @brief Scale vector
 * @param v Double 2d vector
 * @param scale Scaling factor
 * @return Vector scaled by double value
 */
static inline mc_vector2d_double mc_scale_v2d_d(mc_vector2d_double v,
                                                double scale) {
  v.x *= scale;
  v.y *= scale;

  return v;
}

#endif // MC_LINEAR_ALGEBRA_H
