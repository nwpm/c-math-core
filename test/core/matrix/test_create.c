#include "../../../include/cm_core/cm_mat.h"
#include "../../Unity/src/unity.h"
#include "../../Unity/src/unity_internals.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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

void test_create_zero_rows_0_cols_0() { create_zero_checker(0, 0); }
void test_create_zero_rows_1_cols_1() { create_zero_checker(1, 1); }
void test_create_zero_rows_1_cols_5() { create_zero_checker(1, 5); }
void test_create_zero_rows_5_cols_1() { create_zero_checker(5, 1); }
void test_create_zero_rows_50_cols_50() { create_zero_checker(50, 50); }
void test_create_zero_rows_250_cols_50() { create_zero_checker(250, 50); }
void test_create_zero_rows_1000_cols_1000() { create_zero_checker(1000, 1000); }

/************************** Identity ****************************/

void create_identity_checker(size_t size) {

  cm_mat_t *mat = cm_mat_create_identity(size);

  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  TEST_ASSERT_EQUAL_size_t(size, cm_mat_rows(mat));
  TEST_ASSERT_EQUAL_size_t(size, cm_mat_cols(mat));

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (i == j) {
        TEST_ASSERT_EQUAL_FLOAT(1.f, cm_mat_get(mat, i, j));
      } else {
        TEST_ASSERT_EQUAL_FLOAT(0.f, cm_mat_get(mat, i, j));
      }
    }
  }

  cm_mat_free(mat);
}

void test_create_identity_size_0() { create_identity_checker(0); }
void test_create_identity_size_1() { create_identity_checker(1); }
void test_create_identity_size_5() { create_identity_checker(5); }
void test_create_identity_size_25() { create_identity_checker(25); }
void test_create_identity_size_50() { create_identity_checker(50); }
void test_create_identity_size_250() { create_identity_checker(250); }
void test_create_identity_size_1000() { create_identity_checker(1000); }

/************************** Diagonal ****************************/

void create_diag_checker(size_t size, cm_real_t init_val) {

  cm_mat_t *mat = cm_mat_create_diag(size, init_val);

  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  TEST_ASSERT_EQUAL_size_t(size, cm_mat_rows(mat));
  TEST_ASSERT_EQUAL_size_t(size, cm_mat_cols(mat));

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (i == j) {
        TEST_ASSERT_EQUAL_FLOAT(init_val, cm_mat_get(mat, i, j));
      } else {
        TEST_ASSERT_EQUAL_FLOAT(0.f, cm_mat_get(mat, i, j));
      }
    }
  }

  cm_mat_free(mat);
}

void test_create_diag_size_0_init_val_5() { create_diag_checker(0, 5); }
void test_create_diag_size_1_init_val_10() { create_diag_checker(1, 10); }
void test_create_diag_size_5_init_val_2() { create_diag_checker(5, 2); }
void test_create_diag_size_25_init_val_100() { create_diag_checker(25, 100); }
void test_create_diag_size_50_init_val_140() { create_diag_checker(50, 140); }
void test_create_diag_size_250_init_val_250() { create_diag_checker(250, 250); }
void test_create_diag_size_1000_init_val_1000() {
  create_diag_checker(1000, 1000);
}

/************************** Copy ****************************/

void create_copy_checker(size_t source_rows, size_t source_cols) {

  cm_mat_t *source = cm_mat_alloc(source_rows, source_cols);
  TEST_ASSERT_NOT_NULL_MESSAGE(source, "malloc return NULL ptr.");

  for (size_t i = 0; i < source_rows; ++i) {
    for (size_t j = 0; j < source_cols; ++j) {
      cm_mat_set(source, i, j, i * 10 + j);
    }
  }

  cm_mat_t *mat = cm_mat_create_from_matrix(source);
  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  size_t copy_rows = cm_mat_rows(mat);
  size_t copy_cols = cm_mat_cols(mat);
  TEST_ASSERT_EQUAL_size_t(source_rows, copy_rows);
  TEST_ASSERT_EQUAL_size_t(source_cols, copy_cols);

  for (size_t i = 0; i < copy_rows; ++i) {
    for (size_t j = 0; j < copy_cols; ++j) {
      cm_real_t source_val = cm_mat_get(source, i, j);
      cm_real_t copy_val = cm_mat_get(mat, i, j);
      TEST_ASSERT_EQUAL_FLOAT(source_val, copy_val);
    }
  }

  cm_mat_free(mat);
  cm_mat_free(source);
}

