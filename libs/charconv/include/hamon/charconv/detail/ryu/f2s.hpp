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
#ifndef RYU_F2S_HPP
#define RYU_F2S_HPP

#include "hamon/charconv/detail/ryu/ryu.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#ifdef RYU_DEBUG
#include <stdio.h>
#endif

#include "hamon/charconv/detail/ryu/common.h"
#include "hamon/charconv/detail/ryu/f2s_intrinsics.h"
#include "hamon/charconv/detail/ryu/d2s_intrinsics.h"
#include "hamon/charconv/detail/ryu/digit_table.h"
#include "hamon/charconv/detail/ryu/d2fixed.hpp"

#include "hamon/bit/countr_zero.hpp"
#include "hamon/cstring/memcpy.hpp"
#include "hamon/cstring/memmove.hpp"
#include "hamon/cstring/memset.hpp"

#define FLOAT_MANTISSA_BITS 23
#define FLOAT_EXPONENT_BITS 8
#define FLOAT_BIAS 127

namespace hamon {
namespace detail {
namespace ryu {

// A floating decimal representing m * 10^e.
typedef struct floating_decimal_32 {
  uint32_t mantissa;
  // Decimal exponent's range is -45 to 38
  // inclusive, and can fit in a short if needed.
  int32_t exponent;
} floating_decimal_32;

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result large_integer_to_chars(char* const first, char* const last,
  const uint32_t mantissa2, const int32_t exponent2) {

  // Print the integer mantissa2 * 2^exponent2 exactly.

  // For nonzero integers, exponent2 >= -23. (The minimum value occurs when mantissa2 * 2^exponent2 is 1.
  // In that case, mantissa2 is the implicit 1 bit followed by 23 zeros, so exponent2 is -23 to shift away
  // the zeros.) The dense range of exactly representable integers has negative or zero exponents
  // (as positive exponents make the range non-dense). For that dense range, Ryu will always be used:
  // every digit is necessary to uniquely identify the value, so Ryu must print them all.

  // Positive exponents are the non-dense range of exactly representable integers.
  // This contains all of the values for which Ryu can't be used (and a few Ryu-friendly values).

  // Performance note: Long division appears to be faster than losslessly widening float to double and calling
  // __d2fixed_buffered_n(). If __f2fixed_buffered_n() is implemented, it might be faster than long division.

  assert(exponent2 > 0);
  assert(exponent2 <= 104); // because ieeeExponent <= 254

  // Manually represent mantissa2 * 2^exponent2 as a large integer. mantissa2 is always 24 bits
  // (due to the implicit bit), while exponent2 indicates a shift of at most 104 bits.
  // 24 + 104 equals 128 equals 4 * 32, so we need exactly 4 32-bit elements.
  // We use a little-endian representation, visualized like this:

  // << left shift <<
  // most significant
  // data[3] data[2] data[1] data[0]
  //                   least significant
  //                   >> right shift >>

  constexpr uint32_t data_size = 4;
  uint32_t data[data_size]{};

  // maxidx is the index of the most significant nonzero element.
  uint32_t maxidx = ((24 + (uint32_t)(exponent2) + 31) / 32) - 1;
  assert(maxidx < data_size);

  const uint32_t bit_shift = (uint32_t)(exponent2) % 32;
  if (bit_shift <= 8) { // mantissa2's 24 bits don't cross an element boundary
    data[maxidx] = mantissa2 << bit_shift;
  } else { // mantissa2's 24 bits cross an element boundary
    data[maxidx - 1] = mantissa2 << bit_shift;
    data[maxidx] = mantissa2 >> (32 - bit_shift);
  }

  // If Ryu hasn't determined the total output length, we need to buffer the digits generated from right to left
  // by long division. The largest possible float is: 340'282346638'528859811'704183484'516925440
  uint32_t blocks[4];
  int32_t filled_blocks = 0;
  // From left to right, we're going to print:
  // data[0] will be [1, 10] digits.
  // Then if filled_blocks > 0:
  // blocks[filled_blocks - 1], ..., blocks[0] will be 0-filled 9-digit blocks.

  if (maxidx != 0) { // If the integer is actually large, perform long division.
                      // Otherwise, skip to printing data[0].
    for (;;) {
      // Loop invariant: maxidx != 0 (i.e. the integer is actually large)

      const uint32_t most_significant_elem = data[maxidx];
      const uint32_t initial_remainder = most_significant_elem % 1000000000;
      const uint32_t initial_quotient = most_significant_elem / 1000000000;
      data[maxidx] = initial_quotient;
      uint64_t remainder = initial_remainder;

      // Process less significant elements.
      uint32_t idx = maxidx;
      do {
        --idx; // Initially, remainder is at most 10^9 - 1.

        // Now, remainder is at most (10^9 - 1) * 2^32 + 2^32 - 1, simplified to 10^9 * 2^32 - 1.
        remainder = (remainder << 32) | data[idx];

        // floor((10^9 * 2^32 - 1) / 10^9) == 2^32 - 1, so uint32_t quotient is lossless.
        const uint32_t quotient = (uint32_t)(div1e9(remainder));

        // remainder is at most 10^9 - 1 again.
        // For uint32_t truncation, see the __mod1e9() comment in d2s_intrinsics.h.
        remainder = (uint32_t)(remainder) - 1000000000u * quotient;

        data[idx] = quotient;
      } while (idx != 0);

      // Store a 0-filled 9-digit block.
      blocks[filled_blocks++] = (uint32_t)(remainder);

      if (initial_quotient == 0) { // Is the large integer shrinking?
        --maxidx; // log2(10^9) is 29.9, so we can't shrink by more than one element.
        if (maxidx == 0) {
          break; // We've finished long division. Now we need to print data[0].
        }
      }
    }
  }

  assert(data[0] != 0);
  for (uint32_t idx = 1; idx < data_size; ++idx) {
    assert(data[idx] == 0);
  }

  const uint32_t data_olength = data[0] >= 1000000000 ? 10 : decimalLength9(data[0]);
  const uint32_t total_fixed_length = data_olength + 9 * static_cast<uint32_t>(filled_blocks);

  if (last - first < static_cast<ptrdiff_t>(total_fixed_length)) {
    return { last, errc::value_too_large };
  }

  char* result = first;

  // Print data[0]. While it's up to 10 digits,
  // which is more than Ryu generates, the code below can handle this.
  append_n_digits(data_olength, data[0], result);
  result += data_olength;

  // Print 0-filled 9-digit blocks.
  for (int32_t idx = filled_blocks - 1; idx >= 0; --idx) {
    append_nine_digits(blocks[idx], result);
    result += 9;
  }

  return { result, errc{} };
}

static inline HAMON_CXX20_CONSTEXPR floating_decimal_32 f2d(const uint32_t ieeeMantissa, const uint32_t ieeeExponent) {
  int32_t e2;
  uint32_t m2;
  if (ieeeExponent == 0) {
    // We subtract 2 so that the bounds computation has 2 additional bits.
    e2 = 1 - FLOAT_BIAS - FLOAT_MANTISSA_BITS - 2;
    m2 = ieeeMantissa;
  } else {
    e2 = (int32_t) ieeeExponent - FLOAT_BIAS - FLOAT_MANTISSA_BITS - 2;
    m2 = (1u << FLOAT_MANTISSA_BITS) | ieeeMantissa;
  }
  const bool even = (m2 & 1) == 0;
  const bool acceptBounds = even;

#ifdef RYU_DEBUG
  printf("-> %u * 2^%d\n", m2, e2 + 2);
#endif

  // Step 2: Determine the interval of valid decimal representations.
  const uint32_t mv = 4 * m2;
  const uint32_t mp = 4 * m2 + 2;
  // Implicit bool -> int conversion. True is 1, false is 0.
  const uint32_t mmShift = ieeeMantissa != 0 || ieeeExponent <= 1;
  const uint32_t mm = 4 * m2 - 1 - mmShift;

  // Step 3: Convert to a decimal power base using 64-bit arithmetic.
  uint32_t vr, vp, vm;
  int32_t e10;
  bool vmIsTrailingZeros = false;
  bool vrIsTrailingZeros = false;
  uint8_t lastRemovedDigit = 0;
  if (e2 >= 0) {
    const uint32_t q = log10Pow2(e2);
    e10 = (int32_t) q;
    const int32_t k = FLOAT_POW5_INV_BITCOUNT + pow5bits((int32_t) q) - 1;
    const int32_t i = -e2 + (int32_t) q + k;
    vr = mulPow5InvDivPow2(mv, q, i);
    vp = mulPow5InvDivPow2(mp, q, i);
    vm = mulPow5InvDivPow2(mm, q, i);
#ifdef RYU_DEBUG
    printf("%u * 2^%d / 10^%u\n", mv, e2, q);
    printf("V+=%u\nV =%u\nV-=%u\n", vp, vr, vm);
#endif
    if (q != 0 && (vp - 1) / 10 <= vm / 10) {
      // We need to know one removed digit even if we are not going to loop below. We could use
      // q = X - 1 above, except that would require 33 bits for the result, and we've found that
      // 32-bit arithmetic is faster even on 64-bit machines.
      const int32_t l = FLOAT_POW5_INV_BITCOUNT + pow5bits((int32_t) (q - 1)) - 1;
      lastRemovedDigit = (uint8_t) (mulPow5InvDivPow2(mv, q - 1, -e2 + (int32_t) q - 1 + l) % 10);
    }
    if (q <= 9) {
      // The largest power of 5 that fits in 24 bits is 5^10, but q <= 9 seems to be safe as well.
      // Only one of mp, mv, and mm can be a multiple of 5, if any.
      if (mv % 5 == 0) {
        vrIsTrailingZeros = multipleOfPowerOf5_32(mv, q);
      } else if (acceptBounds) {
        vmIsTrailingZeros = multipleOfPowerOf5_32(mm, q);
      } else {
        vp -= multipleOfPowerOf5_32(mp, q);
      }
    }
  } else {
    const uint32_t q = log10Pow5(-e2);
    e10 = (int32_t) q + e2;
    const int32_t i = -e2 - (int32_t) q;
    const int32_t k = pow5bits(i) - FLOAT_POW5_BITCOUNT;
    int32_t j = (int32_t) q - k;
    vr = mulPow5divPow2(mv, (uint32_t) i, j);
    vp = mulPow5divPow2(mp, (uint32_t) i, j);
    vm = mulPow5divPow2(mm, (uint32_t) i, j);
#ifdef RYU_DEBUG
    printf("%u * 5^%d / 10^%u\n", mv, -e2, q);
    printf("%u %d %d %d\n", q, i, k, j);
    printf("V+=%u\nV =%u\nV-=%u\n", vp, vr, vm);
#endif
    if (q != 0 && (vp - 1) / 10 <= vm / 10) {
      j = (int32_t) q - 1 - (pow5bits(i + 1) - FLOAT_POW5_BITCOUNT);
      lastRemovedDigit = (uint8_t) (mulPow5divPow2(mv, (uint32_t) (i + 1), j) % 10);
    }
    if (q <= 1) {
      // {vr,vp,vm} is trailing zeros if {mv,mp,mm} has at least q trailing 0 bits.
      // mv = 4 * m2, so it always has at least two trailing 0 bits.
      vrIsTrailingZeros = true;
      if (acceptBounds) {
        // mm = mv - 1 - mmShift, so it has 1 trailing 0 bit iff mmShift == 1.
        vmIsTrailingZeros = mmShift == 1;
      } else {
        // mp = mv + 2, so it always has at least one trailing 0 bit.
        --vp;
      }
    } else if (q < 31) { // TODO(ulfjack): Use a tighter bound here.
      vrIsTrailingZeros = multipleOfPowerOf2_32(mv, q - 1);
#ifdef RYU_DEBUG
      printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif
    }
  }
#ifdef RYU_DEBUG
  printf("e10=%d\n", e10);
  printf("V+=%u\nV =%u\nV-=%u\n", vp, vr, vm);
  printf("vm is trailing zeros=%s\n", vmIsTrailingZeros ? "true" : "false");
  printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif

  // Step 4: Find the shortest decimal representation in the interval of valid representations.
  int32_t removed = 0;
  uint32_t output;
  if (vmIsTrailingZeros || vrIsTrailingZeros) {
    // General case, which happens rarely (~4.0%).
    while (vp / 10 > vm / 10) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=23106
      // The compiler does not realize that vm % 10 can be computed from vm / 10
      // as vm - (vm / 10) * 10.
      vmIsTrailingZeros &= vm - (vm / 10) * 10 == 0;
#else
      vmIsTrailingZeros &= vm % 10 == 0;
#endif
      vrIsTrailingZeros &= lastRemovedDigit == 0;
      lastRemovedDigit = (uint8_t) (vr % 10);
      vr /= 10;
      vp /= 10;
      vm /= 10;
      ++removed;
    }
#ifdef RYU_DEBUG
    printf("V+=%u\nV =%u\nV-=%u\n", vp, vr, vm);
    printf("d-10=%s\n", vmIsTrailingZeros ? "true" : "false");
#endif
    if (vmIsTrailingZeros) {
      while (vm % 10 == 0) {
        vrIsTrailingZeros &= lastRemovedDigit == 0;
        lastRemovedDigit = (uint8_t) (vr % 10);
        vr /= 10;
        vp /= 10;
        vm /= 10;
        ++removed;
      }
    }
#ifdef RYU_DEBUG
    printf("%u %d\n", vr, lastRemovedDigit);
    printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif
    if (vrIsTrailingZeros && lastRemovedDigit == 5 && vr % 2 == 0) {
      // Round even if the exact number is .....50..0.
      lastRemovedDigit = 4;
    }
    // We need to take vr + 1 if vr is outside bounds or we need to round up.
    output = vr + ((vr == vm && (!acceptBounds || !vmIsTrailingZeros)) || lastRemovedDigit >= 5);
  } else {
    // Specialized for the common case (~96.0%). Percentages below are relative to this.
    // Loop iterations below (approximately):
    // 0: 13.6%, 1: 70.7%, 2: 14.1%, 3: 1.39%, 4: 0.14%, 5+: 0.01%
    while (vp / 10 > vm / 10) {
      lastRemovedDigit = (uint8_t) (vr % 10);
      vr /= 10;
      vp /= 10;
      vm /= 10;
      ++removed;
    }
#ifdef RYU_DEBUG
    printf("%u %d\n", vr, lastRemovedDigit);
    printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif
    // We need to take vr + 1 if vr is outside bounds or we need to round up.
    output = vr + (vr == vm || lastRemovedDigit >= 5);
  }
  const int32_t exp = e10 + removed;

#ifdef RYU_DEBUG
  printf("V+=%u\nV =%u\nV-=%u\n", vp, vr, vm);
  printf("O=%u\n", output);
  printf("EXP=%d\n", exp);
#endif

