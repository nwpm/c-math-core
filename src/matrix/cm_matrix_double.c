#include "cm_matrix_double.h"
#include "../utils/cm_checkers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make NULL check or not?
// TODO: error handler
// TODO: return codes only in debug build or return codes only in some
// functiuons

#ifdef DEBUG
void _cm_matrix_double_printf(const CmMatrixDouble *matrix) {

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      printf("%f ", matrix->data[i * matrix->columns + j]);
    }
    putchar('\n');
  }
}
#else
void _cm_matrix_double_printf(const CmMatrixDouble *matrix) { (void)matrix; }
#endif

#define CM_GET_MATRIX_ELEM(matrix, row, column)                                \
  ((matrix)->data[(row) * (matrix)->columns + (column)])

static void matrix_double_mult_row(CmMatrixDouble *matrix, size_t row,
                                   double mult_by) {
  for (size_t i = 0; i < matrix->columns; ++i) {
    matrix->data[row * matrix->columns + i] *= mult_by;
  }
}

static double cm_matrix_double_det_less_3(const CmMatrixDouble *matrix) {

  double det_out = 0.;

  if (matrix->rows == 1) {
    det_out = matrix->data[0];
  } else if (matrix->rows == 2) {
    det_out = (matrix->data[0] * matrix->data[3]) -
              (matrix->data[1] * matrix->data[2]);
  } else if (matrix->rows == 3) {
    det_out = (matrix->data[0] * matrix->data[4] * matrix->data[8]) +
              (matrix->data[1] * matrix->data[5] * matrix->data[6]) +
              (matrix->data[2] * matrix->data[3] * matrix->data[7]) -
              (matrix->data[2] * matrix->data[4] * matrix->data[6]) -
              (matrix->data[1] * matrix->data[3] * matrix->data[8]) -
              (matrix->data[0] * matrix->data[5] * matrix->data[7]);
  }
  return det_out;
}

CmMatrixDouble *cm_matrix_double_alloc(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = malloc(sizeof(CmMatrixDouble));

  if (!matrix)
    return NULL;

  double *data = malloc(sizeof(double) * rows * cols);

  if (!data) {
    free(matrix);
    return NULL;
  }

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixDouble *cm_matrix_double_calloc(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = malloc(sizeof(CmMatrixDouble));

  if (!matrix)
    return NULL;

  double *data = calloc(rows * cols, sizeof(double));

  if (!data) {
    free(matrix);
    return NULL;
  }

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

// TODO: use memcpy instead for
CmMatrixDouble *
cm_matrix_double_create_from_matrix(const CmMatrixDouble *orig_matrix) {

  if (!orig_matrix || !orig_matrix->data || orig_matrix->columns == 0 ||
      orig_matrix->rows == 0)
    return NULL;

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_alloc(orig_matrix->rows, orig_matrix->columns);

  if (!copy_matrix) {
    return NULL;
  }

  for (size_t i = 0; i < copy_matrix->rows; ++i) {
    for (size_t j = 0; j < copy_matrix->columns; ++j) {
      copy_matrix->data[i * copy_matrix->columns + j] =
          orig_matrix->data[i * orig_matrix->columns + j];
    }
  }

  return copy_matrix;
}

CmMatrixDouble *cm_matrix_double_create_from_array(const double **arr,
                                                   size_t rows, size_t cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);

  if (!matrix)
    return NULL;

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cm_matrix_double_set(matrix, i, j, arr[i][j]);
    }
  }

  return matrix;
}

CmStatusCode cm_matrix_double_swap(CmMatrixDouble **matrix_a,
                                   CmMatrixDouble **matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);

  CmMatrixDouble *tmp = *matrix_a;
  *matrix_a = *matrix_b;
  *matrix_b = tmp;

  return CM_SUCCESS;
}

