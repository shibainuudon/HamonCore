// Copyright 2018 Ulf Adams
//
// The contents of this file may be used under the terms of the Apache License,
// Version 2.0.
//
//    (See accompanying file LICENSE-Apache or copy at
//     http://www.apache.org/licenses/LICENSE-2.0)
//
// Alternatively, the contents of this file may be used under the terms of
// the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE-Boost or copy at
//     https://www.boost.org/LICENSE_1_0.txt)
//
// Unless required by applicable law or agreed to in writing, this software
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.

// Runtime compiler options:
// -DRYU_DEBUG Generate verbose debugging output to stdout.
//
// -DRYU_ONLY_64_BIT_OPS Avoid using uint128_t or 64-bit intrinsics. Slower,
//     depending on your compiler.
//
// -DRYU_AVOID_UINT128 Avoid using uint128_t. Slower, depending on your compiler.
#ifndef RYU_D2FIXED_HPP
#define RYU_D2FIXED_HPP

#include "hamon/charconv/detail/ryu/ryu.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef RYU_DEBUG
#include <inttypes.h>
#include <stdio.h>
#endif

#include "hamon/charconv/detail/ryu/common.h"
#include "hamon/charconv/detail/ryu/digit_table.h"
#include "hamon/charconv/detail/ryu/d2fixed_full_table.h"
#include "hamon/charconv/detail/ryu/d2s_intrinsics.h"

#include "hamon/cstring/memcpy.hpp"
#include "hamon/cstring/memset.hpp"

#define DOUBLE_MANTISSA_BITS 52
#define DOUBLE_EXPONENT_BITS 11
#define DOUBLE_BIAS 1023

#define POW10_ADDITIONAL_BITS 120

