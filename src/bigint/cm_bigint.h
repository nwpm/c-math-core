#ifndef CM_BIG_INT_H
#define CM_BIG_INT_H

#include "../utils/cm_err_codes.h"
#include <stdbool.h>
#include <stddef.h>

#define CM_BIGINT_START_CAPACITY 4

// TODO: change char* buffer to binary buffer(uint32_t)
// TODO: cm_bigint_extended_gcd(const CmBigInt *a, const CmBigInt *b,
//                            	CmBigInt *x, CmBigInt *y, CmBigInt *gcd)
// TODO: cm_bigint_from_hex_string
// TODO:
// CmStatusCode cm_bigint_mod_multiply(CmBigInt *num, const CmBigInt
// *multiplier,
//                                    const CmBigInt *modulus);
// CmStatusCode cm_bigint_mod_pow(CmBigInt *num, const CmBigInt *exponent,
//                               const CmBigInt *modulus);

typedef struct CmBigInt {

  char sign;
  char *data;
  size_t size;
  size_t capacity;

} CmBigInt;

/* Allocate row bigint num */
CmBigInt *cm_bigint_alloc();

/* Create bigint num from X */
CmBigInt *cm_bigint_create_from_num(long long src_num);

/* Create bigint num from c-string */
CmBigInt *cm_bigint_create_from_cstr(const char *src_cstr);

/* Create copy of bigint num */
CmBigInt *cm_bigint_create_copy(const CmBigInt *src_num);

/* Reserve N bytes for bigint data */
CmStatusCode cm_bigint_reserve(CmBigInt *bigint_num, size_t size);

/* Free bigint object */
void cm_bigint_free(CmBigInt *bigint_num);

/* lhs < rhs bigint compare result */
bool cm_bigint_less(const CmBigInt *lhs, const CmBigInt *rhs);

/* lhs <= rhs bigint compare result */
bool cm_bigint_less_or_equal(const CmBigInt *lhs, const CmBigInt *rhs);

/* lhs > rhs bigint compare result */
bool cm_bigint_greater(const CmBigInt *lhs, const CmBigInt *rhs);

/* lhs >= rhs bigint compare result */
bool cm_bigint_greater_or_equal(const CmBigInt *lhs, const CmBigInt *rhs);

/* lhs = rhs bigint compare result */
bool cm_bigint_is_equal(const CmBigInt *lhs, const CmBigInt *rhs);

/* lhs < rhs bigint and long long compare result */
bool cm_bigint_less_ll(const CmBigInt *lhs, long long rhs);

/* lhs <= rhs bigint and long long compare result */
bool cm_bigint_less_or_equal_ll(const CmBigInt *lhs, long long rhs);

/* lhs > rhs bigint and long long compare result */
bool cm_bigint_greater_ll(const CmBigInt *lhs, long long rhs);

/* lhs >= rhs bigint and long long compare result */
bool cm_bigint_greater_or_equal_ll(const CmBigInt *lhs, long long rhs);

/* lhs = rhs bigint and long long compare result */
bool cm_bigint_is_equal_ll(const CmBigInt *lhs, long long rhs);

/* Adds addend to bigint_num and stores the result in bigint_num. */
CmStatusCode cm_bigint_add(CmBigInt *bigint_num, const CmBigInt *addend);

/* Subtract value from bigint_num and stores the result in bigint_num */
CmStatusCode cm_bigint_subtract(CmBigInt *bigint_num, const CmBigInt *subtrc);
CmStatusCode cm_bigint_multiply(CmBigInt *bigint_num,
                                const CmBigInt *multiplier);
CmStatusCode cm_bigint_div(CmBigInt *bigint_num, const CmBigInt *divider);

CmStatusCode cm_bigint_inc(CmBigInt *bigint_num);
CmStatusCode cm_bigint_dec(CmBigInt *bigint_num);

CmStatusCode cm_bigint_add_ll(CmBigInt *bigint_num, long long addend);
CmStatusCode cm_bigint_sub_ll(CmBigInt *bigint_num, long long subtrc);

CmStatusCode cm_bigint_mod(CmBigInt *bigint_num, const CmBigInt *divider);
CmStatusCode cm_bigint_div_mod(CmBigInt *quotient, CmBigInt *remainder,
                               const CmBigInt *dividend,
                               const CmBigInt *divider);

CmStatusCode cm_bigint_gcd(const CmBigInt *bigint_a, const CmBigInt *bigint_b,
                           CmBigInt *res);

/* Calculate num^(exp) */
CmStatusCode cm_bigint_pow(CmBigInt *bigint_num, unsigned long long exp);

/* Check */
bool cm_bigint_is_positive(const CmBigInt *bigint_num);
bool cm_bigint_is_zero(const CmBigInt *bigint_num);

/* Check is bigint num odd */
bool cm_bigint_is_even(const CmBigInt *bigint_num);

/* Check is bigint num even */
bool cm_bigint_is_odd(const CmBigInt *bigint_num);

/* Shifts */
CmStatusCode cm_bigint_shift_left(CmBigInt *bigint_num, size_t k);
void cm_bigint_shift_right(CmBigInt *bigint_num, size_t k);

/* Convert */
char *cm_bigint_to_string(const CmBigInt *bigint_num);

/* Setters */
CmStatusCode cm_bigint_set(CmBigInt *bigint_num, const CmBigInt *setter);
CmStatusCode cm_bigint_set_long(CmBigInt *bigint_num, long long setter);

/* Other */
void cm_bigint_negate(CmBigInt *bigint_num);
void cm_bigint_abs(CmBigInt *bigint_num);

CmStatusCode cm_bigint_shrink_to_fit(CmBigInt *bigint_num);
size_t cm_bigint_num_digits(const CmBigInt *bigint_num);

/* Alloc hex c-string from bigint num */
char *cm_bigint_to_hex_string(const CmBigInt *bigint_num);

/* Alloc bin c-string from bigint num */
char *cm_bigint_to_bin_string(const CmBigInt *bigint_num);

/* Create bigint num from c-string */
CmBigInt *cm_bigint_from_bin_string(const char *str);

#endif
