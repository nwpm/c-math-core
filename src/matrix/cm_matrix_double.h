#ifndef CM_MATRIX_INT_H
#define CM_MATRIX_INT_H

#include <stdbool.h>
#include <stddef.h>

// TODO: create_row_from_matrix
// TODO: create_col_from_matrix
// TODO: invers, minor, gauss
// TODO: tests

typedef enum {

  CM_SUCCESS = 0,
  CM_FAIL,
  CM_ERR_NULL_POINTER,
  CM_ERR_SIZE_MISMATCH,
  CM_ERR_MULT_SIZE_MISMATCH,
  CM_ERR_MATRIX_NOT_SQUARE,
  CM_ERR_ALLOC_FAILED,
  CM_ERR_INVALID_ARGUMENT,

} CmErrorCode;

typedef struct CmMatrixDouble {
  size_t rows;
  size_t columns;
  double *data;
} CmMatrixDouble;

/* Allocation */

CmMatrixDouble *cm_matrix_double_alloc(size_t rows, size_t cols);
CmMatrixDouble *cm_matrix_double_calloc(size_t rows, size_t cols);

CmMatrixDouble *cm_matrix_double_create_from_matrix(const CmMatrixDouble *orig_matrix);

void cm_matrix_double_free(CmMatrixDouble *matrix);

/* Operations */

int cm_matrix_double_set_identity(CmMatrixDouble *matrix);
int cm_matrix_double_set_zero(CmMatrixDouble *matrix);
int cm_matrix_double_set_all(CmMatrixDouble *matrix, double x);
int cm_matrix_double_swap(CmMatrixDouble **matrix_a, CmMatrixDouble **matrix_b);
int cm_matrix_double_transpose(CmMatrixDouble *matrix);

int cm_matrix_double_max(const CmMatrixDouble *matrix, double *max_out);
int cm_matrix_double_min(const CmMatrixDouble *matrix, double *min_out);
int cm_matrix_double_trace(const CmMatrixDouble *matrix, double *trace_out);
int cm_matrix_double_det(const CmMatrixDouble *matrix, double *det_out);

bool cm_matrix_double_is_null(const CmMatrixDouble *matrix);
bool cm_matrix_double_is_identity(const CmMatrixDouble *matrix);
bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                            const CmMatrixDouble *matrix_b);

int cm_matrix_double_add(CmMatrixDouble *matrix_a, const CmMatrixDouble *matrix_b);
int cm_matrix_double_sub(CmMatrixDouble *matrix_a, const CmMatrixDouble *matrix_b);
int cm_matrix_double_scale(CmMatrixDouble *matrix_a, double scale);
CmMatrixDouble *cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b);

CmMatrixDouble *cm_matrix_double_pow(const CmMatrixDouble *base_matrix, double exponent);

/* Inverse */
CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix);

/* Minor */
CmMatrixDouble *cm_matrix_double_minor(const CmMatrixDouble *orig_matrix);

/* Gauss-Jordan */
double *cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix);

/* Getter/Setter */

static inline double cm_matrix_double_get(const CmMatrixDouble *matrix, size_t row,
                                    size_t col) {
  return matrix->data[row * matrix->columns + col];
}

static inline void cm_matrix_double_set(CmMatrixDouble *matrix, size_t row,
                                     size_t col, double x) {
  matrix->data[row * matrix->columns + col] = x;
}

/* Debug */
void _cm_matrix_double_printf(const CmMatrixDouble *matrix);

#endif
