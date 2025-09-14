#include "cm_matrix_int.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: make NULL check or not?
// TODO: error handler
// TODO: return codes only in debug build or return codes only in some
// functiuons
// TODO: use get, set instead row getting, setting

#ifdef DEBUG
void _cm_matrix_int_printf(const CmMatrixInt *matrix) {

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      printf("%d ", matrix->data[i * matrix->columns + j]);
    }
    putchar('\n');
  }
}
#else
void _cm_matrix_int_printf(const CmMatrixInt *matrix) { (void)matrix; }
#endif

#define CM_CHECK_NULL(ptr)                                                     \
  do {                                                                         \
    if ((ptr) == NULL) {                                                       \
      return CM_ERR_NULL_POINTER;                                              \
    }                                                                          \
  } while (0)

#define CM_SQUARE_CHECK(matrix)                                                \
  do {                                                                         \
    if ((matrix->rows) != (matrix->columns)) {                                 \
      return CM_ERR_MATRIX_NOT_SQUARE;                                         \
    }                                                                          \
  } while (0)

#define CM_SIZE_MATCH(matrix_a, matrix_b)                                      \
  do {                                                                         \
    if (((matrix_a->rows) != (matrix_b->rows)) ||                              \
        ((matrix_a->columns) != (matrix_b->columns))) {                        \
      return CM_ERR_SIZE_MISMATCH;                                             \
    }                                                                          \
  } while (0)

#define CM_MULT_SIZE_MATCH(matrix_a, matrix_b)                                 \
  do {                                                                         \
    if (((matrix_a->columns) != (matrix_b->rows))) {                           \
      return CM_ERR_MULT_SIZE_MISMATCH;                                        \
    }                                                                          \
  } while (0)

CmMatrixInt *cm_matrix_int_alloc(size_t rows, size_t cols) {

  CmMatrixInt *matrix = malloc(sizeof(CmMatrixInt));

  if (!matrix)
    return NULL;

  int *data = malloc(sizeof(int) * rows * cols);

  if (!data) {
    free(matrix);
    return NULL;
  }

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixInt *cm_matrix_int_calloc(size_t rows, size_t cols) {

  CmMatrixInt *matrix = malloc(sizeof(CmMatrixInt));

  if (!matrix)
    return NULL;

  int *data = calloc(rows * cols, sizeof(int));

  if (!data) {
    free(matrix);
    return NULL;
  }

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixInt *cm_matrix_int_create_from_matrix(const CmMatrixInt *orig_matrix) {

  CmMatrixInt *copy_matrix =
      cm_matrix_int_alloc(orig_matrix->rows, orig_matrix->columns);

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

int cm_matrix_int_swap(CmMatrixInt **matrix_a, CmMatrixInt **matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);

  CmMatrixInt *tmp = *matrix_a;
  *matrix_a = *matrix_b;
  *matrix_b = tmp;

  return CM_SUCCESS;
}

int cm_matrix_int_set_identity(CmMatrixInt *matrix) {

  CM_CHECK_NULL(matrix);
  CM_SQUARE_CHECK(matrix);

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

int cm_matrix_int_set_zero(CmMatrixInt *matrix) {

  CM_CHECK_NULL(matrix);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      matrix->data[i * matrix->columns + j] = 0;
    }
  }

  return CM_SUCCESS;
}

int cm_matrix_int_set_all(CmMatrixInt *matrix, int x) {

  CM_CHECK_NULL(matrix);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      matrix->data[i * matrix->columns + j] = x;
    }
  }

  return CM_SUCCESS;
}

int cm_matrix_int_max(const CmMatrixInt *matrix, int *max_out) {

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

int cm_matrix_int_min(const CmMatrixInt *matrix, int *min_out) {

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

int cm_matrix_int_transpose(CmMatrixInt *matrix) {

  CM_CHECK_NULL(matrix);

  CmMatrixInt *tmp_matrix = cm_matrix_int_calloc(matrix->columns, matrix->rows);

  // NOTE: separate macro?
  if (!tmp_matrix) {
    return CM_ERR_ALLOC_FAILED;
  }

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      tmp_matrix->data[j * matrix->rows + i] =
          matrix->data[i * matrix->columns + j];
    }
  }

  return CM_SUCCESS;
}

int cm_matrix_int_trace(const CmMatrixInt *matrix, int *trace_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(trace_out);
  CM_SQUARE_CHECK(matrix);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (i == j) {
        *trace_out += matrix->data[i * matrix->columns + j];
      }
    }
  }

  return CM_SUCCESS;
}

