#include "trignm.h"
#include "../constants/constnts.h"

/*Degrees and radians convertion*/
float sml_to_deg(float rad) { return (rad * STRGHT_ANG / PI); }
float sml_to_rad(float deg) { return (deg * PI / STRGHT_ANG); }

/*Reduction of angles in (-2PI, 2PI)*/
float sml_normalize_angle(float deg) {
  int turns = (int)(deg / FULL_TRN_DEG);
  float result = deg - (turns * FULL_TRN_DEG);
  return result;
}

/*Simple check is angles adjacent*/
/*FLOAT COMPARISON*/
int sml_is_angles_adjacent(float first_angle, float second_angle) {
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
int sml_find_quadrant(float deg) {
  /*Get rid of decimal part*/
  int normalized_angle = (int)sml_normalize_angle(deg);
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