  floating_decimal_32 fd;
  fd.exponent = exp;
  fd.mantissa = output;
  return fd;
}

static inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result to_chars(char* const first, char* const last, const floating_decimal_32 v,
  chars_format fmt, const uint32_t ieeeMantissa, const uint32_t ieeeExponent) {
  // Step 5: Print the decimal representation.
  uint32_t output = v.mantissa;
  int32_t ryu_exponent = v.exponent;
  const uint32_t olength = decimalLength9(output);
  int32_t scientific_exponent = ryu_exponent + (int32_t)(olength) - 1;

#ifdef RYU_DEBUG
  printf("DIGITS=%u\n", v.mantissa);
  printf("OLEN=%u\n", olength);
  printf("EXP=%u\n", v.exponent + olength);
#endif

  if (fmt == chars_format{}) {
    int32_t lower;
    int32_t upper;

    if (olength == 1) {
      // Value | Fixed   | Scientific
      // 1e-3  | "0.001" | "1e-03"
      // 1e4   | "10000" | "1e+04"
      lower = -3;
      upper = 4;
    } else {
      // Value   | Fixed       | Scientific
      // 1234e-7 | "0.0001234" | "1.234e-04"
      // 1234e5  | "123400000" | "1.234e+08"
      lower = -(int32_t)(olength + 3);
      upper = 5;
    }

    if (lower <= ryu_exponent && ryu_exponent <= upper) {
      fmt = chars_format::fixed;
    } else {
      fmt = chars_format::scientific;
    }
  } else if (fmt == chars_format::general) {
    // C11 7.21.6.1 "The fprintf function"/8:
    // "Let P equal [...] 6 if the precision is omitted [...].
    // Then, if a conversion with style E would have an exponent of X:
    // - if P > X >= -4, the conversion is with style f [...].
    // - otherwise, the conversion is with style e [...]."
    if (-4 <= scientific_exponent && scientific_exponent < 6) {
      fmt = chars_format::fixed;
    } else {
      fmt = chars_format::scientific;
    }
  }

  if (fmt == chars_format::fixed) {
    // Example: output == 1729, olength == 4

    // ryu_exponent  | Printed  | whole_digits  | total_fixed_length   | Notes
    // --------------|----------|---------------|----------------------|---------------------------------------
    //             2 | 172900   |  6            | whole_digits         | Ryu can't be used for printing
    //             1 | 17290    |  5            | (sometimes adjusted) | when the trimmed digits are nonzero.
    // --------------|----------|---------------|----------------------|---------------------------------------
    //             0 | 1729     |  4            | whole_digits         | Unified length cases.
    // --------------|----------|---------------|----------------------|---------------------------------------
    //            -1 | 172.9    |  3            | olength + 1          | This case can't happen for
    //            -2 | 17.29    |  2            |                      | olength == 1, but no additional
    //            -3 | 1.729    |  1            |                      | code is needed to avoid it.
    // --------------|----------|---------------|----------------------|---------------------------------------
    //            -4 | 0.1729   |  0            | 2 - ryu_exponent     | C11 7.21.6.1 "The fprintf function"/8:
    //            -5 | 0.01729  | -1            |                      | "If a decimal-point character appears,
    //            -6 | 0.001729 | -2            |                      | at least one digit appears before it."

    const int32_t whole_digits = (int32_t)(olength) + ryu_exponent;

    uint32_t total_fixed_length;
    if (ryu_exponent >= 0) { // cases "172900" and "1729"
      total_fixed_length = (uint32_t)(whole_digits);
      if (output == 1) {
        // Rounding can affect the number of digits.
        // For example, 1e11f is exactly "99999997952" which is 11 digits instead of 12.
        // We can use a lookup table to detect this and adjust the total length.
        const uint8_t adjustment[39] = {
          0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,0,1,1,0,1,1,1 };
        total_fixed_length -= adjustment[ryu_exponent];
        // whole_digits doesn't need to be adjusted because these cases won't refer to it later.
      }
    } else if (whole_digits > 0) { // case "17.29"
      total_fixed_length = olength + 1;
    } else { // case "0.001729"
      total_fixed_length = (uint32_t)(2 - ryu_exponent);
    }

    if (last - first < static_cast<ptrdiff_t>(total_fixed_length)) {
      return { last, errc::value_too_large };
    }

    char* mid;
    if (ryu_exponent > 0) { // case "172900"
      bool can_use_ryu;

      if (ryu_exponent > 10) { // 10^10 is the largest power of 10 that's exactly representable as a float.
        can_use_ryu = false;
      } else {
        // Ryu generated X: v.mantissa * 10^ryu_exponent
        // v.mantissa == 2^trailing_zero_bits * (v.mantissa >> trailing_zero_bits)
        // 10^ryu_exponent == 2^ryu_exponent * 5^ryu_exponent

        // trailing_zero_bits is [0, 29] (aside: because 2^29 is the largest power of 2
        // with 9 decimal digits, which is float's round-trip limit.)
        // ryu_exponent is [1, 10].
        // Normalization adds [2, 23] (aside: at least 2 because the pre-normalized mantissa is at least 5).
        // This adds up to [3, 62], which is well below float's maximum binary exponent 127.

        // Therefore, we just need to consider (v.mantissa >> trailing_zero_bits) * 5^ryu_exponent.

        // If that product would exceed 24 bits, then X can't be exactly represented as a float.
        // (That's not a problem for round-tripping, because X is close enough to the original float,
        // but X isn't mathematically equal to the original float.) This requires a high-precision fallback.

        // If the product is 24 bits or smaller, then X can be exactly represented as a float (and we don't
        // need to re-synthesize it; the original float must have been X, because Ryu wouldn't produce the
        // same output for two different floats X and Y). This allows Ryu's output to be used (zero-filled).

        // (2^24 - 1) / 5^0 (for indexing), (2^24 - 1) / 5^1, ..., (2^24 - 1) / 5^10
        const uint32_t max_shifted_mantissa[11] = {
          16777215, 3355443, 671088, 134217, 26843, 5368, 1073, 214, 42, 8, 1 };
        auto trailing_zero_bits = hamon::countr_zero(v.mantissa); // v.mantissa is guaranteed nonzero
        const uint32_t shifted_mantissa = v.mantissa >> trailing_zero_bits;
        can_use_ryu = shifted_mantissa <= max_shifted_mantissa[ryu_exponent];
      }

      if (!can_use_ryu) {
        const uint32_t mantissa2 = ieeeMantissa | (1u << FLOAT_MANTISSA_BITS); // restore implicit bit
        const int32_t exponent2 = (int32_t)(ieeeExponent)
          - FLOAT_BIAS - FLOAT_MANTISSA_BITS; // bias and normalization

        // Performance note: We've already called Ryu, so this will redundantly perform buffering and bounds checking.
        return large_integer_to_chars(first, last, mantissa2, exponent2);
      }

      // can_use_ryu
      // Print the decimal digits, left-aligned within [first, first + total_fixed_length).
      mid = first + olength;
    } else { // cases "1729", "17.29", and "0.001729"
      // Print the decimal digits, right-aligned within [first, first + total_fixed_length).
      mid = first + total_fixed_length;
    }

    while (output >= 10000) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=38217
      const uint32_t c = output - 10000 * (output / 10000);
#else
      const uint32_t c = output % 10000;
#endif
      output /= 10000;
      const uint32_t c0 = (c % 100) << 1;
      const uint32_t c1 = (c / 100) << 1;
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c0, 2);
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c1, 2);
    }
    if (output >= 100) {
      const uint32_t c = (output % 100) << 1;
      output /= 100;
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c, 2);
    }
    if (output >= 10) {
      const uint32_t c = output << 1;
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c, 2);
    } else {
      *--mid = static_cast<char>('0' + output);
    }

    if (ryu_exponent > 0) { // case "172900" with can_use_ryu
      // Performance note: it might be more efficient to do this immediately after setting mid.
      hamon::ct::memset(first + olength, '0', static_cast<size_t>(ryu_exponent));
    } else if (ryu_exponent == 0) { // case "1729"
      // Done!
    } else if (whole_digits > 0) { // case "17.29"
      // Performance note: moving digits might not be optimal.
      hamon::ct::memmove(first, first + 1, static_cast<size_t>(whole_digits));
      first[whole_digits] = '.';
    } else { // case "0.001729"
      // Performance note: a larger memset() followed by overwriting '.' might be more efficient.
      first[0] = '0';
      first[1] = '.';
      hamon::ct::memset(first + 2, '0', static_cast<size_t>(-whole_digits));
    }

    return { first + total_fixed_length, errc{} };
  }

  const uint32_t total_scientific_length =
    olength + (olength > 1) + 4; // digits + possible decimal point + scientific exponent
  if (last - first < static_cast<ptrdiff_t>(total_scientific_length)) {
    return { last, errc::value_too_large };
  }
  char* const result = first;

  // Print the decimal digits.
  // The following code is equivalent to:
  // for (uint32_t i = 0; i < olength - 1; ++i) {
  //   const uint32_t c = output % 10; output /= 10;
  //   result[index + olength - i] = (char) ('0' + c);
  // }
  // result[index] = '0' + output % 10;
  uint32_t i = 0;
  while (output >= 10000) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=38217
    const uint32_t c = output - 10000 * (output / 10000);
