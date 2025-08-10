#ifndef CM_MATRIX_INT_H
#define CM_MATRIX_INT_H

#include <stdbool.h>
#include <stddef.h>

// TODO: create_row_from_matrix
// TODO: create_col_from_matrix

typedef enum {

  CM_SUCCESS = 0,
  CM_ERR_NULL_POINTER,
  CM_ERR_SIZE_MISMATCH,
  CM_ERR_NOT_SQUARE,
  CM_ERR_ALLOC_FAILED,
  CM_ERR_INVALID_ARGUMENT,

} CmErrorCode;

typedef struct CmMatrixInt {
  size_t rows;
  size_t columns;
  int *data;
} CmMatrixInt;

/* Allocation */

CmMatrixInt *cm_matrix_int_alloc(size_t rows, size_t cols);
CmMatrixInt *cm_matrix_int_calloc(size_t rows, size_t cols);

CmMatrixInt *cm_matrix_int_create_from_matrix(const CmMatrixInt *orig_matrix);

void cm_matrix_int_free(CmMatrixInt *matrix);

/* Operations */

int cm_matrix_int_set_identity(CmMatrixInt *matrix);
int cm_matrix_int_set_zero(CmMatrixInt *matrix);
int cm_matrix_int_set_all(CmMatrixInt *matrix, int x);
int cm_matrix_int_swap(CmMatrixInt **matrix_a, CmMatrixInt **matrix_b);
int cm_matrix_int_transpose(CmMatrixInt *matrix);

int cm_matrix_int_max(const CmMatrixInt *matrix, int *max_out);
int cm_matrix_int_min(const CmMatrixInt *matrix, int *min_out);
int cm_matrix_int_trace(const CmMatrixInt *matrix, int *trace_out);
int cm_matrix_int_det(const CmMatrixInt *matrix, int *det_out);

int cm_matrix_int_is_null(const CmMatrixInt *matrix, bool *out_result);
int cm_matrix_int_is_identity(const CmMatrixInt *matrix, bool *out_result);
int cm_matrix_int_is_equal(const CmMatrixInt *matrix_a,
                            const CmMatrixInt *matrix_b, bool *out_result);


int cm_matrix_int_add(CmMatrixInt *matrix_a, const CmMatrixInt *matrix_b);
int cm_matrix_int_sub(CmMatrixInt *matrix_a, const CmMatrixInt *matrix_b);
int cm_matrix_int_scale(CmMatrixInt *matrix_a, int scale);
int cm_matrix_int_mul(CmMatrixInt *matrix_a, const CmMatrixInt *matrix_b);

/* Getter/Setter */

int cm_matrix_int_get(const CmMatrixInt *matrix, size_t row, size_t col);
int cm_matrix_int_set(CmMatrixInt *matrix, size_t row, size_t col, int x);

/* Debug */
void _cm_matrix_int_printf(const CmMatrixInt *matrix);

#endif
