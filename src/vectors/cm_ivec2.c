#include "cm_ivec2.h"

void cm_ivec2_copy(cm_ivec2 v, cm_ivec2 dest){
  dest.x = v.x;
  dest.y = v.y;
}

void cm_ivec2_zero(cm_ivec2 v){
  v.x = 0;
  v.y = 0;
}

void cm_ivec2_add(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest){
  dest.x = a.x + b.x;
  dest.y = a.y + b.y;
}

void cm_ivec2_sub(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest){
  dest.x = a.x - b.y;
  dest.y = a.x - b.y;
}


