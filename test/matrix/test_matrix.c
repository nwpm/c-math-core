#include "../../src/matrix/cm_matrix_double.h"
#include "../Unity/src/unity.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void setUp() {}
void tearDown() {}

// create_from_matrix + set_all + is_equal

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

void test_create_from_matrix_rows_1_cols_1() {
  check_create_from_matrix(1, 1, 5.);
}
void test_create_from_matrix_rows_1_cols_5() {
  check_create_from_matrix(1, 5, 5.);
}
void test_create_from_matrix_rows_5_cols_1() {
  check_create_from_matrix(5, 1, 5.);
}
void test_create_from_matrix_rows_100_cols_100() {
  check_create_from_matrix(100, 100, 5.);
}

// Set Identity + is identity

void check_set_identity(size_t orig_rows, size_t orig_cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(orig_rows, orig_cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);
  TEST_ASSERT_TRUE(cm_matrix_double_is_identity(matrix));

  cm_matrix_double_free(matrix);
}

void test_set_identity_rows_1_cols_1() { check_set_identity(1, 1); }
void test_set_identity_rows_5_cols_5() { check_set_identity(5, 5); }
void test_set_identity_rows_25_cols_25() { check_set_identity(25, 25); }
void test_set_identity_rows_100_cols_100() { check_set_identity(100, 100); }

// set_zero + is zero matrix

void check_set_zero(size_t orig_rows, size_t orig_cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(orig_rows, orig_cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_zero(matrix);
  TEST_ASSERT_TRUE(cm_matrix_double_is_null(matrix));

  cm_matrix_double_free(matrix);
}

void test_set_zero_rows_1_cols_1() { check_set_zero(1, 1); }
void test_set_zero_rows_5_cols_5() { check_set_zero(5, 5); }
void test_set_zero_rows_15_cols_5() { check_set_zero(5, 5); }
void test_set_zero_rows_25_cols_25() { check_set_zero(25, 25); }
void test_set_zero_rows_55_cols_15() { check_set_zero(25, 25); }
void test_set_zero_rows_100_cols_100() { check_set_zero(100, 100); }

// swap + get

void check_swap(size_t matrix_a_rows, size_t matrix_a_cols,
                size_t matrix_b_rows, size_t matrix_b_cols, double init_a,
                double init_b) {

  CmMatrixDouble *matrix_a =
      cm_matrix_double_alloc(matrix_a_rows, matrix_a_cols);
  TEST_ASSERT_NOT_NULL(matrix_a);

  cm_matrix_double_set_all(matrix_a, init_a);

  CmMatrixDouble *matrix_b =
      cm_matrix_double_alloc(matrix_b_rows, matrix_b_cols);
  TEST_ASSERT_NOT_NULL(matrix_b);

  cm_matrix_double_set_all(matrix_b, init_b);

  cm_matrix_double_swap(&matrix_a, &matrix_b);

  TEST_ASSERT_EQUAL_size_t(matrix_a_rows, matrix_b->rows);
  TEST_ASSERT_EQUAL_size_t(matrix_a_cols, matrix_b->columns);

  TEST_ASSERT_EQUAL_size_t(matrix_b_rows, matrix_a->rows);
  TEST_ASSERT_EQUAL_size_t(matrix_b_cols, matrix_a->columns);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(init_b, cm_matrix_double_get(matrix_a, i, j));
    }
  }

  for (size_t i = 0; i < matrix_b->rows; ++i) {
    for (size_t j = 0; j < matrix_b->columns; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(init_a, cm_matrix_double_get(matrix_b, i, j));
    }
  }

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
}

void test_swap_matrix_a_rows_8_cols_1_matrix_b_rows_5_cols_10() {
  check_swap(8, 1, 5, 10, 3., 9.);
}
void test_swap_matrix_a_rows_14_cols_23_matrix_b_rows_3_cols_44() {
  check_swap(14, 23, 3, 44, 10., 23.);
}
void test_swap_matrix_a_rows_10_cols_10_matrix_b_rows_10_cols_10() {
  check_swap(10, 10, 10, 10, 3., 3.);
}
void test_swap_matrix_a_rows_113_cols_133_matrix_b_rows_144_cols_244() {
  check_swap(113, 133, 144, 244, 0., 43.);
}
void test_swap_matrix_a_rows_410_cols_410_matrix_b_rows_510_cols_510() {
  check_swap(410, 410, 510, 510, 100., 500.);
}

// transpose

void check_transpose(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  double init_val = 1.;
  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      cm_matrix_double_set(matrix, i, j, init_val++);
    }
  }

  cm_matrix_double_transpose(&matrix);

  init_val = 1.;
  for (size_t i = 0; i < matrix->columns; ++i) {
    for (size_t j = 0; j < matrix->rows; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(init_val, cm_matrix_double_get(matrix, j, i));
      init_val++;
    }
  }

  cm_matrix_double_free(matrix);
}

void test_transpose_rows_1_cols_1() { check_transpose(1, 1); }
void test_transpose_rows_5_cols_5() { check_transpose(5, 5); }
void test_transpose_rows_2_cols_3() { check_transpose(2, 3); }
void test_transpose_rows_15_cols_7() { check_transpose(15, 7); }
void test_transpose_rows_65_cols_97() { check_transpose(65, 97); }
void test_transpose_rows_239_cols_432() { check_transpose(239, 432); }

