#include "euclide_geom.h"
#include "../constants/constnts.h"
#include <stdio.h>

float sml_circumference(float rad) {
  if (rad < 0) {
    return -1;
  }

  float result = 2 * PI * rad;
  return result;
}

int main(void) {

  printf("%f\n", sml_circumference(2.15f));
  return 0;
}
