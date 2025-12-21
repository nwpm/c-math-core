#include "../../../include/cm_core/cm_mat.h"
#include "../../Unity/src/unity.h"
#include "../../Unity/src/unity_internals.h"
#include <stddef.h>
#include <stdio.h>

// NOTE: test float version of matrix

void setUp() {}
void tearDown() {}

/************************** Alloc ****************************/

void alloc_checker(size_t rows, size_t cols) {

  cm_mat_t *mat = cm_mat_alloc(rows, cols);

  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  TEST_ASSERT_EQUAL_size_t(rows, cm_mat_rows(mat));
  TEST_ASSERT_EQUAL_size_t(cols, cm_mat_cols(mat));

  cm_mat_free(mat);
}

void test_alloc_rows_0_cols_0() { alloc_checker(0, 0); }
void test_alloc_rows_1_cols_1() { alloc_checker(1, 1); }
void test_alloc_rows_1_cols_5() { alloc_checker(1, 5); }
void test_alloc_rows_5_cols_1() { alloc_checker(5, 1); }
void test_alloc_rows_50_cols_50() { alloc_checker(50, 50); }
void test_alloc_rows_250_cols_50() { alloc_checker(250, 50); }
void test_alloc_rows_1000_cols_1000() { alloc_checker(1000, 1000); }

/************************** Zero ****************************/

void create_zero_checker(size_t rows, size_t cols) {

  cm_mat_t *mat = cm_mat_create_zero(rows, cols);

  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  TEST_ASSERT_EQUAL_size_t(rows, cm_mat_rows(mat));
  TEST_ASSERT_EQUAL_size_t(cols, cm_mat_cols(mat));

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      TEST_ASSERT_EQUAL_FLOAT(0.f, cm_mat_get(mat, i, j));
    }
  }

  cm_mat_free(mat);
}

void test_create_zero_rows_0_cols_0() { alloc_checker(0, 0); }
void test_create_zero_rows_1_cols_1() { alloc_checker(1, 1); }
void test_create_zero_rows_1_cols_5() { alloc_checker(1, 5); }
void test_create_zero_rows_5_cols_1() { alloc_checker(5, 1); }
void test_create_zero_rows_50_cols_50() { alloc_checker(50, 50); }
void test_create_zero_rows_250_cols_50() { alloc_checker(250, 50); }
void test_create_zero_rows_1000_cols_1000() { alloc_checker(1000, 1000); }

int main() {

  UNITY_BEGIN();

  puts("**********Test alloc**********");
  RUN_TEST(test_alloc_rows_0_cols_0);
  RUN_TEST(test_alloc_rows_1_cols_1);
  RUN_TEST(test_alloc_rows_1_cols_5);
  RUN_TEST(test_alloc_rows_5_cols_1);
  RUN_TEST(test_alloc_rows_50_cols_50);
  RUN_TEST(test_alloc_rows_250_cols_50);
  RUN_TEST(test_alloc_rows_1000_cols_1000);

  puts("**********Test create zero**********");
  RUN_TEST(test_create_zero_rows_0_cols_0);
  RUN_TEST(test_create_zero_rows_1_cols_1);
  RUN_TEST(test_create_zero_rows_1_cols_5);
  RUN_TEST(test_create_zero_rows_5_cols_1);
  RUN_TEST(test_create_zero_rows_50_cols_50);
  RUN_TEST(test_create_zero_rows_250_cols_50);
  RUN_TEST(test_create_zero_rows_1000_cols_1000);

  return UNITY_END();
}
