#ifndef ARITH_H
#define ARITH_H

/**
 * @brief Calculate the greatest common divisor of 2 numbers.
 * 
 * @param a First number
 * @param b Second number
 * @return int 
 */
u_int64_t gcd(u_int64_t a, u_int64_t b);

/**
 * @brief Calculate the greatest common divisor of an array of numbers.
 * 
 * @param nums Array of numbers
 * @param nums_size Length of array
 * @return int 
 */
u_int64_t gcd_arr(u_int64_t nums[], unsigned int nums_size);

/**
 * @brief Calculate the greatest common divisor of n numbers.
 * 
 * @param n Number of arguments, must be >= 2
 * @param a First number
 * @param b Second number
 * @return int 
 */
u_int64_t gcd_varg(unsigned int n, u_int64_t a, u_int64_t b, ...);

/**
 * @brief Calculate the least common multiple of 2 numbers.
 * 
 * @param a First number
 * @param b Second number
 * @return u_int64_t 
 */
u_int64_t lcm(u_int64_t a, u_int64_t b);

/**
 * @brief Calculate the least common multiple of n numbers.
 * 
 * @param nums Array of numbers
 * @param b Length of array
 * @return u_int64_t 
 */
u_int64_t lcm_arr(int nums[], unsigned int nums_size);

#endif
