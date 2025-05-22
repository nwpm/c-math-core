#include "trignm.h"
#include "../constants/constnts.h"

/*Degrees and radians convertion*/
float sml_to_deg(float rad) { return (rad * STRGHT_ANG / PI); }
float sml_to_rad(float deg) { return (deg * PI / STRGHT_ANG); }

/*Reduction of angles in (-2PI, 2PI)*/
float sml_normalize_angle(float rad) {
  int turns = (int)(rad / TWO_PI);
  float result = rad - (turns * TWO_PI);
  return result;
}

/*Simple check is angles adjacent*/
/*FLOAT COMPARISON*/
int sml_is_angles_adjacent(float first_angle, float second_angle) {
  return first_angle + second_angle == STRGHT_ANG;
}

/**/
float _sml_absolute_value(float num) {
  return (num > 0.f) ? num : (-1.f * num);
}

int _sml_float_compare(float first, float second) {
  return _sml_absolute_value(first - second) < 0.00001;
}
/**/

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
int sml_find_quadrant(float rad) {

  float normalize = sml_normalize_angle(rad);

  int equal_zero = _sml_float_compare(normalize, 0.f);
  int equal_pi_2 = _sml_float_compare(normalize, HALF_PI);
  int equal_pi = _sml_float_compare(normalize, PI);
  int equal_3pi_2 = _sml_float_compare(normalize, THREE_PI_OVER_TWO);
  int equal_2_pi = _sml_float_compare(normalize, TWO_PI);

  if (equal_zero || equal_pi_2 || equal_pi || equal_3pi_2 || equal_2_pi) {
    return 0;
  }

  if (normalize > 0.f && normalize < HALF_PI) {
    return 1;
  } else if (normalize > HALF_PI && normalize < PI) {
    return 2;
  } else if (normalize > PI && normalize < THREE_PI_OVER_TWO) {
    return 3;
  }

  return 4;
}
