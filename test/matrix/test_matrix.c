#include "../../src/matrix/cm_matrix_double.h"
#include "../Unity/src/unity.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void setUp() {}
void tearDown() {}

// Create from matrix

void check_create_from_matrix(size_t orig_rows, size_t orig_cols,
                              double init_val) {

  CmMatrixDouble *source = cm_matrix_double_alloc(orig_rows, orig_cols);
  TEST_ASSERT_NOT_NULL(source);

  cm_matrix_double_set_all(source, init_val);

  CmMatrixDouble *copy = cm_matrix_double_create_from_matrix(source);
  TEST_ASSERT_NOT_NULL(copy);

  TEST_ASSERT_TRUE(cm_matrix_double_is_equal(source, copy));

  cm_matrix_double_free(source);
  cm_matrix_double_free(copy);
}

void test_create_from_matrix_rows_1_cols_1(){
  check_create_from_matrix(1, 1, 5.);
}

void test_create_from_matrix_rows_1_cols_5(){
  check_create_from_matrix(1, 5, 5.);
}

void test_create_from_matrix_rows_5_cols_1(){
  check_create_from_matrix(5, 1, 5.);
}

void test_create_from_matrix_rows_100_cols_100(){
  check_create_from_matrix(100, 100, 5.);
}

// Set Identity



int main() {

  UNITY_BEGIN();

  puts("\nCreate from matrix\n");
  RUN_TEST(test_create_from_matrix_rows_1_cols_1);
  RUN_TEST(test_create_from_matrix_rows_1_cols_5);
  RUN_TEST(test_create_from_matrix_rows_5_cols_1);
  RUN_TEST(test_create_from_matrix_rows_100_cols_100);

  return UNITY_END();
}