#else
    const uint32_t c = output % 10000;
#endif
    output /= 10000;
    const uint32_t c0 = (c % 100) << 1;
    const uint32_t c1 = (c / 100) << 1;
    hamon::ct::memcpy(result + olength - i - 1, DIGIT_TABLE + c0, 2);
    hamon::ct::memcpy(result + olength - i - 3, DIGIT_TABLE + c1, 2);
    i += 4;
  }
  if (output >= 100) {
    const uint32_t c = (output % 100) << 1;
    output /= 100;
    hamon::ct::memcpy(result + olength - i - 1, DIGIT_TABLE + c, 2);
    i += 2;
  }
  if (output >= 10) {
    const uint32_t c = output << 1;
    // We can't use memcpy here: the decimal dot goes between these two digits.
    result[2] = DIGIT_TABLE[c + 1];
    result[0] = DIGIT_TABLE[c];
  } else {
    result[0] = (char) ('0' + output);
  }

  // Print decimal point if needed.
  uint32_t index;
  if (olength > 1) {
    result[1] = '.';
    index = olength + 1;
  } else {
    index = 1;
  }

  // Print the exponent.
  result[index++] = 'e';
  if (scientific_exponent < 0) {
    result[index++] = '-';
    scientific_exponent = -scientific_exponent;
  } else {
    result[index++] = '+';
  }

  hamon::ct::memcpy(result + index, DIGIT_TABLE + 2 * scientific_exponent, 2);
  index += 2;

  return { first + total_scientific_length, errc{} };
}

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result f2s_buffered_n(char* const first, char* const last, const float f,
  const chars_format fmt) {

  // Step 1: Decode the floating-point number, and unify normalized and subnormal cases.
  const uint32_t bits = float_to_bits(f);

#ifdef RYU_DEBUG
  printf("IN=");
  for (int32_t bit = 31; bit >= 0; --bit) {
    printf("%u", (bits >> bit) & 1);
  }
  printf("\n");
#endif

  // Decode bits into mantissa and exponent.
  const uint32_t ieeeMantissa = bits & ((1u << FLOAT_MANTISSA_BITS) - 1);
  const uint32_t ieeeExponent = bits >> FLOAT_MANTISSA_BITS;

  // When fmt == chars_format::fixed and the floating-point number is a large integer,
  // it's faster to skip Ryu and immediately print the integer exactly.
  if (fmt == chars_format::fixed) {
    const uint32_t mantissa2 = ieeeMantissa | (1u << FLOAT_MANTISSA_BITS); // restore implicit bit
    const int32_t exponent2 = static_cast<int32_t>(ieeeExponent)
      - FLOAT_BIAS - FLOAT_MANTISSA_BITS; // bias and normalization

    // Normal values are equal to mantissa2 * 2^exponent2.
    // (Subnormals are different, but they'll be rejected by the exponent2 test here, so they can be ignored.)

    if (exponent2 > 0) {
      return large_integer_to_chars(first, last, mantissa2, exponent2);
    }
  }

  const floating_decimal_32 v = f2d(ieeeMantissa, ieeeExponent);
  return to_chars(first, last, v, fmt, ieeeMantissa, ieeeExponent);
}

}	// namespace ryu
}	// namespace detail
}	// namespace hamon

#endif // RYU_F2S_HPP