void test_create_copy_rows_0_cols_0() { create_copy_checker(0, 0); }
void test_create_copy_rows_1_cols_1() { create_copy_checker(1, 1); }
void test_create_copy_rows_1_cols_5() { create_copy_checker(1, 5); }
void test_create_copy_rows_5_cols_1() { create_copy_checker(5, 1); }
void test_create_copy_rows_50_cols_50() { create_copy_checker(50, 50); }
void test_create_copy_rows_250_cols_50() { create_copy_checker(250, 50); }
void test_create_copy_rows_1000_cols_1000() { create_copy_checker(1000, 1000); }

/************************** Create from array ****************************/

void create_from_arr_checker(size_t source_rows, size_t source_cols) {

  cm_real_t **source = malloc(source_rows * sizeof(cm_real_t *));
  TEST_ASSERT_NOT_NULL_MESSAGE(source, "malloc return NULL ptr.");

  for (size_t i = 0; i < source_rows; ++i) {
    source[i] = malloc(source_cols * sizeof(cm_real_t));
  }

  for (size_t i = 0; i < source_rows; ++i) {
    for (size_t j = 0; j < source_cols; ++j) {
      source[i][j] = i * 100 + j;
    }
  }

  // NOTE: const problem
  cm_mat_t *mat = cm_mat_create_from_array((const cm_real_t **)source,
                                           source_rows, source_cols);
  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  size_t copy_rows = cm_mat_rows(mat);
  size_t copy_cols = cm_mat_cols(mat);
  TEST_ASSERT_EQUAL_size_t(source_rows, copy_rows);
  TEST_ASSERT_EQUAL_size_t(source_cols, copy_cols);

  for (size_t i = 0; i < copy_rows; ++i) {
    for (size_t j = 0; j < copy_cols; ++j) {
      cm_real_t source_val = source[i][j];
      cm_real_t copy_val = cm_mat_get(mat, i, j);
      TEST_ASSERT_EQUAL_FLOAT(source_val, copy_val);
    }
  }

  cm_mat_free(mat);
  for (size_t i = 0; i < source_rows; ++i) {
    free(source[i]);
  }
  free(source);
}

void test_create_from_arr_rows_0_cols_0() { create_from_arr_checker(0, 0); }
void test_create_from_arr_rows_1_cols_1() { create_from_arr_checker(1, 1); }
void test_create_from_arr_rows_1_cols_5() { create_from_arr_checker(1, 5); }
void test_create_from_arr_rows_5_cols_1() { create_from_arr_checker(5, 1); }
void test_create_from_arr_rows_50_cols_50() { create_from_arr_checker(50, 50); }
void test_create_from_arr_rows_250_cols_50() {
  create_from_arr_checker(250, 50);
}
void test_create_from_arr_rows_1000_cols_1000() {
  create_from_arr_checker(1000, 1000);
}

/************************** Column ****************************/

void create_col_checker(size_t source_rows, size_t source_cols,
                        size_t create_col) {

  cm_mat_t *source = cm_mat_alloc(source_rows, source_cols);
  TEST_ASSERT_NOT_NULL_MESSAGE(source, "malloc return NULL ptr.");

  for (size_t i = 0; i < source_rows; ++i) {
    for (size_t j = 0; j < source_cols; ++j) {
      cm_mat_set(source, i, j, i * 10 + j);
    }
  }

  cm_mat_t *mat = cm_mat_col(source, create_col);
  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  size_t copy_rows = cm_mat_rows(mat);
  size_t copy_cols = cm_mat_cols(mat);
  TEST_ASSERT_EQUAL_size_t(source_rows, copy_rows);
  TEST_ASSERT_EQUAL_size_t(1, copy_cols);

  for (size_t i = 0; i < copy_rows; ++i) {
    cm_real_t source_val = cm_mat_get(source, i, create_col);
    cm_real_t copy_val = cm_mat_get(mat, i, 0);
    TEST_ASSERT_EQUAL_FLOAT(source_val, copy_val);
  }

  cm_mat_free(mat);
  cm_mat_free(source);
}

