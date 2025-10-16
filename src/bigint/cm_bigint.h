#ifndef CM_BIG_INT_H
#define CM_BIG_INT_H

#include "../utils/cm_err_codes.h"
#include <stdbool.h>
#include <stddef.h>

#define CM_BIGINT_START_CAPACITY 4

typedef struct CmBigInt {

  char sign;
  char *buffer;
  size_t size;
  size_t capacity;

} CmBigInt;

/* Allocation */
CmBigInt *cm_bigint_alloc();
CmBigInt *cm_bigint_create_from_num(long long src_num);
CmBigInt *cm_bigint_create_from_cstr(const char *src_cstr);
CmBigInt *cm_bigint_create_copy(const CmBigInt *src_num);
void cm_bigint_free(CmBigInt *bigint_num);

/* Compare */
bool cm_bigint_less(const CmBigInt *lhs, const CmBigInt *rhs);
bool cm_bigint_less_or_equal(const CmBigInt *lhs, const CmBigInt *rhs);
bool cm_bigint_greater(const CmBigInt *lhs, const CmBigInt *rhs);
bool cm_bigint_greater_or_equal(const CmBigInt *lhs, const CmBigInt *rhs);
bool cm_bigint_is_equal(const CmBigInt *lhs, const CmBigInt *rhs);

bool cm_bigint_less_ll(const CmBigInt *lhs, long long rhs);
bool cm_bigint_less_or_equal_ll(const CmBigInt *lhs, long long rhs);
bool cm_bigint_greater_ll(const CmBigInt *lhs, long long rhs);
bool cm_bigint_greater_or_equal_ll(const CmBigInt *lhs, long long rhs);
bool cm_bigint_is_equal_ll(const CmBigInt *lhs, long long rhs);

/* Operations */
CmStatusCode cm_bigint_add(CmBigInt *bigint_num, const CmBigInt *addend);
CmStatusCode cm_bigint_subtract(CmBigInt *bigint_num, const CmBigInt *subtrc);
CmStatusCode cm_bigint_multiply(CmBigInt *bigint_num,
                                const CmBigInt *multiplier);
CmStatusCode cm_bigint_divide(CmBigInt *bigint_num, const CmBigInt *divider);

CmStatusCode cm_bigint_inc(CmBigInt *bigint_num);
CmStatusCode cm_bigint_dec(CmBigInt *bigint_num);

CmStatusCode cm_bigint_add_ll(CmBigInt *bigint_num, long long addend);
CmStatusCode cm_bigint_sub_ll(CmBigInt *bigint_num, long long subtrc);

CmStatusCode cm_bigint_mod(CmBigInt *bigint_num, const CmBigInt *divider);
CmStatusCode cm_bigint_div_mod(CmBigInt *quotient, CmBigInt *remainder,
                               const CmBigInt *dividend,
                               const CmBigInt *divider);

/* Check */
bool cm_bigint_is_positive(const CmBigInt *bigint_num);
bool cm_bigint_is_zero(const CmBigInt *bigint_num);

/* Shifts */
CmStatusCode cm_bigint_shift_left(CmBigInt *bigint_num, size_t k);
CmStatusCode cm_bigint_shift_right(CmBigInt *bigint_num, size_t k);

/* Convert */
char *cm_bigint_to_string(const CmBigInt *bigint_num);

/* Setters */
CmStatusCode cm_bigint_set(CmBigInt *bigint_num, const CmBigInt *setter);
CmStatusCode cm_bigint_set_long(CmBigInt *bigint_num, long long setter);

/* Other */
CmBigInt *cm_bigint_negate(CmBigInt *bigint_num);
CmBigInt *cm_bigint_abs(CmBigInt *bigint_num);

CmStatusCode cm_bigint_shrink_to_fit(CmBigInt *bigint_num);

// TODO:

CmStatusCode cm_bigint_pow(CmBigInt *num, unsigned long long exponent);
CmStatusCode cm_bigint_mod_multiply(CmBigInt *num, const CmBigInt *multiplier,
                                    const CmBigInt *modulus);
CmStatusCode cm_bigint_mod_pow(CmBigInt *num, const CmBigInt *exponent,
                               const CmBigInt *modulus);

#endif // BIG_INT_H
