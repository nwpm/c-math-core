#include "../../include/euclidean/mc_euclidean.h"
#include "../../include/constants/constants.h"

float mc_circumference_f(float radius) {
  if (radius <= 0.f) {
    return 0.f;
  }

  return 2.f * radius * PI;
}

double mc_circumference_d(double radius) {
  if (radius <= 0.) {
    return 0.;
  }

  return 2. * radius * PI;
}


float mc_circle_area_f(float radius){
  if(radius <= 0.f){
    return 0.f;
  }

  return PI * radius * radius;
}

double mc_circle_area_d(double radius){
  if(radius <= 0.){
    return 0.;
  }

  return PI * radius * radius;
}

