#ifndef CM_MATRIX_INT_H
#define CM_MATRIX_INT_H

#include <stddef.h>
#include <stdbool.h>

typedef struct CmMatrixInt{
  size_t rows;
  size_t columns;
  int *data;
} CmMatrixInt;

/* Allocation */

CmMatrixInt* cm_matrix_int_alloc(size_t rows, size_t cols);
CmMatrixInt* cm_matrix_int_calloc(size_t rows, size_t cols);

CmMatrixInt* cm_matrix_int_create_from_matrix(const CmMatrixInt *orig_matrix);

// TODO: create_row_from_matrix
// TODO: create_col_from_matrix

void cm_matrix_int_free(CmMatrixInt *matrix);

/* Operations */

CmMatrixInt* cm_matrix_int_set_zero(CmMatrixInt *matrix);
CmMatrixInt* cm_matrix_int_set_all(CmMatrixInt *matrix);
CmMatrixInt* cm_matrix_int_set_identity(CmMatrixInt *matrix);

int cm_matrix_int_swap(CmMatrixInt* matrix_a, CmMatrixInt* matrix_b);

int cm_matrix_int_max(const CmMatrixInt* matrix);
int cm_matrix_int_min(const CmMatrixInt* matrix);

int cm_matrix_int_transpose(CmMatrixInt* matrix);

int cm_matrix_int_trace(const CmMatrixInt* matrix);

bool cm_matrix_int_is_null(const CmMatrixInt* matrix);
bool cm_matrix_int_is_identity(const CmMatrixInt* matrix);
bool cm_matrix_int_is_equal(const CmMatrixInt* matrix_a, const CmMatrixInt* matrix_b);

int cm_matrix_int_add(CmMatrixInt *matrix_a, const CmMatrixInt* matrix_b);
int cm_matrix_int_sub(CmMatrixInt *matrix_a, const CmMatrixInt* matrix_b);
int cm_matrix_int_scale(CmMatrixInt *matrix_a, int scale);
int cm_matrix_int_mul(CmMatrixInt *matrix_a, const CmMatrixInt* matrix_b);


#endif
