#include "../../../include/cmathcore/vector2.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Is Zero Tests********************
Test(compare, is_zero_non_zero_vector) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  bool res = cm_vec2_is_zero(a);
  cr_expect(eq(int, res, false));
}

Test(compare, is_zero_zero_vector) {

  cm_vec2_t a;

  cm_vec2_init(&a, 0., 0.);

  bool res = cm_vec2_is_zero(a);
  cr_expect(eq(int, res, true));
}

// ********************Is Equal Tests********************
Test(compare, is_equal_non_equal_vectors) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  bool res = cm_vec2_is_equal(a, b);
  cr_expect(eq(int, res, false));
}

Test(compare, is_equal_equal_vectors) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 2., 3.);

  bool res = cm_vec2_is_equal(a, b);
  cr_expect(eq(int, res, true));
}