// TODO: memset optimuzation
CmStatusCode cm_matrix_double_set_identity(CmMatrixDouble *matrix) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);
  CM_MATRIX_BUFF_NULL_CHECK(matrix);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (i == j) {
        matrix->data[i * matrix->columns + j] = 1;
      } else {
        matrix->data[i * matrix->columns + j] = 0;
      }
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_set_zero(CmMatrixDouble *matrix) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_BUFF_NULL_CHECK(matrix);

  memset(matrix->data, 0, sizeof(double) * matrix->rows * matrix->columns);

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_set_all(CmMatrixDouble *matrix, double x) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_BUFF_NULL_CHECK(matrix);

  if (x == 0.) {
    cm_matrix_double_set_zero(matrix);
    return CM_SUCCESS;
  }

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    matrix->data[i] = x;
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_max(const CmMatrixDouble *matrix,
                                  double *max_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(max_out);

  *max_out = matrix->data[0];

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (matrix->data[i * matrix->columns + j] > *max_out)
        *max_out = matrix->data[i * matrix->columns + j];
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_min(const CmMatrixDouble *matrix,
                                  double *min_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(min_out);

  *min_out = matrix->data[0];

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (matrix->data[i * matrix->columns + j] < *min_out)
        *min_out = matrix->data[i * matrix->columns + j];
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_transpose(CmMatrixDouble **matrix) {

  CM_CHECK_NULL(matrix);

  CmMatrixDouble *tmp_matrix =
      cm_matrix_double_alloc((*matrix)->columns, (*matrix)->rows);

  if (!tmp_matrix) {
    return CM_ERR_ALLOC_FAILED;
  }

  for (size_t i = 0; i < (*matrix)->rows; ++i) {
    for (size_t j = 0; j < (*matrix)->columns; ++j) {
      tmp_matrix->data[j * (*matrix)->rows + i] =
          (*matrix)->data[i * (*matrix)->columns + j];
    }
  }

  cm_matrix_double_free(*matrix);
  *matrix = tmp_matrix;

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_trace(const CmMatrixDouble *matrix,
                                    double *trace_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(trace_out);
  CM_MATRIX_SQUARE_CHECK(matrix);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (i == j) {
        *trace_out += matrix->data[i * matrix->columns + j];
      }
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_det(const CmMatrixDouble *matrix,
                                  double *det_out) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);

  if (matrix->columns <= 3) {
    *det_out = cm_matrix_double_det_less_3(matrix);
    return CM_SUCCESS;
  }

  CmMatrixDouble *copy_matrix = cm_matrix_double_create_from_matrix(matrix);
  CM_CHECK_NULL(copy_matrix);

  double *mult_constants = malloc(copy_matrix->columns * sizeof(double));
  if (!mult_constants)
    return CM_ERR_ALLOC_FAILED;

  int mult_const_index = 0;
  int swap_number = 0;

  for (size_t k = 0; k < copy_matrix->rows - 1; ++k) {

    double pivot = cm_matrix_double_get(copy_matrix, k, k);
    if (pivot == 0) {

      bool find_non_zero = false;

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (cm_matrix_double_get(copy_matrix, i, k) != 0) {

          find_non_zero = true;
          void *buffer = malloc(copy_matrix->columns * sizeof(double));

          if (!buffer)
            return CM_ERR_ALLOC_FAILED;

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);

          swap_number++;
        }
      }

      if (!find_non_zero) {
        *det_out = 0;
        cm_matrix_double_free(copy_matrix);
        free(mult_constants);
        return CM_SUCCESS;
      }
    }

    matrix_double_mult_row(copy_matrix, k, (1. / pivot));

    mult_constants[mult_const_index++] = pivot;

    for (size_t i = k + 1; i < copy_matrix->rows; ++i) {
      double deleted = -cm_matrix_double_get(copy_matrix, i, k);
      for (size_t j = 0; j < copy_matrix->columns; ++j) {
        double set_elem = cm_matrix_double_get(copy_matrix, k, j) * deleted +
                          cm_matrix_double_get(copy_matrix, i, j);
        cm_matrix_double_set(copy_matrix, i, j, set_elem);
      }
    }
  }

  double mult = (swap_number % 2 == 0) ? 1 : -1;

  *det_out = mult * cm_matrix_double_get(copy_matrix, copy_matrix->rows - 1,
                                         copy_matrix->rows - 1);

  for (int i = 0; i < mult_const_index; ++i) {
    *det_out *= mult_constants[i];
  }

  cm_matrix_double_free(copy_matrix);
  free(mult_constants);

  return CM_SUCCESS;
}

CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix) {

  if (!orig_matrix || (orig_matrix->rows != orig_matrix->columns)) {
    return NULL;
  }

  double det = 0.;
  cm_matrix_double_det(orig_matrix, &det);
  if (det == 0.)
    return NULL;

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_create_from_matrix(orig_matrix);
  if (!copy_matrix) {
    return NULL;
  }

  CmMatrixDouble *res_matrix =
      cm_matrix_double_alloc(orig_matrix->rows, orig_matrix->columns);
  if (!res_matrix) {
    return NULL;
  }
  cm_matrix_double_set_identity(res_matrix);

  for (size_t k = 0; k < copy_matrix->columns; ++k) {

    double pivot = copy_matrix->data[k * copy_matrix->columns + k];

    if (pivot == 0.) {
      bool find_non_zero = false;

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++k) {
        if (copy_matrix->data[i * copy_matrix->columns + k] != 0) {

          find_non_zero = true;
          void *buffer = malloc(copy_matrix->columns * sizeof(double));

          if (!buffer)
            return NULL;

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);

          memcpy(buffer, res_matrix->data + (i * res_matrix->columns),
                 sizeof(double) * res_matrix->columns);

          memmove(res_matrix->data + (i * res_matrix->columns),
                  res_matrix->data + (k * res_matrix->columns),
                  sizeof(double) * res_matrix->columns);

          memmove(res_matrix->data + (k * res_matrix->columns), buffer,
                  sizeof(double) * res_matrix->columns);
        }
      }

      if (!find_non_zero) {
        return NULL;
      }
    }

    matrix_double_mult_row(copy_matrix, k, 1. / (pivot));
    matrix_double_mult_row(res_matrix, k, 1. / (pivot));

    for (size_t j = 0; j < copy_matrix->rows; ++j) {
      if (j == k)
        continue;

      double pivot = copy_matrix->data[j * copy_matrix->columns + k];

      for (size_t i = 0; i < copy_matrix->columns; ++i) {
        copy_matrix->data[j * copy_matrix->columns + i] =
            (copy_matrix->data[k * copy_matrix->columns + i] * pivot * -1.) +
            copy_matrix->data[j * copy_matrix->columns + i];

        res_matrix->data[j * res_matrix->columns + i] =
            (res_matrix->data[k * res_matrix->columns + i] * pivot * -1.) +
            res_matrix->data[j * res_matrix->columns + i];
      }
    }
  }

  cm_matrix_double_free(copy_matrix);

  return res_matrix;
}

CmStatusCode cm_matrix_double_minor(const CmMatrixDouble *matrix, size_t row,
                                    size_t col, double *minor_out) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);

  if (matrix->rows == 0 && matrix->columns == 0)
    return CM_ERR_ZERO_MATRIX;

  if (row > matrix->rows || col > matrix->columns)
    return CM_ERR_WRONG_POS;

  CmMatrixDouble *block_matrix =
      cm_matrix_double_alloc(matrix->rows - 1, matrix->columns - 1);

  size_t block_i = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {
    if (i == row)
      continue;

    size_t block_j = 0;
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (j == col)
        continue;

      double elem = cm_matrix_double_get(matrix, i, j);
      cm_matrix_double_set(block_matrix, block_i, block_j++, elem);
    }
    ++block_i;
  }

  cm_matrix_double_det(block_matrix, minor_out);

  cm_matrix_double_free(block_matrix);

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_cofactor(const CmMatrixDouble *matrix, size_t row,
                                       size_t col, double *cofactor_out) {

  double sign = 1;
  if ((row + col) && 0x1) {
    sign = -1.;
  }

  double minor = 0.;
  CmStatusCode res = cm_matrix_double_minor(matrix, row, col, &minor);
  *cofactor_out = sign * minor;

  return res;
}

CmStatusCode cm_matrix_double_pow(CmMatrixDouble **matrix, unsigned exp) {

  if (!matrix)
    return CM_ERR_NULL_POINTER;

  if (exp == 1)
    return CM_SUCCESS;
  else if (exp == 0) {
    cm_matrix_double_set_zero(*matrix);
    return CM_SUCCESS;
  }

  CmMatrixDouble *res =
      cm_matrix_double_alloc((*matrix)->rows, (*matrix)->columns);
  if (!res)
    return CM_ERR_ALLOC_FAILED;

  cm_matrix_double_set_identity(res);

  while (exp > 0) {
    if (exp & 0x1) {
      CmMatrixDouble *tmp = cm_matrix_double_mul(res, *matrix);
      if (!tmp) {
        cm_matrix_double_free(res);
        return CM_ERR_ALLOC_FAILED;
      }
      cm_matrix_double_free(res);
      res = tmp;
    }
    CmMatrixDouble *tmp = cm_matrix_double_mul(*matrix, *matrix);
    if (!tmp) {
      cm_matrix_double_free(res);
      return CM_ERR_ALLOC_FAILED;
    }
    cm_matrix_double_free(*matrix);
    *matrix = tmp;
    exp /= 2;
  }

  for (size_t i = 0; i < (*matrix)->rows; ++i) {
    for (size_t j = 0; j < (*matrix)->columns; ++j) {
      cm_matrix_double_set(*matrix, i, j, cm_matrix_double_get(res, i, j));
    }
  }

  cm_matrix_double_free(res);

  return CM_SUCCESS;
}

