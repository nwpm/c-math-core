#include "euclide_geom.h"
#include "../constants/constnts.h"

float sml_circumference(float rad) {
  if (rad < 0) {
    return -1;
  }

  float result = 2 * PI * rad;
  return result;
}
