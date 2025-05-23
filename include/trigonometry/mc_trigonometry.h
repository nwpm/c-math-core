#ifndef TRIGNM_H
#define TRIGNM_H

#include "../constants/constnts.h"

/**
 * @brief Convert angle in radians to angle in degrees
 * @param rad Decimal value of angle
 * @return Decimal value of angle measure
 */
static inline float mc_to_deg_f(float rad) { return ((rad * 180.f) / PI); }

/**
 * @brief Convert angle in degrees to angle in radians
 * @param deg Decimal value of angle
 * @return Decimal value of angle measure
 */
static inline float mc_to_rad_f(float deg) { return ((deg * PI) / 180.f); }

/**
 * @brief Convert angle in radians to angle in degrees
 * @param rad Decimal value of angle
 * @return Decimal value of angle measure
 */
static inline double mc_to_deg_d(double rad) { return ((rad * 180.) / PI); }

/**
 * @brief Convert angle in degrees to angle in radians
 * @param deg Decimal value of angle
 * @return Decimal value of angle measure
 */
static inline double mc_to_rad_d(double deg) { return ((deg * PI) / 180.); }

#endif
