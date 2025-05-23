#ifndef MC_ALGEBRA_H
#define MC_ALGEBRA_H

/**
 * @brief Return absolute value of integer number
 * @param num Integer value
 * @return Absolute integer value
 */
static inline int mc_abs_i(int num) { return num > 0 ? num : -num; }

/**
 * @brief Return absolute value of integer number
 * @param num Integer value
 * @return Absolute integer value
 */
static inline long long mc_abs_ll(long long num) {
  return num > 0ll ? num : -num;
}

/**
 * @brief Return absolute value of decimal number
 * @param num Decimal value
 * @return Absolute decimal value
 */
static inline float mc_abs_f(float num) { return num > 0.f ? num : -num; }

/**
 * @brief Return absolute value of decimal number
 * @param num Decimal value
 * @return Absolute decimal value
 */
static inline double mc_abs_d(double num) { return num > 0. ? num : -num; }

/**
 * @brief Calculate value of base in integer exponent
 * @param base Integer value
 * @param exp Integer value
 * @return Base to an integer power
 */
double mc_ipow_i(int base, int exp);

/**
 * @brief Calculate value of base in integer exponent
 * @param base Integer value
 * @param exp Integer value
 * @return Base to an integer power
 */
double mc_ipow_ll(long long base, int exp);

/**
 * @brief Calculate value of base in integer exponent
 * @param base Integer value
 * @param exp Decimal value
 * @return Base to an integer power
 */
double mc_ipow_f(float base, int exp);

/**
 * @brief Calculate value of base in integer exponent
 * @param base Integer value
 * @param exp Decimal value
 * @return Base to an integer power
 */
double mc_ipow_d(double base, int exp);

/**
 * @brief Compute least common multiple of two natural numbers
 * @param n1 Integer value
 * @param n2 Integer value
 * @return Return least common multiple of two integers
 * @retval 0 If n1 or n2 is zero
 * @retval Least common multiple of |n1| and |n2|
 */
int mc_lcm_i(int n1, int n2);

/**
 * @brief Compute least common multiple of two natural numbers
 * @param n1 Integer value
 * @param n2 Integer value
 * @return Return least common multiple of two integers
 * @retval 0 If n1 or n2 is zero
 * @retval Least common multiple of |n1| and |n2|
 */
long long mc_lcm_ll(long long n1, long long n2);

/**
 * @brief Compute greatest common divisor of two natural numbers
 * @param n1 Integer value
 * @param n2 Integer value
 * @return Return greatest common divisor of two integers
 * @retval 0 If n1 and n2 is zero
 * @retval Greatest common devisor of |n1| and |n2|
 */
int mc_gcd_i(int n1, int n2);

/**
 * @brief Compute greatest common divisor of two natural numbers
 * @param n1 Integer value
 * @param n2 Integer value
 * @return Return greatest common divisor of two integers
 * @retval 0 If n1 and n2 is zero
 * @retval Greatest common divisor of |n1| and |n2|
 */
long long mc_gcd_ll(long long n1, long long n2);

/**
 * @brief Compute percent of number n
 * @param n Decimal value
 * @param percent Decimal value
 * @return Return percent of two number n
 */
static inline float mc_percent_f(float n, float percent) {
  return (n * (percent / 100.f));
}

/**
 * @brief Compute percent of number n
 * @param n Decimal value
 * @param percent Decimal value
 * @return Return percent of two number n
 */
static inline double mc_percent_d(double n, double percent) {
  return (n * (percent / 100.));
}

/**
 * @brief Compute sum from start index to end index
 * of arithmetic progression
 * @param start Natural value of start position
 * @param end Natural value of end position
 * @return Sum of arithmetic progression from start to end
 */
float mc_fsum_ap(unsigned int start, unsigned int end, float n_start, float n_end);

/**
 * @brief Compute sum from start index to end index
 * of arithmetic progression
 * @param start Natural value of start position
 * @param end Natural value of end position
 * @return Sum of arithmetic progression from start to end
 */
double mc_dsum_ap(unsigned int start, unsigned int end, double n_start, double n_end);

#endif // MC_ALGEBRA_H
