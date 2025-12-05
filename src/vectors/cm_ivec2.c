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

void cm_ivec2_scale(cm_ivec2 v, int s, cm_ivec2 dest){
  dest.x = v.x * s;
  dest.y = v.y * s;
}

void cm_ivec2_fill(cm_ivec2 v, int val){
  v.x = val;
  v.y = val;
}

int cm_ivec2_dot(cm_ivec2 a, cm_ivec2 b){
  return a.x * b.x + a.y * b.y;
}

int cm_ivec2_cross(cm_ivec2 a, cm_ivec2 b){
  return a.x * b.y - a.y * b.x;
}





