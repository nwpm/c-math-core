#ifndef CM_CHECKERS_H
#define CM_CHECKERS_H

#include "cm_err_codes.h"

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

#endif
