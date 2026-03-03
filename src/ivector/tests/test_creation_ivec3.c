#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../../../include/cmathcore/ivector3.h"

// ********************Init Tests********************
Test(creation, init_positive_components) {

  cm_ivec3_t v;
  cm_ivec3_init(&v, 1, 5, 3);

  cr_expect(eq(i64, cm_ivec3_get_x(v), 1));
  cr_expect(eq(i64, cm_ivec3_get_y(v), 5));
  cr_expect(eq(i64, cm_ivec3_get_z(v), 3));
}

// ********************Copy Tests********************
Test(creation, copy_positive_components) {

  cm_ivec3_t src;
  cm_ivec3_t dest;
  cm_ivec3_init(&src, 1, 5, 3);
  cm_ivec3_copy(src, &dest);

  cr_expect(eq(i64, cm_ivec3_get_x(dest), cm_ivec3_get_x(src)));
  cr_expect(eq(i64, cm_ivec3_get_y(dest), cm_ivec3_get_y(src)));
  cr_expect(eq(i64, cm_ivec3_get_z(dest), cm_ivec3_get_z(src)));
}

Test(creation, self_copy) {

  cm_ivec3_t src;
  cm_ivec3_init(&src, 1, 5, 3);
  cm_ivec3_copy(src, &src);

  cr_expect(eq(i64, cm_ivec3_get_x(src), 1));
  cr_expect(eq(i64, cm_ivec3_get_y(src), 5));
  cr_expect(eq(i64, cm_ivec3_get_z(src), 3));
}

// ********************Fill Tests********************
Test(creation, fill_positive_components) {

  cm_ivec3_t v;
  cm_ivec3_fill(&v, 1);

  cr_expect(eq(i64, cm_ivec3_get_x(v), 1));
  cr_expect(eq(i64, cm_ivec3_get_y(v), 1));
  cr_expect(eq(i64, cm_ivec3_get_z(v), 1));
}

// ********************Set Zero Tests********************
Test(creation, default_set_zero) {

  cm_ivec3_t v;
  cm_ivec3_set_zero(&v);

  cr_expect(eq(i64, cm_ivec3_get_x(v), 0));
  cr_expect(eq(i64, cm_ivec3_get_y(v), 0));
  cr_expect(eq(i64, cm_ivec3_get_z(v), 0));
}
