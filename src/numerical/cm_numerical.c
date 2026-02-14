#include "../../../include/cm_core/cm_numerical.h"

cm_real_t cm_abs(cm_real_t x) { return x >= 0 ? x : -x; }

cm_real_t cm_sign(cm_real_t x){
  return x >= 0 ? 1 : -1;
}

cm_real_t cm_clamp(cm_real_t x, cm_real_t min, cm_real_t max){
  if(x < min){
    return min;
  }else if(max < x){
    return max;
  }

  return x;
}

cm_real_t cm_min(cm_real_t x, cm_real_t y){
  return x > y ? y : x;
}

cm_real_t cm_max(cm_real_t x, cm_real_t y){
  return x > y ? x : y;
}

cm_real_t cm_lerp(cm_real_t a, cm_real_t b, cm_real_t t){
  return 1;
}

cm_real_t cm_sqr(cm_real_t x){
  return x * x;
}

cm_real_t cm_sqrt(cm_real_t x){
  return 1;
}

cm_real_t cm_rsqrt(cm_real_t x){
  return 1 / cm_sqrt(x);
}

cm_real_t cm_inv(cm_real_t x){
  return 1 / x;
}