namespace hamon {
namespace detail {
namespace ryu {

#if defined(HAS_UINT128)
static inline HAMON_CXX20_CONSTEXPR uint128_t umul256(const uint128_t a, const uint64_t bHi, const uint64_t bLo, uint128_t* const productHi) {
  const uint64_t aLo = (uint64_t)a;
  const uint64_t aHi = (uint64_t)(a >> 64);

  const uint128_t b00 = (uint128_t)aLo * bLo;
  const uint128_t b01 = (uint128_t)aLo * bHi;
  const uint128_t b10 = (uint128_t)aHi * bLo;
  const uint128_t b11 = (uint128_t)aHi * bHi;

  const uint64_t b00Lo = (uint64_t)b00;
  const uint64_t b00Hi = (uint64_t)(b00 >> 64);

  const uint128_t mid1 = b10 + b00Hi;
  const uint64_t mid1Lo = (uint64_t)(mid1);
  const uint64_t mid1Hi = (uint64_t)(mid1 >> 64);

  const uint128_t mid2 = b01 + mid1Lo;
  const uint64_t mid2Lo = (uint64_t)(mid2);
  const uint64_t mid2Hi = (uint64_t)(mid2 >> 64);

  const uint128_t pHi = b11 + mid1Hi + mid2Hi;
  const uint128_t pLo = ((uint128_t)mid2Lo << 64) | b00Lo;

  *productHi = pHi;
  return pLo;
}

// Returns the high 128 bits of the 256-bit product of a and b.
static inline HAMON_CXX20_CONSTEXPR uint128_t umul256_hi(const uint128_t a, const uint64_t bHi, const uint64_t bLo) {
  // Reuse the umul256 implementation.
  // Optimizers will likely eliminate the instructions used to compute the
  // low part of the product.
  uint128_t hi;
  umul256(a, bHi, bLo, &hi);
  return hi;
}

// Unfortunately, gcc/clang do not automatically turn a 128-bit integer division
// into a multiplication, so we have to do it manually.
static inline HAMON_CXX20_CONSTEXPR uint32_t uint128_mod1e9(const uint128_t v) {
  // After multiplying, we're going to shift right by 29, then truncate to uint32_t.
  // This means that we need only 29 + 32 = 61 bits, so we can truncate to uint64_t before shifting.
  const uint64_t multiplied = (uint64_t) umul256_hi(v, 0x89705F4136B4A597u, 0x31680A88F8953031u);

  // For uint32_t truncation, see the mod1e9() comment in d2s_intrinsics.h.
  const uint32_t shifted = (uint32_t) (multiplied >> 29);

  return ((uint32_t) v) - 1000000000 * shifted;
}

// Best case: use 128-bit type.
static inline HAMON_CXX20_CONSTEXPR uint32_t mulShift_mod1e9(const uint64_t m, const uint64_t* const mul, const int32_t j) {
  const uint128_t b0 = ((uint128_t) m) * mul[0]; // 0
  const uint128_t b1 = ((uint128_t) m) * mul[1]; // 64
  const uint128_t b2 = ((uint128_t) m) * mul[2]; // 128
#ifdef RYU_DEBUG
  if (j < 128 || j > 180) {
    printf("%d\n", j);
  }
#endif
  assert(j >= 128);
  assert(j <= 180);
  // j: [128, 256)
  const uint128_t mid = b1 + (uint64_t) (b0 >> 64); // 64
  const uint128_t s1 = b2 + (uint64_t) (mid >> 64); // 128
  return uint128_mod1e9(s1 >> (j - 128));
}

#else // HAS_UINT128

#if defined(HAS_64_BIT_INTRINSICS)
// Returns the low 64 bits of the high 128 bits of the 256-bit product of a and b.
static inline HAMON_CXX20_CONSTEXPR uint64_t umul256_hi128_lo64(
  const uint64_t aHi, const uint64_t aLo, const uint64_t bHi, const uint64_t bLo) {
  uint64_t b00Hi;
  const uint64_t b00Lo = umul128(aLo, bLo, &b00Hi);
  uint64_t b01Hi;
  const uint64_t b01Lo = umul128(aLo, bHi, &b01Hi);
  uint64_t b10Hi;
  const uint64_t b10Lo = umul128(aHi, bLo, &b10Hi);
  uint64_t b11Hi;
  const uint64_t b11Lo = umul128(aHi, bHi, &b11Hi);
  (void) b00Lo; // unused
  (void) b11Hi; // unused
  const uint64_t temp1Lo = b10Lo + b00Hi;
  const uint64_t temp1Hi = b10Hi + (temp1Lo < b10Lo);
  const uint64_t temp2Lo = b01Lo + temp1Lo;
  const uint64_t temp2Hi = b01Hi + (temp2Lo < b01Lo);
  return b11Lo + temp1Hi + temp2Hi;
}

static inline HAMON_CXX20_CONSTEXPR uint32_t uint128_mod1e9(const uint64_t vHi, const uint64_t vLo) {
  // After multiplying, we're going to shift right by 29, then truncate to uint32_t.
  // This means that we need only 29 + 32 = 61 bits, so we can truncate to uint64_t before shifting.
  const uint64_t multiplied = umul256_hi128_lo64(vHi, vLo, 0x89705F4136B4A597u, 0x31680A88F8953031u);

  // For uint32_t truncation, see the mod1e9() comment in d2s_intrinsics.h.
  const uint32_t shifted = (uint32_t) (multiplied >> 29);

  return ((uint32_t) vLo) - 1000000000 * shifted;
}
#endif // HAS_64_BIT_INTRINSICS

static inline HAMON_CXX20_CONSTEXPR uint32_t mulShift_mod1e9(const uint64_t m, const uint64_t* const mul, const int32_t j) {
  uint64_t high0;                                   // 64
  const uint64_t low0 = umul128(m, mul[0], &high0); // 0
  uint64_t high1;                                   // 128
  const uint64_t low1 = umul128(m, mul[1], &high1); // 64
  uint64_t high2;                                   // 192
  const uint64_t low2 = umul128(m, mul[2], &high2); // 128
  const uint64_t s0low = low0;              // 0
  (void) s0low; // unused
  const uint64_t s0high = low1 + high0;     // 64
  const uint32_t c1 = s0high < low1;
  const uint64_t s1low = low2 + high1 + c1; // 128
  const uint32_t c2 = s1low < low2; // high1 + c1 can't overflow, so compare against low2
  const uint64_t s1high = high2 + c2;       // 192
#ifdef RYU_DEBUG
  if (j < 128 || j > 180) {
    printf("%d\n", j);
  }
#endif
  assert(j >= 128);
  assert(j <= 180);
#if defined(HAS_64_BIT_INTRINSICS)
  const uint32_t dist = (uint32_t) (j - 128); // dist: [0, 52]
  const uint64_t shiftedhigh = s1high >> dist;
  const uint64_t shiftedlow = shiftright128(s1low, s1high, dist);
  return uint128_mod1e9(shiftedhigh, shiftedlow);
#else // HAS_64_BIT_INTRINSICS
  if (j < 160) { // j: [128, 160)
    const uint64_t r0 = mod1e9(s1high);
    const uint64_t r1 = mod1e9((r0 << 32) | (s1low >> 32));
    const uint64_t r2 = ((r1 << 32) | (s1low & 0xffffffff));
    return mod1e9(r2 >> (j - 128));
  } else { // j: [160, 192)
    const uint64_t r0 = mod1e9(s1high);
    const uint64_t r1 = ((r0 << 32) | (s1low >> 32));
    return mod1e9(r1 >> (j - 160));
  }
#endif // HAS_64_BIT_INTRINSICS
}
#endif // HAS_UINT128

// Convert `digits` to a sequence of decimal digits. Append the digits to the result.
// The caller has to guarantee that:
//   10^(olength-1) <= digits < 10^olength
// e.g., by passing `olength` as `decimalLength9(digits)`.
static inline HAMON_CXX20_CONSTEXPR void append_n_digits(const uint32_t olength, uint32_t digits, char* const result) {
#ifdef RYU_DEBUG
  printf("DIGITS=%u\n", digits);
#endif

  uint32_t i = 0;
  while (digits >= 10000) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=38217
    const uint32_t c = digits - 10000 * (digits / 10000);
#else
    const uint32_t c = digits % 10000;
#endif
    digits /= 10000;
    const uint32_t c0 = (c % 100) << 1;
    const uint32_t c1 = (c / 100) << 1;
    hamon::ct::memcpy(result + olength - i - 2, DIGIT_TABLE + c0, 2);
    hamon::ct::memcpy(result + olength - i - 4, DIGIT_TABLE + c1, 2);
    i += 4;
  }
  if (digits >= 100) {
    const uint32_t c = (digits % 100) << 1;
    digits /= 100;
    hamon::ct::memcpy(result + olength - i - 2, DIGIT_TABLE + c, 2);
    i += 2;
  }
  if (digits >= 10) {
    const uint32_t c = digits << 1;
    hamon::ct::memcpy(result + olength - i - 2, DIGIT_TABLE + c, 2);
  } else {
    result[0] = (char) ('0' + digits);
  }
}

// Convert `digits` to a sequence of decimal digits. Print the first digit, followed by a decimal
// dot '.' followed by the remaining digits. The caller has to guarantee that:
//   10^(olength-1) <= digits < 10^olength
// e.g., by passing `olength` as `decimalLength9(digits)`.
static inline HAMON_CXX20_CONSTEXPR void append_d_digits(const uint32_t olength, uint32_t digits, char* const result) {
#ifdef RYU_DEBUG
  printf("DIGITS=%u\n", digits);
#endif

  uint32_t i = 0;
  while (digits >= 10000) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=38217
    const uint32_t c = digits - 10000 * (digits / 10000);
#else
    const uint32_t c = digits % 10000;
#endif
    digits /= 10000;
    const uint32_t c0 = (c % 100) << 1;
    const uint32_t c1 = (c / 100) << 1;
    hamon::ct::memcpy(result + olength + 1 - i - 2, DIGIT_TABLE + c0, 2);
    hamon::ct::memcpy(result + olength + 1 - i - 4, DIGIT_TABLE + c1, 2);
    i += 4;
  }
  if (digits >= 100) {
    const uint32_t c = (digits % 100) << 1;
    digits /= 100;
    hamon::ct::memcpy(result + olength + 1 - i - 2, DIGIT_TABLE + c, 2);
    i += 2;
  }
  if (digits >= 10) {
    const uint32_t c = digits << 1;
    result[2] = DIGIT_TABLE[c + 1];
    result[1] = '.';
    result[0] = DIGIT_TABLE[c];
  } else {
    result[1] = '.';
    result[0] = (char) ('0' + digits);
  }
}

// Convert `digits` to decimal and write the last `count` decimal digits to result.
// If `digits` contains additional digits, then those are silently ignored.
static inline HAMON_CXX20_CONSTEXPR void append_c_digits(const uint32_t count, uint32_t digits, char* const result) {
#ifdef RYU_DEBUG
  printf("DIGITS=%u\n", digits);
#endif
  // Copy pairs of digits from DIGIT_TABLE.
  uint32_t i = 0;
  for (; i < count - 1; i += 2) {
    const uint32_t c = (digits % 100) << 1;
    digits /= 100;
    hamon::ct::memcpy(result + count - i - 2, DIGIT_TABLE + c, 2);
  }
  // Generate the last digit if count is odd.
  if (i < count) {
    const char c = (char) ('0' + (digits % 10));
    result[count - i - 1] = c;
  }
}

// Convert `digits` to decimal and write the last 9 decimal digits to result.
// If `digits` contains additional digits, then those are silently ignored.
static inline HAMON_CXX20_CONSTEXPR void append_nine_digits(uint32_t digits, char* const result) {
#ifdef RYU_DEBUG
  printf("DIGITS=%u\n", digits);
#endif
  if (digits == 0) {
    hamon::ct::memset(result, '0', 9);
    return;
  }

  for (uint32_t i = 0; i < 5; i += 4) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=38217
    const uint32_t c = digits - 10000 * (digits / 10000);
#else
    const uint32_t c = digits % 10000;
#endif
    digits /= 10000;
    const uint32_t c0 = (c % 100) << 1;
    const uint32_t c1 = (c / 100) << 1;
    hamon::ct::memcpy(result + 7 - i, DIGIT_TABLE + c0, 2);
    hamon::ct::memcpy(result + 5 - i, DIGIT_TABLE + c1, 2);
  }
  result[0] = (char) ('0' + digits);
}

