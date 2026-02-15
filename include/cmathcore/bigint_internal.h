#ifndef CM_BIG_INT_INTERNAL_H
#define CM_BIG_INT_INTERNAL_H

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

typedef struct cm_bigint_t {

  char sign;
  char *data;
  size_t size;
  size_t capacity;

} cm_bigint_t;

#endif
