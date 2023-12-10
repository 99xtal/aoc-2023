#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

u_int64_t gcd(u_int64_t a, u_int64_t b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

u_int64_t gcd_arr(u_int64_t nums[], unsigned int nums_size) {
    int result = nums[0];
    for (unsigned int i = 0; i < nums_size; i++) {
        result = gcd(nums[i], result);
    }
    return result;
}

u_int64_t gcd_varg(unsigned int n, u_int64_t a, u_int64_t b, ...) {
    assert(n >= 2);

    va_list arg_ptr;
    va_start(arg_ptr, b);
    int result = gcd(a, b);
    for (unsigned int i = 2; i < n; i++) {
        result = gcd(va_arg(arg_ptr, u_int64_t), result);
    }
    va_end(arg_ptr);
    return result;
}

uint64_t lcm(uint64_t a, uint64_t b) {
  return a * b / gcd(a,b);
}

uint64_t lcm_arr(int a[], unsigned int size) {
  uint64_t result = a[0];
  for (int i = 1; i < size; i++) {
    result = lcm(a[i], result);
  }
  return result;
}
