#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../../../include/cmathcore/ivector2.h"

// ********************Init Tests********************
Test(creation, init_positive_components) {

  cm_ivec2_t v;
  cm_ivec2_init(&v, 1, 5);

  cr_expect(eq(i64, cm_ivec2_get_x(v), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(v), 5));
}

// ********************Copy Tests********************
Test(creation, copy_positive_components) {

  cm_ivec2_t src;
  cm_ivec2_t dest;
  cm_ivec2_init(&src, 1, 5);
  cm_ivec2_copy(src, &dest);

  cr_expect(eq(i64, cm_ivec2_get_x(dest), cm_ivec2_get_x(src)));
  cr_expect(eq(i64, cm_ivec2_get_y(dest), cm_ivec2_get_y(src)));
}

Test(creation, self_copy) {

  cm_ivec2_t src;
  cm_ivec2_init(&src, 1, 5);
  cm_ivec2_copy(src, &src);

  cr_expect(eq(i64, cm_ivec2_get_x(src), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(src), 5));
}

// ********************Fill Tests********************
Test(creation, fill_positive_components) {

  cm_ivec2_t v;
  cm_ivec2_fill(&v, 1);

  cr_expect(eq(i64, cm_ivec2_get_x(v), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(v), 1));
}

// ********************Set Zero Tests********************
Test(creation, default_set_zero) {

  cm_ivec2_t v;
  cm_ivec2_set_zero(&v);

  cr_expect(eq(i64, cm_ivec2_get_x(v), 0));
  cr_expect(eq(i64, cm_ivec2_get_y(v), 0));
}
