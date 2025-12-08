#ifndef CM_MATRIX_DOUBLE_INTERNAL_H
#define CM_MATRIX_DOUBLE_INTERNAL_H

#include <stdbool.h>
#include <stddef.h>

// TODO: cm_matrix_double_set_submatrix(dest, src, row_offset, col_offset)
// TODO: resize
// TODO: LU, QR, Cholesky
// TODO: random_matrix(rows, cols, min, max)
// TODO: fixed_matrix(3x3, 2x2, 4x4)
// TODO: cm_matrix_double_from_txt
// TODO: linear transfonmations(rotation, mirror, projection, shear, scale
// compration, expantion)

/* Matrix double type */
typedef struct CmMatrixDouble {
  size_t rows;
  size_t columns;
  double *data;
} CmMatrixDouble;

typedef double (*CmMatrixMapFunc)(double x);

#ifdef CM_DEBUG
void _cm_matrix_double_printf(const CmMatrixDouble *matrix);
#endif

#endif
