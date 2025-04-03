#include "trignm.h"
#include <stdio.h>

#define PI 3.141592
#define STRGHT_ANG 180.0
#define FULL_TRN_DEG 360.0
#define FULL_TRN_INT_DEG 360
#define FULL_TRN_RAD (2 * PI)

float absolute_value(float val) { return val > 0.0 ? val : (-1.0 * val); }

/*Degrees and radians convertion*/
float to_deg(float rad) { return (rad * STRGHT_ANG / PI); }
float to_rad(float deg) { return (deg * PI / STRGHT_ANG); }

/*Reduction of angles in (-2PI, 2PI)*/
float normalize_angle_signed(float deg) {
  int turns = (int)(deg / FULL_TRN_DEG);
  float result = deg - (turns * FULL_TRN_DEG);
  return result;
}

/*Simple check is angles adjacent*/
int is_angles_adjacent(float first_angle, float second_angle) {
  return first_angle + second_angle == STRGHT_ANG;
}

/*Find in what quadrant is angle*/
/*
 Test cases for function:
 0
 0.00001
 45
 45.555
 89.9999
 90
 123.4
 179.0001
 180.5
 260.1
 269.0111
 271.0001
 And same but negative versions
*/
/*For now functions correctly work only with integer values of angle*/
int find_quadrant_deg(float deg) {
  /*Get rid of decimal part*/
  int normalized_angle = (int)normalize_angle_signed(deg);
  float decimal_part = deg - normalized_angle;

  decimal_part = decimal_part > 0.f ? decimal_part : -1.f * decimal_part;
  normalized_angle = normalized_angle >= 0
                         ? normalized_angle
                         : normalized_angle + FULL_TRN_INT_DEG;

  if (normalized_angle + decimal_part > 0.f && normalized_angle < 90.f) {
    return 1;
  } else if (normalized_angle + decimal_part > 90.f &&
             normalized_angle < 180.f) {
    return 2;
  } else if (normalized_angle + decimal_part > 180.f &&
             normalized_angle < 270.f) {
    return 3;
  } else if (normalized_angle + decimal_part > 270.f &&
             normalized_angle < 360.f) {
    return 4;
  }

  /*If function return zero, angle is a boundary point*/
  return 0;
}

int main(void) {
  float angle_f = -181.0001;
  float angle_s = 60.0;
  printf("%d\n", find_quadrant_deg(angle_f));
  printf("%f\n", absolute_value(angle_f));
  return 0;
}