// Bareiss
int cm_matrix_int_det(const CmMatrixInt *matrix, int *det_out) {

  CM_CHECK_NULL(matrix);
  CM_SQUARE_CHECK(matrix);

  if (matrix->rows == 2) {
    *det_out = (matrix->data[0] * matrix->data[3]) -
               (matrix->data[1] * matrix->data[2]);
    return CM_SUCCESS;
  }

  CmMatrixInt *copy_matrix = cm_matrix_int_create_from_matrix(matrix);
  CM_CHECK_NULL(copy_matrix);

  int d = 1;

  for (size_t k = 0; k < copy_matrix->rows - 1; ++k) {
    int pivot = copy_matrix->data[k * copy_matrix->columns + k];
    if (pivot == 0) {
      // swap
    }
    for (size_t i = k + 1; i < copy_matrix->rows; ++i) {
      for (size_t j = k + 1; j < copy_matrix->columns; ++j) {

        int elem1 = copy_matrix->data[i * copy_matrix->columns + j];
        int elem2 = copy_matrix->data[i * copy_matrix->columns + k];
        int elem3 = copy_matrix->data[k * copy_matrix->columns + j];

        copy_matrix->data[i * copy_matrix->columns + j] =
            (pivot * elem1 - elem2 * elem3) / d;
      }
    }
    for (size_t n = k + 1; n < copy_matrix->rows; ++n) {
      copy_matrix->data[n * copy_matrix->columns + k] = 0;
    }
    d = pivot;
  }

  *det_out = cm_matrix_int_get(copy_matrix, copy_matrix->rows - 1,
                               copy_matrix->columns - 1);

  cm_matrix_int_free(copy_matrix);

  return CM_SUCCESS;
}

bool cm_matrix_int_is_null(const CmMatrixInt *matrix) {

  if (!matrix)
    return false;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (matrix->data[i * matrix->columns + j] == 0) {
        return false;
      }
    }
  }

  return true;
}

bool cm_matrix_int_is_identity(const CmMatrixInt *matrix) {

  if (!matrix)
    return false;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      int current_elem = matrix->data[i * matrix->columns + j];
      if (i == j && current_elem != 1) {
        return false;
      } else if (i != j && current_elem != 0) {
        return false;
      }
    }
  }

  return true;
}

bool cm_matrix_int_is_equal(const CmMatrixInt *matrix_a,
                            const CmMatrixInt *matrix_b) {

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

int cm_matrix_int_add(CmMatrixInt *matrix_a, const CmMatrixInt *matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_SIZE_MATCH(matrix_a, matrix_b);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      matrix_a->data[i * matrix_a->columns + j] +=
          matrix_b->data[i * matrix_b->columns + j];
    }
  }

  return CM_SUCCESS;
}

int cm_matrix_int_sub(CmMatrixInt *matrix_a, const CmMatrixInt *matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_SIZE_MATCH(matrix_a, matrix_b);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      matrix_a->data[i * matrix_a->columns + j] -=
          matrix_b->data[i * matrix_b->columns + j];
    }
  }

  return CM_SUCCESS;
}

int cm_matrix_int_scale(CmMatrixInt *matrix_a, int scale) {

  CM_CHECK_NULL(matrix_a);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      matrix_a->data[i * matrix_a->columns + j] *= scale;
    }
  }

  return CM_SUCCESS;
}

CmMatrixInt *cm_matrix_int_mul(const CmMatrixInt *matrix_a,
                               const CmMatrixInt *matrix_b) {

  if (!matrix_a || !matrix_b)
    return NULL;
  if (matrix_a->columns != matrix_b->rows)
    return NULL;

  CmMatrixInt *result = cm_matrix_int_alloc(matrix_a->rows, matrix_b->columns);

  if (!result)
    return NULL;

  // size_t set_row = 0;
  // size_t set_column = 0;

  for (size_t i = 0; i < result->rows; ++i) {
    for (size_t k = 0; k < result->columns; ++k) {
      int result_elem = 0;
      for (size_t j = 0; j < result->columns; ++j) {
        result_elem += cm_matrix_int_get(matrix_a, i, j) *
                       cm_matrix_int_get(matrix_b, j, k);
      }
      cm_matrix_int_set(result, i, k, result_elem);
    }
  }

  return NULL;
}

void cm_matrix_int_free(CmMatrixInt *matrix) {
  free(matrix->data);
  free(matrix);
}