bool cm_matrix_double_is_null(const CmMatrixDouble *matrix) {

  if (!matrix)
    return false;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (matrix->data[i * matrix->columns + j] != 0) {
        return false;
      }
    }
  }

  return true;
}

bool cm_matrix_double_is_identity(const CmMatrixDouble *matrix) {

  if (!matrix)
    return false;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      double current_elem = matrix->data[i * matrix->columns + j];
      if (i == j && current_elem != 1) {
        return false;
      } else if (i != j && current_elem != 0) {
        return false;
      }
    }
  }

  return true;
}

bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b) {

  if (!matrix_a || !matrix_b)
    return false;

  if ((matrix_a->rows != matrix_b->rows) ||
      (matrix_a->columns != matrix_b->columns))
    return false;

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      if (matrix_a->data[i * matrix_a->columns + j] !=
          matrix_b->data[i * matrix_b->columns + j])
        return false;
    }
  }

  return true;
}

CmStatusCode cm_matrix_double_add(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_MATRIX_SIZE_MATCH(matrix_a, matrix_b);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      matrix_a->data[i * matrix_a->columns + j] +=
          matrix_b->data[i * matrix_b->columns + j];
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_sub(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_MATRIX_SIZE_MATCH(matrix_a, matrix_b);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      matrix_a->data[i * matrix_a->columns + j] -=
          matrix_b->data[i * matrix_b->columns + j];
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_scale(CmMatrixDouble *matrix_a, double scale) {

  CM_CHECK_NULL(matrix_a);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      matrix_a->data[i * matrix_a->columns + j] *= scale;
    }
  }

  return CM_SUCCESS;
}

CmMatrixDouble *cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                                     const CmMatrixDouble *matrix_b) {

  if (!matrix_a || !matrix_b)
    return NULL;
  if (matrix_a->columns != matrix_b->rows)
    return NULL;

  CmMatrixDouble *result =
      cm_matrix_double_alloc(matrix_a->rows, matrix_b->columns);

  if (!result)
    return NULL;

  for (size_t i = 0; i < result->rows; ++i) {
    for (size_t k = 0; k < result->columns; ++k) {
      double result_elem = 0;
      for (size_t j = 0; j < matrix_a->columns; ++j) {
        result_elem += cm_matrix_double_get(matrix_a, i, j) *
                       cm_matrix_double_get(matrix_b, j, k);
      }
      cm_matrix_double_set(result, i, k, result_elem);
    }
  }

  return result;
}

CmStatusCode cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix,
                                    double *res) {
  CM_CHECK_NULL(augmented_matrix);
  CM_CHECK_NULL(res);

  if (augmented_matrix->rows != (augmented_matrix->columns - 1)) {
    return CM_ERR_INVALID_SIZE;
  }

  double matrix_det = 0.;
  cm_matrix_double_det(augmented_matrix, &matrix_det);
  if (matrix_det == 0)
    return CM_ERR_SINGULAR_MATRIX;

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_create_from_matrix(augmented_matrix);
  if (!copy_matrix) {
    return CM_ERR_ALLOC_FAILED;
  }

  for (size_t k = 0; k < copy_matrix->columns; ++k) {

    double pivot = copy_matrix->data[k * copy_matrix->columns + k];

    if (pivot == 0.) {
      bool find_non_zero = false;

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++k) {
        if (copy_matrix->data[i * copy_matrix->columns + k] != 0) {

          find_non_zero = true;
          void *buffer = malloc(copy_matrix->columns * sizeof(double));

          if (!buffer)
            return CM_ERR_ALLOC_FAILED;

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);
        }
      }

      if (!find_non_zero) {
        return CM_FAIL;
      }
    }

    matrix_double_mult_row(copy_matrix, k, 1. / (pivot));

    for (size_t j = 0; j < copy_matrix->rows; ++j) {
      if (j == k)
        continue;

      double pivot = copy_matrix->data[j * copy_matrix->columns + k];

      for (size_t i = 0; i < copy_matrix->columns; ++i) {
        copy_matrix->data[j * copy_matrix->columns + i] =
            (copy_matrix->data[k * copy_matrix->columns + i] * pivot * -1.) +
            copy_matrix->data[j * copy_matrix->columns + i];
      }
    }
  }

  for (size_t i = 0; i < copy_matrix->rows; ++i) {
    res[i] = cm_matrix_double_get(copy_matrix, i, copy_matrix->columns - 1);
  }

  cm_matrix_double_free(copy_matrix);

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_free(CmMatrixDouble *matrix) {
  if (!matrix)
    return CM_ERR_NULL_POINTER;
  free(matrix->data);
  free(matrix);
  return CM_SUCCESS;
}
