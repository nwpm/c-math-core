#include "../../src/matrix/cm_matrix_int.h"

int main(){

  CmMatrixInt* matrix = cm_matrix_int_alloc(4, 5);

  cm_matrix_int_set_identity(matrix);

  _cm_matrix_int_printf(matrix);

  cm_matrix_int_free(matrix);

  return 0;
}