static inline HAMON_CXX20_CONSTEXPR uint32_t indexForExponent(const uint32_t e) {
  return (e + 15) / 16;
}

static inline HAMON_CXX20_CONSTEXPR uint32_t pow10BitsForIndex(const uint32_t idx) {
  return 16 * idx + POW10_ADDITIONAL_BITS;
}

static inline HAMON_CXX20_CONSTEXPR uint32_t lengthForIndex(const uint32_t idx) {
  // +1 for ceil, +16 for mantissa, +8 to round up when dividing by 9
  return (log10Pow2(16 * (int32_t) idx) + 1 + 16 + 8) / 9;
}

static inline int copy_special_str_printf(char* const result, const bool sign, const uint64_t mantissa) {
#if defined(_MSC_VER)
  // TODO: Check that -nan is expected output on Windows.
  if (sign) {
    result[0] = '-';
  }
  if (mantissa) {
    if (mantissa < (1ull << (DOUBLE_MANTISSA_BITS - 1))) {
      hamon::ct::memcpy(result + sign, "nan(snan)", 9);
      return sign + 9;
    }
    hamon::ct::memcpy(result + sign, "nan", 3);
    return sign + 3;
  }
#else
  if (mantissa) {
    hamon::ct::memcpy(result, "nan", 3);
    return 3;
  }
  if (sign) {
    result[0] = '-';
  }
#endif
  hamon::ct::memcpy(result + sign, "Infinity", 8);
  return sign + 8;
}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wsign-conversion")

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result d2fixed_buffered_n(char* first, char* const last, const double d,
  const uint32_t precision) {
  char* const original_first = first;

  const uint64_t bits = double_to_bits(d);
#ifdef RYU_DEBUG
  printf("IN=");
  for (int32_t bit = 63; bit >= 0; --bit) {
    printf("%d", (int) ((bits >> bit) & 1));
  }
  printf("\n");
#endif

  // Case distinction; exit early for the easy cases.
  if (bits == 0) {
    const int32_t total_zero_length = 1 // leading zero
      + static_cast<int32_t>(precision != 0) // possible decimal point
      + static_cast<int32_t>(precision); // zeroes after decimal point

    if (last - first < total_zero_length) {
      return { last, errc::value_too_large };
    }

    *first++ = '0';
    if (precision > 0) {
      *first++ = '.';
      hamon::ct::memset(first, '0', precision);
      first += precision;
    }
    return { first, errc{} };
  }

  // Decode bits into mantissa and exponent.
  const uint64_t ieeeMantissa = bits & ((1ull << DOUBLE_MANTISSA_BITS) - 1);
  const uint32_t ieeeExponent = static_cast<uint32_t>(bits >> DOUBLE_MANTISSA_BITS);

  int32_t e2;
  uint64_t m2;
  if (ieeeExponent == 0) {
    e2 = 1 - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
    m2 = ieeeMantissa;
  } else {
    e2 = (int32_t) ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
    m2 = (1ull << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
  }

#ifdef RYU_DEBUG
  printf("-> %" PRIu64 " * 2^%d\n", m2, e2);
#endif

  bool nonzero = false;
  if (e2 >= -52) {
    const uint32_t idx = e2 < 0 ? 0 : indexForExponent((uint32_t) e2);
    const uint32_t p10bits = pow10BitsForIndex(idx);
    const int32_t len = (int32_t) lengthForIndex(idx);
#ifdef RYU_DEBUG
    printf("idx=%u\n", idx);
    printf("len=%d\n", len);
#endif
    for (int32_t i = len - 1; i >= 0; --i) {
      const uint32_t j = p10bits - static_cast<uint32_t>(e2);
      // Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
      // a slightly faster code path in mulShift_mod1e9. Instead, we can just increase the multipliers.
      const uint32_t digits = mulShift_mod1e9(m2 << 8, POW10_SPLIT[POW10_OFFSET[idx] + i], (int32_t) (j + 8));
      if (nonzero) {
        if (last - first < 9) {
          return { last, errc::value_too_large };
        }
        append_nine_digits(digits, first);
        first += 9;
      } else if (digits != 0) {
        const uint32_t olength = decimalLength9(digits);
        if (last - first < static_cast<ptrdiff_t>(olength)) {
          return { last, errc::value_too_large };
        }
        append_n_digits(olength, digits, first);
        first += olength;
        nonzero = true;
      }
    }
  }
  if (!nonzero) {
    if (first == last) {
      return { last, errc::value_too_large };
    }
    *first++ = '0';
  }
  if (precision > 0) {
    if (first == last) {
      return { last, errc::value_too_large };
    }
    *first++ = '.';
  }
#ifdef RYU_DEBUG
  printf("e2=%d\n", e2);
#endif
  if (e2 < 0) {
    const int32_t idx = -e2 / 16;
#ifdef RYU_DEBUG
    printf("idx=%d\n", idx);
#endif
    const uint32_t blocks = precision / 9 + 1;
    // 0 = don't round up; 1 = round up unconditionally; 2 = round up if odd.
    int roundUp = 0;
    uint32_t i = 0;
    if (blocks <= MIN_BLOCK_2[idx]) {
      i = blocks;
      if (last - first < static_cast<ptrdiff_t>(precision)) {
        return { last, errc::value_too_large };
      }
      hamon::ct::memset(first, '0', precision);
      first += precision;
    } else if (i < MIN_BLOCK_2[idx]) {
      i = MIN_BLOCK_2[idx];
      if (last - first < static_cast<ptrdiff_t>(9 * i)) {
        return { last, errc::value_too_large };
      }
      hamon::ct::memset(first, '0', 9 * i);
      first += 9 * i;
    }
    for (; i < blocks; ++i) {
      const int32_t j = ADDITIONAL_BITS_2 + (-e2 - 16 * idx);
      const uint32_t p = POW10_OFFSET_2[idx] + i - MIN_BLOCK_2[idx];
      if (p >= POW10_OFFSET_2[idx + 1]) {
        // If the remaining digits are all 0, then we might as well use hamon::ct::memset.
        // No rounding required in this case.
        const uint32_t fill = precision - 9 * i;
        if (last - first < static_cast<ptrdiff_t>(fill)) {
          return { last, errc::value_too_large };
        }
        hamon::ct::memset(first, '0', fill);
        first += fill;
        break;
      }
      // Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
      // a slightly faster code path in mulShift_mod1e9. Instead, we can just increase the multipliers.
      uint32_t digits = mulShift_mod1e9(m2 << 8, POW10_SPLIT_2[p], j + 8);
#ifdef RYU_DEBUG
      printf("digits=%u\n", digits);
#endif
      if (i < blocks - 1) {
        if (last - first < 9) {
          return { last, errc::value_too_large };
        }
        append_nine_digits(digits, first);
        first += 9;
      } else {
        const uint32_t maximum = precision - 9 * i;
        uint32_t lastDigit = 0;
        for (uint32_t k = 0; k < 9 - maximum; ++k) {
          lastDigit = digits % 10;
          digits /= 10;
        }
#ifdef RYU_DEBUG
        printf("lastDigit=%u\n", lastDigit);
#endif
        if (lastDigit != 5) {
          roundUp = lastDigit > 5;
        } else {
          // Is m * 10^(additionalDigits + 1) / 2^(-e2) integer?
          const int32_t requiredTwos = -e2 - (int32_t) precision - 1;
          const bool trailingZeros = requiredTwos <= 0
            || (requiredTwos < 60 && multipleOfPowerOf2(m2, (uint32_t) requiredTwos));
          roundUp = trailingZeros ? 2 : 1;
#ifdef RYU_DEBUG
          printf("requiredTwos=%d\n", requiredTwos);
          printf("trailingZeros=%s\n", trailingZeros ? "true" : "false");
#endif
        }
        if (maximum > 0) {
          if (last - first < static_cast<ptrdiff_t>(maximum)) {
            return { last, errc::value_too_large };
          }
          append_c_digits(maximum, digits, first);
          first += maximum;
        }
        break;
      }
    }
#ifdef RYU_DEBUG
    printf("roundUp=%d\n", roundUp);
#endif
    if (roundUp != 0) {
      char* round = first;
      char* dot = last;
      while (true) {
        if (round == original_first) {
          round[0] = '1';
          if (dot != last) {
            dot[0] = '0';
            dot[1] = '.';
          }
          if (first == last) {
            return { last, errc::value_too_large };
          }
          *first++ = '0';
          break;
        }
        --round;
        const char c = round[0];
        if (c == '.') {
          dot = round;
        } else if (c == '9') {
          round[0] = '0';
          roundUp = 1;
        } else {
          if (roundUp == 1 || c % 2 != 0) {
            round[0] = c + 1;
          }
          break;
        }
      }
    }
  } else {
    if (last - first < static_cast<ptrdiff_t>(precision)) {
      return { last, errc::value_too_large };
    }
    hamon::ct::memset(first, '0', precision);
    first += precision;
  }
  return { first, errc{} };
}

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result d2exp_buffered_n(char* first, char* const last, const double d,
  uint32_t precision) {
  char* const original_first = first;

  const uint64_t bits = double_to_bits(d);
#ifdef RYU_DEBUG
  printf("IN=");
  for (int32_t bit = 63; bit >= 0; --bit) {
    printf("%d", (int) ((bits >> bit) & 1));
  }
  printf("\n");
#endif

  // Case distinction; exit early for the easy cases.
  if (bits == 0) {
    const int32_t total_zero_length = 1 // leading zero
      + static_cast<int32_t>(precision != 0) // possible decimal point
      + static_cast<int32_t>(precision) // zeroes after decimal point
      + 4; // "e+00"
    if (last - first < total_zero_length) {
      return { last, errc::value_too_large };
    }
    *first++ = '0';
    if (precision > 0) {
      *first++ = '.';
      hamon::ct::memset(first, '0', precision);
      first += precision;
    }
    hamon::ct::memcpy(first, "e+00", 4);
    first += 4;
    return { first, errc{} };
  }

  // Decode bits into mantissa and exponent.
  const uint64_t ieeeMantissa = bits & ((1ull << DOUBLE_MANTISSA_BITS) - 1);
  const uint32_t ieeeExponent = static_cast<uint32_t>(bits >> DOUBLE_MANTISSA_BITS);

  int32_t e2;
  uint64_t m2;
  if (ieeeExponent == 0) {
    e2 = 1 - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
    m2 = ieeeMantissa;
  } else {
    e2 = (int32_t) ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;
    m2 = (1ull << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
  }

#ifdef RYU_DEBUG
  printf("-> %" PRIu64 " * 2^%d\n", m2, e2);
#endif

  const bool printDecimalPoint = precision > 0;
  ++precision;
  uint32_t digits = 0;
  uint32_t printedDigits = 0;
  uint32_t availableDigits = 0;
  int32_t exp = 0;
  if (e2 >= -52) {
    const uint32_t idx = e2 < 0 ? 0 : indexForExponent((uint32_t) e2);
    const uint32_t p10bits = pow10BitsForIndex(idx);
    const int32_t len = (int32_t) lengthForIndex(idx);
#ifdef RYU_DEBUG
    printf("idx=%u\n", idx);
    printf("len=%d\n", len);
#endif
    for (int32_t i = len - 1; i >= 0; --i) {
      const uint32_t j = p10bits - static_cast<uint32_t>(e2);
      // Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
      // a slightly faster code path in mulShift_mod1e9. Instead, we can just increase the multipliers.
      digits = mulShift_mod1e9(m2 << 8, POW10_SPLIT[POW10_OFFSET[idx] + i], (int32_t) (j + 8));
      if (printedDigits != 0) {
        if (printedDigits + 9 > precision) {
          availableDigits = 9;
          break;
        }
        if (last - first < 9) {
          return { last, errc::value_too_large };
        }
        append_nine_digits(digits, first);
        first += 9;
        printedDigits += 9;
      } else if (digits != 0) {
        availableDigits = decimalLength9(digits);
        exp = i * 9 + (int32_t) availableDigits - 1;
        if (availableDigits > precision) {
          break;
        }
        if (printDecimalPoint) {
          if (last - first < static_cast<ptrdiff_t>(availableDigits + 1)) {
            return { last, errc::value_too_large };
          }
          append_d_digits(availableDigits, digits, first);
          first += availableDigits + 1; // +1 for decimal point
        } else {
          if (first == last) {
            return { last, errc::value_too_large };
          }
          *first++ = static_cast<char>('0' + digits);
        }
        printedDigits = availableDigits;
        availableDigits = 0;
      }
    }
  }

  if (e2 < 0 && availableDigits == 0) {
    const int32_t idx = -e2 / 16;
#ifdef RYU_DEBUG
    printf("idx=%d, e2=%d, min=%d\n", idx, e2, MIN_BLOCK_2[idx]);
#endif
    for (int32_t i = MIN_BLOCK_2[idx]; i < 200; ++i) {
      const int32_t j = ADDITIONAL_BITS_2 + (-e2 - 16 * idx);
      const uint32_t p = POW10_OFFSET_2[idx] + (uint32_t) i - MIN_BLOCK_2[idx];
      // Temporary: j is usually around 128, and by shifting a bit, we push it to 128 or above, which is
      // a slightly faster code path in mulShift_mod1e9. Instead, we can just increase the multipliers.
      digits = (p >= POW10_OFFSET_2[idx + 1]) ? 0 : mulShift_mod1e9(m2 << 8, POW10_SPLIT_2[p], j + 8);
#ifdef RYU_DEBUG
      printf("exact=%" PRIu64 " * (%" PRIu64 " + %" PRIu64 " << 64) >> %d\n", m2, POW10_SPLIT_2[p][0], POW10_SPLIT_2[p][1], j);
      printf("digits=%u\n", digits);
#endif
      if (printedDigits != 0) {
        if (printedDigits + 9 > precision) {
          availableDigits = 9;
          break;
        }
        if (last - first < 9) {
          return { last, errc::value_too_large };
        }
        append_nine_digits(digits, first);
        first += 9;
        printedDigits += 9;
      } else if (digits != 0) {
        availableDigits = decimalLength9(digits);
        exp = -(i + 1) * 9 + (int32_t) availableDigits - 1;
        if (availableDigits > precision) {
          break;
        }
        if (printDecimalPoint) {
          if (last - first < static_cast<ptrdiff_t>(availableDigits + 1)) {
            return { last, errc::value_too_large };
          }
          append_d_digits(availableDigits, digits, first);
          first += availableDigits + 1; // +1 for decimal point
        } else {
          if (first == last) {
            return { last, errc::value_too_large };
          }
          *first++ = static_cast<char>('0' + digits);
        }
        printedDigits = availableDigits;
        availableDigits = 0;
      }
    }
  }

  const uint32_t maximum = precision - printedDigits;
#ifdef RYU_DEBUG
  printf("availableDigits=%u\n", availableDigits);
  printf("digits=%u\n", digits);
  printf("maximum=%u\n", maximum);
#endif
  if (availableDigits == 0) {
    digits = 0;
  }
  uint32_t lastDigit = 0;
  if (availableDigits > maximum) {
    for (uint32_t k = 0; k < availableDigits - maximum; ++k) {
      lastDigit = digits % 10;
      digits /= 10;
    }
  }
#ifdef RYU_DEBUG
  printf("lastDigit=%u\n", lastDigit);
#endif
  // 0 = don't round up; 1 = round up unconditionally; 2 = round up if odd.
  int roundUp = 0;
  if (lastDigit != 5) {
    roundUp = lastDigit > 5;
  } else {
    // Is m * 2^e2 * 10^(precision + 1 - exp) integer?
    // precision was already increased by 1, so we don't need to write + 1 here.
    const int32_t rexp = (int32_t) precision - exp;
    const int32_t requiredTwos = -e2 - rexp;
    bool trailingZeros = requiredTwos <= 0
      || (requiredTwos < 60 && multipleOfPowerOf2(m2, (uint32_t) requiredTwos));
    if (rexp < 0) {
      const int32_t requiredFives = -rexp;
      trailingZeros = trailingZeros && multipleOfPowerOf5(m2, (uint32_t) requiredFives);
    }
    roundUp = trailingZeros ? 2 : 1;
#ifdef RYU_DEBUG
    printf("requiredTwos=%d\n", requiredTwos);
    printf("trailingZeros=%s\n", trailingZeros ? "true" : "false");
#endif
  }
  if (printedDigits != 0) {
    if (last - first < static_cast<ptrdiff_t>(maximum)) {
      return { last, errc::value_too_large };
    }
    if (digits == 0) {
      hamon::ct::memset(first, '0', maximum);
    } else {
      append_c_digits(maximum, digits, first);
    }
    first += maximum;
  } else {
    if (printDecimalPoint) {
      if (last - first < static_cast<ptrdiff_t>(maximum + 1)) {
        return { last, errc::value_too_large };
      }
      append_d_digits(maximum, digits, first);
      first += maximum + 1; // +1 for decimal point
    } else {
      if (first == last) {
        return { last, errc::value_too_large };
      }
      *first++ = static_cast<char>('0' + digits);
    }
  }
#ifdef RYU_DEBUG
  printf("roundUp=%d\n", roundUp);
#endif
  if (roundUp != 0) {
    char* round = first;
    while (true) {
      if (round == original_first) {
        round[0] = '1';
        ++exp;
        break;
      }
      --round;
      const char c = round[0];
      if (c == '.') {
        // Keep going.
      } else if (c == '9') {
        round[0] = '0';
        roundUp = 1;
      } else {
        if (roundUp == 1 || c % 2 != 0) {
          round[0] = c + 1;
        }
        break;
      }
    }
  }

  char sign_character;

  if (exp < 0) {
    sign_character = '-';
    exp = -exp;
  } else {
    sign_character = '+';
  }

  const int exponent_part_length = exp >= 100
    ? 5 // "e+NNN"
    : 4; // "e+NN"

  if (last - first < exponent_part_length) {
    return { last, errc::value_too_large };
  }

  *first++ = 'e';
  *first++ = sign_character;

  if (exp >= 100) {
    const int32_t c = exp % 10;
    hamon::ct::memcpy(first, DIGIT_TABLE + 2 * (exp / 10), 2);
    first[2] = (char) ('0' + c);
    first += 3;
  } else {
    hamon::ct::memcpy(first, DIGIT_TABLE + 2 * exp, 2);
    first += 2;
  }

  return { first, errc{} };
}

HAMON_WARNING_POP()

}	// namespace ryu
}	// namespace detail
}	// namespace hamon

#endif // RYU_D2FIXED_HPP
