#ifndef CM_BIG_INT_H
#define CM_BIG_INT_H

#include <stddef.h>

#define CM_BIGINT_START_CAPACITY 4

typedef struct CmBigInt {

  char sign;
  char *buffer;
  size_t size;
  size_t capacity;

} CmBigInt;

CmBigInt *cm_bigint_create();
CmBigInt *cm_bigint_create_from_num(long long src_num);
CmBigInt *cm_bigint_create_from_cstr(const char *src_cstr);
CmBigInt *cm_bigint_create_copy(const CmBigInt *src_num);

int cm_bigint_less(const CmBigInt *lhs, const CmBigInt *rhs);
int cm_bigint_less_or_equal(const CmBigInt *lhs, const CmBigInt *rhs);
int cm_bigint_greater(const CmBigInt *lhs, const CmBigInt *rhs);
int cm_bigint_greater_or_equal(const CmBigInt *lhs, const CmBigInt *rhs);
int cm_bigint_is_equal(const CmBigInt *lhs, const CmBigInt *rhs);

CmBigInt *cm_bigint_add(CmBigInt *bigint_num, const CmBigInt *addend);
CmBigInt *cm_bigint_subtract(CmBigInt *bigint_num, const CmBigInt *substr);
CmBigInt *cm_bigint_multiply(CmBigInt *bigint_num, const CmBigInt* multiplier);

CmBigInt *cm_bigint_negate(CmBigInt *bigint_num);
CmBigInt *cm_bigint_abs(CmBigInt *bigint_num);

void cm_bigint_free(CmBigInt *bigint_num);

#endif // BIG_INT_H
