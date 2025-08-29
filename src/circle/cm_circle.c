#include "cm_circle.h"

int on_circle(double x, double y, double r, double px1, double py1){

  double right_part = (r * r);
  double left_part = ((x - px1) * (x - px1)) + ((y - py1) * (y - py1));

  if (left_part < right_part)
    return -1;
  else if (left_part > right_part)
    return 1;

  return 0;
}