void test_create_col_rows_1_cols_1() { create_col_checker(1, 1, 0); }
void test_create_col_rows_1_cols_5() { create_col_checker(1, 5, 2); }
void test_create_col_rows_5_cols_1() { create_col_checker(5, 1, 0); }
void test_create_col_rows_50_cols_50() { create_col_checker(50, 50, 24); }
void test_create_col_rows_100_cols_1() { create_col_checker(100, 1, 0); }
void test_create_col_rows_250_cols_50() { create_col_checker(250, 50, 5); }
void test_create_col_rows_1000_cols_1000() {
  create_col_checker(1000, 1000, 650);
}

/************************** Column ****************************/

void create_row_checker(size_t source_rows, size_t source_cols,
                        size_t create_row) {

  cm_mat_t *source = cm_mat_alloc(source_rows, source_cols);
  TEST_ASSERT_NOT_NULL_MESSAGE(source, "malloc return NULL ptr.");

  for (size_t i = 0; i < source_rows; ++i) {
    for (size_t j = 0; j < source_cols; ++j) {
      cm_mat_set(source, i, j, i * 10 + j);
    }
  }

  cm_mat_t *mat = cm_mat_row(source, create_row);
  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  size_t copy_rows = cm_mat_rows(mat);
  size_t copy_cols = cm_mat_cols(mat);
  TEST_ASSERT_EQUAL_size_t(1, copy_rows);
  TEST_ASSERT_EQUAL_size_t(source_cols, copy_cols);

  for (size_t i = 0; i < copy_cols; ++i) {
    cm_real_t source_val = cm_mat_get(source, create_row, i);
    cm_real_t copy_val = cm_mat_get(mat, 0, i);
    TEST_ASSERT_EQUAL_FLOAT(source_val, copy_val);
  }

  cm_mat_free(mat);
  cm_mat_free(source);
}

void test_create_row_rows_1_cols_1() { create_row_checker(1, 1, 0); }
void test_create_row_rows_1_cols_5() { create_row_checker(1, 5, 0); }
void test_create_row_rows_5_cols_1() { create_row_checker(5, 1, 2); }
void test_create_row_rows_50_cols_50() { create_row_checker(50, 50, 24); }
void test_create_row_rows_1_cols_100() { create_row_checker(1, 100, 0); }
void test_create_row_rows_250_cols_50() { create_row_checker(250, 50, 5); }
void test_create_row_rows_1000_cols_1000() {
  create_row_checker(1000, 1000, 650);
}

/************************** Submatrix ****************************/

void create_submatrix_checker(size_t source_rows, size_t source_cols,
                              size_t row_start, size_t row_end,
                              size_t col_start, size_t col_end) {

  cm_mat_t *source = cm_mat_alloc(source_rows, source_cols);
  TEST_ASSERT_NOT_NULL_MESSAGE(source, "malloc return NULL ptr.");

  for (size_t i = 0; i < source_rows; ++i) {
    for (size_t j = 0; j < source_cols; ++j) {
      cm_mat_set(source, i, j, i * 10 + j);
    }
  }

  cm_mat_t *mat = cm_mat_submat(source, row_start, row_end, col_start, col_end);
  TEST_ASSERT_NOT_NULL_MESSAGE(mat, "malloc return NULL ptr.");
  size_t copy_rows = cm_mat_rows(mat);
  size_t copy_cols = cm_mat_cols(mat);
  TEST_ASSERT_EQUAL_size_t(row_end - row_start + 1, copy_rows);
  TEST_ASSERT_EQUAL_size_t(col_end - col_start + 1, copy_cols);

  for (size_t i = 0; i < copy_rows; ++i) {
    for (size_t j = 0; j < copy_cols; ++j) {
      cm_real_t source_val = cm_mat_get(source, row_start + i, col_start + j);
      cm_real_t copy_val = cm_mat_get(mat, i, j);
      TEST_ASSERT_EQUAL_FLOAT(source_val, copy_val);
    }
  }

  cm_mat_free(mat);
  cm_mat_free(source);
}