// max

void check_max(size_t rows, size_t cols, double max_elem, size_t max_elem_row,
               size_t max_elem_col) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);

  cm_matrix_double_set(matrix, max_elem_row, max_elem_col, max_elem);

  double max_current = 0.;
  cm_matrix_double_max(matrix, &max_current);

  TEST_ASSERT_EQUAL_DOUBLE(max_elem, max_current);
  cm_matrix_double_free(matrix);
}

void test_max_rows_3_cols_3_expected_100() { check_max(3, 3, 100., 0, 1); }
void test_max_rows_10_cols_5_expected_100() { check_max(10, 5, 100., 4, 3); }
void test_max_rows_25_cols_25_expected_100() {
  check_max(25, 25, 100., 11, 17);
}
void test_max_rows_90_cols_120_expected_100() {
  check_max(90, 120, 100., 39, 71);
}
void test_max_rows_150_cols_150_expected_100() {
  check_max(150, 150, 100., 100, 120);
}

// min

void check_min(size_t rows, size_t cols, double min_elem, size_t min_elem_row,
               size_t min_elem_col) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);

  cm_matrix_double_set(matrix, min_elem_row, min_elem_col, min_elem);

  double min_current = 0.;
  cm_matrix_double_min(matrix, &min_current);

  TEST_ASSERT_EQUAL_DOUBLE(min_elem, min_current);
  cm_matrix_double_free(matrix);
}

void test_min_rows_3_cols_3_expected_minus_10() { check_min(3, 3, -10., 0, 1); }
void test_min_rows_10_cols_5_expected_minus_10() {
  check_min(10, 5, -10., 4, 3);
}
void test_min_rows_25_cols_25_expected_minus_10() {
  check_min(25, 25, -10., 11, 17);
}
void test_min_rows_90_cols_120_expected_minus_10() {
  check_min(90, 120, -10., 39, 71);
}
void test_min_rows_150_cols_150_expected_minus_10() {
  check_min(150, 150, -10., 100, 120);
}

int main() {

  UNITY_BEGIN();

  puts("\nCreate_from_matrix + set_all + is_equal\n");
  RUN_TEST(test_create_from_matrix_rows_1_cols_1);
  RUN_TEST(test_create_from_matrix_rows_1_cols_5);
  RUN_TEST(test_create_from_matrix_rows_5_cols_1);
  RUN_TEST(test_create_from_matrix_rows_100_cols_100);

  puts("\nSet identity + is identity\n");
  RUN_TEST(test_set_identity_rows_1_cols_1);
  RUN_TEST(test_set_identity_rows_5_cols_5);
  RUN_TEST(test_set_identity_rows_25_cols_25);
  RUN_TEST(test_set_identity_rows_100_cols_100);

  puts("\nSet zero + is zero\n");
  RUN_TEST(test_set_zero_rows_1_cols_1);
  RUN_TEST(test_set_zero_rows_5_cols_5);
  RUN_TEST(test_set_zero_rows_15_cols_5);
  RUN_TEST(test_set_zero_rows_25_cols_25);
  RUN_TEST(test_set_zero_rows_55_cols_15);
  RUN_TEST(test_set_zero_rows_100_cols_100);

  puts("\nswap + get\n");
  RUN_TEST(test_swap_matrix_a_rows_8_cols_1_matrix_b_rows_5_cols_10);
  RUN_TEST(test_swap_matrix_a_rows_410_cols_410_matrix_b_rows_510_cols_510);
  RUN_TEST(test_swap_matrix_a_rows_10_cols_10_matrix_b_rows_10_cols_10);
  RUN_TEST(test_swap_matrix_a_rows_113_cols_133_matrix_b_rows_144_cols_244);
  RUN_TEST(test_swap_matrix_a_rows_14_cols_23_matrix_b_rows_3_cols_44);

  puts("\ntranspose\n");
  RUN_TEST(test_transpose_rows_1_cols_1);
  RUN_TEST(test_transpose_rows_2_cols_3);
  RUN_TEST(test_transpose_rows_5_cols_5);
  RUN_TEST(test_transpose_rows_15_cols_7);
  RUN_TEST(test_transpose_rows_65_cols_97);
  RUN_TEST(test_transpose_rows_239_cols_432);

  puts("\nmax\n");
  RUN_TEST(test_max_rows_3_cols_3_expected_100);
  RUN_TEST(test_max_rows_10_cols_5_expected_100);
  RUN_TEST(test_max_rows_25_cols_25_expected_100);
  RUN_TEST(test_max_rows_90_cols_120_expected_100);
  RUN_TEST(test_max_rows_150_cols_150_expected_100);

  puts("\nmin\n");
  RUN_TEST(test_min_rows_3_cols_3_expected_minus_10);
  RUN_TEST(test_min_rows_10_cols_5_expected_minus_10);
  RUN_TEST(test_min_rows_25_cols_25_expected_minus_10);
  RUN_TEST(test_min_rows_90_cols_120_expected_minus_10);
  RUN_TEST(test_min_rows_150_cols_150_expected_minus_10);

  return UNITY_END();
}
