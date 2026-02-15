#include "../../../include/cmathcore/ivector2.h"
#include <stdio.h>

int main(){
  cm_ivec2_t v;
  cm_ivec2_init(&v, 1, 1);

  printf("%ld %ld\n", v.x, v.y);

  return 0;
}