void test_create_submatrix_rows_1_cols_1() {
  create_submatrix_checker(1, 1, 0, 0, 0, 0);
}
void test_create_submatrix_rows_1_cols_5() {
  create_submatrix_checker(1, 5, 0, 0, 0, 2);
}
void test_create_submatrix_rows_5_cols_1() {
  create_submatrix_checker(5, 1, 0, 2, 0, 0);
}
void test_create_submatrix_rows_50_cols_50() {
  create_submatrix_checker(50, 50, 20, 25, 5, 10);
}
void test_create_submatrix_rows_100_cols_100() {
  create_submatrix_checker(100, 100, 0, 99, 0, 99);
}
void test_create_submatrix_rows_250_cols_50() {
  create_submatrix_checker(250, 50, 10, 200, 5, 25);
}
void test_create_submatrix_rows_1000_cols_1000() {
  create_submatrix_checker(1000, 1000, 0, 999, 0, 999);
}

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

  puts("**********Test create identity**********");
  RUN_TEST(test_create_identity_size_0);
  RUN_TEST(test_create_identity_size_1);
  RUN_TEST(test_create_identity_size_5);
  RUN_TEST(test_create_identity_size_25);
  RUN_TEST(test_create_identity_size_50);
  RUN_TEST(test_create_identity_size_250);
  RUN_TEST(test_create_identity_size_1000);

  puts("**********Test create diagonal**********");
  RUN_TEST(test_create_diag_size_0_init_val_5);
  RUN_TEST(test_create_diag_size_1_init_val_10);
  RUN_TEST(test_create_diag_size_5_init_val_2);
  RUN_TEST(test_create_diag_size_25_init_val_100);
  RUN_TEST(test_create_diag_size_50_init_val_140);
  RUN_TEST(test_create_diag_size_250_init_val_250);
  RUN_TEST(test_create_diag_size_1000_init_val_1000);

  puts("**********Test create copy**********");
  RUN_TEST(test_create_copy_rows_0_cols_0);
  RUN_TEST(test_create_copy_rows_1_cols_1);
  RUN_TEST(test_create_copy_rows_1_cols_5);
  RUN_TEST(test_create_copy_rows_5_cols_1);
  RUN_TEST(test_create_copy_rows_50_cols_50);
  RUN_TEST(test_create_copy_rows_250_cols_50);
  RUN_TEST(test_create_copy_rows_1000_cols_1000);

  puts("**********Test create from array**********");
  RUN_TEST(test_create_from_arr_rows_0_cols_0);
  RUN_TEST(test_create_from_arr_rows_1_cols_1);
  RUN_TEST(test_create_from_arr_rows_1_cols_5);
  RUN_TEST(test_create_from_arr_rows_5_cols_1);
  RUN_TEST(test_create_from_arr_rows_50_cols_50);
  RUN_TEST(test_create_from_arr_rows_250_cols_50);
  RUN_TEST(test_create_from_arr_rows_1000_cols_1000);

  puts("**********Test create column**********");
  RUN_TEST(test_create_col_rows_1_cols_1);
  RUN_TEST(test_create_col_rows_1_cols_5);
  RUN_TEST(test_create_col_rows_5_cols_1);
  RUN_TEST(test_create_col_rows_50_cols_50);
  RUN_TEST(test_create_col_rows_100_cols_1);
  RUN_TEST(test_create_col_rows_250_cols_50);
  RUN_TEST(test_create_col_rows_1000_cols_1000);

  puts("**********Test create row**********");
  RUN_TEST(test_create_row_rows_1_cols_1);
  RUN_TEST(test_create_row_rows_1_cols_5);
  RUN_TEST(test_create_row_rows_5_cols_1);
  RUN_TEST(test_create_row_rows_50_cols_50);
  RUN_TEST(test_create_row_rows_1_cols_100);
  RUN_TEST(test_create_row_rows_250_cols_50);
  RUN_TEST(test_create_row_rows_1000_cols_1000);

  puts("**********Test create submatrix**********");
  RUN_TEST(test_create_submatrix_rows_1_cols_1);
  RUN_TEST(test_create_submatrix_rows_1_cols_5);
  RUN_TEST(test_create_submatrix_rows_5_cols_1);
  RUN_TEST(test_create_submatrix_rows_50_cols_50);
  RUN_TEST(test_create_submatrix_rows_100_cols_100);
  RUN_TEST(test_create_submatrix_rows_250_cols_50);
  RUN_TEST(test_create_submatrix_rows_1000_cols_1000);

  return UNITY_END();
}
