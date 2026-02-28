#include "../../../include/cmathcore/vector2.h"
#include <criterion/criterion.h>

Test(creation, default_init){

  cm_vec2_t v;
  cm_vec2_init(&v, 1., 5.);

  cr_expect(cm_vec2_get_x(v) == 1.);
  cr_expect(cm_vec2_get_y(v) == 5.);
}

Test(creation, default_copy){

  cm_vec2_t src;
  cm_vec2_t dest;
  cm_vec2_init(&src, 1., 5.);
  cm_vec2_copy(src, &dest);

  cr_expect(cm_vec2_get_x(dest) == cm_vec2_get_x(src));
  cr_expect(cm_vec2_get_y(dest) == cm_vec2_get_y(src));
}

Test(creation, self_copy){

  cm_vec2_t src;
  cm_vec2_init(&src, 1., 5.);
  cm_vec2_copy(src, &src);

  cr_expect(cm_vec2_get_x(src) == cm_vec2_get_x(src));
  cr_expect(cm_vec2_get_y(src) == cm_vec2_get_y(src));
}

Test(creation, default_fill){

  cm_vec2_t v;
  cm_vec2_fill(&v, 1.);

  cr_expect(cm_vec2_get_x(v) == 1.);
  cr_expect(cm_vec2_get_y(v) == 1.);
}

Test(creation, default_set_zero){

  cm_vec2_t v;
  cm_vec2_set_zero(&v);

  cr_expect(cm_vec2_get_x(v) == 0.);
  cr_expect(cm_vec2_get_y(v) == 0.);
}


