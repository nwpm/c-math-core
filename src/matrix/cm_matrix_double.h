#ifndef CM_MATRIX_INT_H
#define CM_MATRIX_INT_H

#include <stdbool.h>
#include <stddef.h>

// TODO: create_row_from_matrix
// TODO: create_col_from_matrix
// TODO: minor, gauss
// TODO: tests

typedef enum CmMatrixCode {

  CM_SUCCESS = 0,
  CM_FAIL,
  CM_ERR_WRONG_POS,
  CM_ERR_NULL_POINTER,
  CM_ERR_SIZE_MISMATCH,
  CM_ERR_MULT_SIZE_MISMATCH,
  CM_ERR_MATRIX_NOT_SQUARE,
  CM_ERR_ALLOC_FAILED,
  CM_ERR_INVALID_SIZE,
  CM_ERR_INVALID_ARGUMENT,
  CM_ERR_ZERO_MATRIX

} CmMatrixCode;

typedef struct CmMatrixDouble {
  size_t rows;
  size_t columns;
  double *data;
} CmMatrixDouble;

/* Allocation */

CmMatrixDouble *cm_matrix_double_alloc(size_t rows, size_t cols);
CmMatrixDouble *cm_matrix_double_calloc(size_t rows, size_t cols);

CmMatrixDouble *
cm_matrix_double_create_from_matrix(const CmMatrixDouble *orig_matrix);
CmMatrixDouble *cm_matrix_double_create_from_array(const double **arr,
                                                   size_t rows, size_t cols);

void cm_matrix_double_free(CmMatrixDouble *matrix);

/* Operations */

CmMatrixCode cm_matrix_double_set_identity(CmMatrixDouble *matrix);
CmMatrixCode cm_matrix_double_set_zero(CmMatrixDouble *matrix);
CmMatrixCode cm_matrix_double_set_all(CmMatrixDouble *matrix, double x);
CmMatrixCode cm_matrix_double_swap(CmMatrixDouble **matrix_a,
                                   CmMatrixDouble **matrix_b);
CmMatrixCode cm_matrix_double_transpose(CmMatrixDouble **matrix);

CmMatrixCode cm_matrix_double_max(const CmMatrixDouble *matrix,
                                  double *max_out);
CmMatrixCode cm_matrix_double_min(const CmMatrixDouble *matrix,
                                  double *min_out);
CmMatrixCode cm_matrix_double_trace(const CmMatrixDouble *matrix,
                                    double *trace_out);
CmMatrixCode cm_matrix_double_det(const CmMatrixDouble *matrix,
                                  double *det_out);

bool cm_matrix_double_is_null(const CmMatrixDouble *matrix);
bool cm_matrix_double_is_identity(const CmMatrixDouble *matrix);
bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b);

CmMatrixCode cm_matrix_double_add(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b);
CmMatrixCode cm_matrix_double_sub(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b);
CmMatrixCode cm_matrix_double_scale(CmMatrixDouble *matrix_a, double scale);
CmMatrixDouble *cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                                     const CmMatrixDouble *matrix_b);

CmMatrixCode cm_matrix_double_pow(CmMatrixDouble **matrix, unsigned exp);

/* Inverse */
CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix);

/* Minor */
CmMatrixCode cm_matrix_double_minor(const CmMatrixDouble *matrix, size_t row,
                                    size_t col, double *minor_out);

/* Cofactor */
CmMatrixCode cm_matrix_double_cofactor(const CmMatrixDouble *matrix, size_t row,
                                       size_t col, double *cofactor_out);

/* Gauss-Jordan */
CmMatrixCode cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix,
                                    double *res);

/* Getter/Setter */

static inline double cm_matrix_double_get(const CmMatrixDouble *matrix,
                                          size_t row, size_t col) {
  return matrix->data[row * matrix->columns + col];
}

static inline void cm_matrix_double_set(CmMatrixDouble *matrix, size_t row,
                                        size_t col, double x) {
  matrix->data[row * matrix->columns + col] = x;
}

/* Debug */
void _cm_matrix_double_printf(const CmMatrixDouble *matrix);

#endif
