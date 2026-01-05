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
// -DRYU_OPTIMIZE_SIZE Use smaller lookup tables. Instead of storing every
//     required power of 5, only store every 26th entry, and compute
//     intermediate values with a multiplication. This reduces the lookup table
//     size by about 10x (only one case, and only double) at the cost of some
//     performance. Currently requires MSVC intrinsics.
#ifndef RYU_D2S_HPP
#define RYU_D2S_HPP

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
#include "hamon/charconv/detail/ryu/d2s_intrinsics.h"

// Include either the small or the full lookup tables depending on the mode.
#if defined(RYU_OPTIMIZE_SIZE)
#include "hamon/charconv/detail/ryu/d2s_small_table.h"
#else
#include "hamon/charconv/detail/ryu/d2s_full_table.h"
#endif

#include "hamon/bit/countr_zero.hpp"
#include "hamon/cstring/memcpy.hpp"
#include "hamon/cstring/memmove.hpp"
#include "hamon/cstring/memset.hpp"

#define DOUBLE_MANTISSA_BITS 52
#define DOUBLE_EXPONENT_BITS 11
#define DOUBLE_BIAS 1023

namespace hamon {
namespace detail {
namespace ryu {

static inline HAMON_CXX20_CONSTEXPR uint32_t decimalLength17(const uint64_t v) {
  // This is slightly faster than a loop.
  // The average output length is 16.38 digits, so we check high-to-low.
  // Function precondition: v is not an 18, 19, or 20-digit number.
  // (17 digits are sufficient for round-tripping.)
  assert(v < 100000000000000000L);
  if (v >= 10000000000000000L) { return 17; }
  if (v >= 1000000000000000L) { return 16; }
  if (v >= 100000000000000L) { return 15; }
  if (v >= 10000000000000L) { return 14; }
  if (v >= 1000000000000L) { return 13; }
  if (v >= 100000000000L) { return 12; }
  if (v >= 10000000000L) { return 11; }
  if (v >= 1000000000L) { return 10; }
  if (v >= 100000000L) { return 9; }
  if (v >= 10000000L) { return 8; }
  if (v >= 1000000L) { return 7; }
  if (v >= 100000L) { return 6; }
  if (v >= 10000L) { return 5; }
  if (v >= 1000L) { return 4; }
  if (v >= 100L) { return 3; }
  if (v >= 10L) { return 2; }
  return 1;
}

// A floating decimal representing m * 10^e.
typedef struct floating_decimal_64 {
  uint64_t mantissa;
  // Decimal exponent's range is -324 to 308
  // inclusive, and can fit in a short if needed.
  int32_t exponent;
} floating_decimal_64;

static inline HAMON_CXX20_CONSTEXPR floating_decimal_64 d2d(const uint64_t ieeeMantissa, const uint32_t ieeeExponent) {
  int32_t e2;
  uint64_t m2;
  if (ieeeExponent == 0) {
    // We subtract 2 so that the bounds computation has 2 additional bits.
    e2 = 1 - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS - 2;
    m2 = ieeeMantissa;
  } else {
    e2 = (int32_t) ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS - 2;
    m2 = (1ull << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
  }
  const bool even = (m2 & 1) == 0;
  const bool acceptBounds = even;

#ifdef RYU_DEBUG
  printf("-> %" PRIu64 " * 2^%d\n", m2, e2 + 2);
#endif

  // Step 2: Determine the interval of valid decimal representations.
  const uint64_t mv = 4 * m2;
  // Implicit bool -> int conversion. True is 1, false is 0.
  const uint32_t mmShift = ieeeMantissa != 0 || ieeeExponent <= 1;
  // We would compute mp and mm like this:
  // uint64_t mp = 4 * m2 + 2;
  // uint64_t mm = mv - 1 - mmShift;

  // Step 3: Convert to a decimal power base using 128-bit arithmetic.
  uint64_t vr, vp, vm;
  int32_t e10;
  bool vmIsTrailingZeros = false;
  bool vrIsTrailingZeros = false;
  if (e2 >= 0) {
    // I tried special-casing q == 0, but there was no effect on performance.
    // This expression is slightly faster than max(0, log10Pow2(e2) - 1).
    const uint32_t q = log10Pow2(e2) - (e2 > 3);
    e10 = (int32_t) q;
    const int32_t k = DOUBLE_POW5_INV_BITCOUNT + pow5bits((int32_t) q) - 1;
    const int32_t i = -e2 + (int32_t) q + k;
#if defined(RYU_OPTIMIZE_SIZE)
    uint64_t pow5[2];
    double_computeInvPow5(q, pow5);
    vr = mulShiftAll64(m2, pow5, i, &vp, &vm, mmShift);
#else
    vr = mulShiftAll64(m2, DOUBLE_POW5_INV_SPLIT[q], i, &vp, &vm, mmShift);
#endif
#ifdef RYU_DEBUG
    printf("%" PRIu64 " * 2^%d / 10^%u\n", mv, e2, q);
    printf("V+=%" PRIu64 "\nV =%" PRIu64 "\nV-=%" PRIu64 "\n", vp, vr, vm);
#endif
    if (q <= 21) {
      // This should use q <= 22, but I think 21 is also safe. Smaller values
      // may still be safe, but it's more difficult to reason about them.
      // Only one of mp, mv, and mm can be a multiple of 5, if any.
      const uint32_t mvMod5 = ((uint32_t) mv) - 5 * ((uint32_t) div5(mv));
      if (mvMod5 == 0) {
        vrIsTrailingZeros = multipleOfPowerOf5(mv, q);
      } else if (acceptBounds) {
        // Same as min(e2 + (~mm & 1), pow5Factor(mm)) >= q
        // <=> e2 + (~mm & 1) >= q && pow5Factor(mm) >= q
        // <=> true && pow5Factor(mm) >= q, since e2 >= q.
        vmIsTrailingZeros = multipleOfPowerOf5(mv - 1 - mmShift, q);
      } else {
        // Same as min(e2 + 1, pow5Factor(mp)) >= q.
        vp -= multipleOfPowerOf5(mv + 2, q);
      }
    }
  } else {
    // This expression is slightly faster than max(0, log10Pow5(-e2) - 1).
    const uint32_t q = log10Pow5(-e2) - (-e2 > 1);
    e10 = (int32_t) q + e2;
    const int32_t i = -e2 - (int32_t) q;
    const int32_t k = pow5bits(i) - DOUBLE_POW5_BITCOUNT;
    const int32_t j = (int32_t) q - k;
#if defined(RYU_OPTIMIZE_SIZE)
    uint64_t pow5[2];
    double_computePow5(i, pow5);
    vr = mulShiftAll64(m2, pow5, j, &vp, &vm, mmShift);
#else
    vr = mulShiftAll64(m2, DOUBLE_POW5_SPLIT[i], j, &vp, &vm, mmShift);
#endif
#ifdef RYU_DEBUG
    printf("%" PRIu64 " * 5^%d / 10^%u\n", mv, -e2, q);
    printf("%u %d %d %d\n", q, i, k, j);
    printf("V+=%" PRIu64 "\nV =%" PRIu64 "\nV-=%" PRIu64 "\n", vp, vr, vm);
#endif
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
    } else if (q < 63) { // TODO(ulfjack): Use a tighter bound here.
      // We want to know if the full product has at least q trailing zeros.
      // We need to compute min(p2(mv), p5(mv) - e2) >= q
      // <=> p2(mv) >= q && p5(mv) - e2 >= q
      // <=> p2(mv) >= q (because -e2 >= q)
      vrIsTrailingZeros = multipleOfPowerOf2(mv, q);
#ifdef RYU_DEBUG
      printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif
    }
  }
#ifdef RYU_DEBUG
  printf("e10=%d\n", e10);
  printf("V+=%" PRIu64 "\nV =%" PRIu64 "\nV-=%" PRIu64 "\n", vp, vr, vm);
  printf("vm is trailing zeros=%s\n", vmIsTrailingZeros ? "true" : "false");
  printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif

  // Step 4: Find the shortest decimal representation in the interval of valid representations.
  int32_t removed = 0;
  uint8_t lastRemovedDigit = 0;
  uint64_t output;
  // On average, we remove ~2 digits.
  if (vmIsTrailingZeros || vrIsTrailingZeros) {
    // General case, which happens rarely (~0.7%).
    for (;;) {
      const uint64_t vpDiv10 = div10(vp);
      const uint64_t vmDiv10 = div10(vm);
      if (vpDiv10 <= vmDiv10) {
        break;
      }
      const uint32_t vmMod10 = ((uint32_t) vm) - 10 * ((uint32_t) vmDiv10);
      const uint64_t vrDiv10 = div10(vr);
      const uint32_t vrMod10 = ((uint32_t) vr) - 10 * ((uint32_t) vrDiv10);
      vmIsTrailingZeros &= vmMod10 == 0;
      vrIsTrailingZeros &= lastRemovedDigit == 0;
      lastRemovedDigit = (uint8_t) vrMod10;
      vr = vrDiv10;
      vp = vpDiv10;
      vm = vmDiv10;
      ++removed;
    }
#ifdef RYU_DEBUG
    printf("V+=%" PRIu64 "\nV =%" PRIu64 "\nV-=%" PRIu64 "\n", vp, vr, vm);
    printf("d-10=%s\n", vmIsTrailingZeros ? "true" : "false");
#endif
    if (vmIsTrailingZeros) {
      for (;;) {
        const uint64_t vmDiv10 = div10(vm);
        const uint32_t vmMod10 = ((uint32_t) vm) - 10 * ((uint32_t) vmDiv10);
        if (vmMod10 != 0) {
          break;
        }
        const uint64_t vpDiv10 = div10(vp);
        const uint64_t vrDiv10 = div10(vr);
        const uint32_t vrMod10 = ((uint32_t) vr) - 10 * ((uint32_t) vrDiv10);
        vrIsTrailingZeros &= lastRemovedDigit == 0;
        lastRemovedDigit = (uint8_t) vrMod10;
        vr = vrDiv10;
        vp = vpDiv10;
        vm = vmDiv10;
        ++removed;
      }
    }
#ifdef RYU_DEBUG
    printf("%" PRIu64 " %d\n", vr, lastRemovedDigit);
    printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif
    if (vrIsTrailingZeros && lastRemovedDigit == 5 && vr % 2 == 0) {
      // Round even if the exact number is .....50..0.
      lastRemovedDigit = 4;
    }
    // We need to take vr + 1 if vr is outside bounds or we need to round up.
    output = vr + ((vr == vm && (!acceptBounds || !vmIsTrailingZeros)) || lastRemovedDigit >= 5);
  } else {
    // Specialized for the common case (~99.3%). Percentages below are relative to this.
    bool roundUp = false;
    const uint64_t vpDiv100 = div100(vp);
    const uint64_t vmDiv100 = div100(vm);
    if (vpDiv100 > vmDiv100) { // Optimization: remove two digits at a time (~86.2%).
      const uint64_t vrDiv100 = div100(vr);
      const uint32_t vrMod100 = ((uint32_t) vr) - 100 * ((uint32_t) vrDiv100);
      roundUp = vrMod100 >= 50;
      vr = vrDiv100;
      vp = vpDiv100;
      vm = vmDiv100;
      removed += 2;
    }
    // Loop iterations below (approximately), without optimization above:
    // 0: 0.03%, 1: 13.8%, 2: 70.6%, 3: 14.0%, 4: 1.40%, 5: 0.14%, 6+: 0.02%
    // Loop iterations below (approximately), with optimization above:
    // 0: 70.6%, 1: 27.8%, 2: 1.40%, 3: 0.14%, 4+: 0.02%
    for (;;) {
      const uint64_t vpDiv10 = div10(vp);
      const uint64_t vmDiv10 = div10(vm);
      if (vpDiv10 <= vmDiv10) {
        break;
      }
      const uint64_t vrDiv10 = div10(vr);
      const uint32_t vrMod10 = ((uint32_t) vr) - 10 * ((uint32_t) vrDiv10);
      roundUp = vrMod10 >= 5;
      vr = vrDiv10;
      vp = vpDiv10;
      vm = vmDiv10;
      ++removed;
    }
#ifdef RYU_DEBUG
    printf("%" PRIu64 " roundUp=%s\n", vr, roundUp ? "true" : "false");
    printf("vr is trailing zeros=%s\n", vrIsTrailingZeros ? "true" : "false");
#endif
    // We need to take vr + 1 if vr is outside bounds or we need to round up.
    output = vr + (vr == vm || roundUp);
  }
  const int32_t exp = e10 + removed;

#ifdef RYU_DEBUG
  printf("V+=%" PRIu64 "\nV =%" PRIu64 "\nV-=%" PRIu64 "\n", vp, vr, vm);
  printf("O=%" PRIu64 "\n", output);
  printf("EXP=%d\n", exp);
#endif

  floating_decimal_64 fd;
  fd.exponent = exp;
  fd.mantissa = output;
  return fd;
}

static inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result to_chars(char* const first, char* const last, const floating_decimal_64 v,
  chars_format fmt, const double f) {
  // Step 5: Print the decimal representation.
  uint64_t output = v.mantissa;
  int32_t ryu_exponent = v.exponent;
  const uint32_t olength = decimalLength17(output);
  int32_t scientific_exponent = ryu_exponent + static_cast<int32_t>(olength) - 1;

#ifdef RYU_DEBUG
  printf("DIGITS=%" PRIu64 "\n", v.mantissa);
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
      lower = -static_cast<int32_t>(olength + 3);
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

    const int32_t whole_digits = static_cast<int32_t>(olength) + ryu_exponent;

    uint32_t total_fixed_length;
    if (ryu_exponent >= 0) { // cases "172900" and "1729"
      total_fixed_length = static_cast<uint32_t>(whole_digits);
      if (output == 1) {
        // Rounding can affect the number of digits.
        // For example, 1e23 is exactly "99999999999999991611392" which is 23 digits instead of 24.
        // We can use a lookup table to detect this and adjust the total length.
        const uint8_t adjustment[309] = {
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,0,0,
          1,1,0,0,1,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,0,1,1,1,
          1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,0,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,1,0,1,0,1,1,0,1,
          1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,0,0,1,0,0,0,1,
          0,1,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,1,1,1,0,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,0,0,1,
          1,1,0,1,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1,0,1,0,0,0,0,0,1,1,0,
          0,1,0,1,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,1,0,1,0 };
        total_fixed_length -= adjustment[ryu_exponent];
        // whole_digits doesn't need to be adjusted because these cases won't refer to it later.
      }
    } else if (whole_digits > 0) { // case "17.29"
      total_fixed_length = olength + 1;
    } else { // case "0.001729"
      total_fixed_length = static_cast<uint32_t>(2 - ryu_exponent);
    }

    if (last - first < static_cast<ptrdiff_t>(total_fixed_length)) {
      return { last, errc::value_too_large };
    }

    char* mid;
    if (ryu_exponent > 0) { // case "172900"
      bool can_use_ryu;

      if (ryu_exponent > 22) { // 10^22 is the largest power of 10 that's exactly representable as a double.
        can_use_ryu = false;
      } else {
        // Ryu generated X: v.mantissa * 10^ryu_exponent
        // v.mantissa == 2^trailing_zero_bits * (v.mantissa >> trailing_zero_bits)
        // 10^ryu_exponent == 2^ryu_exponent * 5^ryu_exponent

        // trailing_zero_bits is [0, 56] (aside: because 2^56 is the largest power of 2
        // with 17 decimal digits, which is double's round-trip limit.)
        // ryu_exponent is [1, 22].
        // Normalization adds [2, 52] (aside: at least 2 because the pre-normalized mantissa is at least 5).
        // This adds up to [3, 130], which is well below double's maximum binary exponent 1023.

        // Therefore, we just need to consider (v.mantissa >> trailing_zero_bits) * 5^ryu_exponent.

        // If that product would exceed 53 bits, then X can't be exactly represented as a double.
        // (That's not a problem for round-tripping, because X is close enough to the original double,
        // but X isn't mathematically equal to the original double.) This requires a high-precision fallback.

        // If the product is 53 bits or smaller, then X can be exactly represented as a double (and we don't
        // need to re-synthesize it; the original double must have been X, because Ryu wouldn't produce the
        // same output for two different doubles X and Y). This allows Ryu's output to be used (zero-filled).

        // (2^53 - 1) / 5^0 (for indexing), (2^53 - 1) / 5^1, ..., (2^53 - 1) / 5^22
        const uint64_t max_shifted_mantissa[23] = {
          9007199254740991u, 1801439850948198u, 360287970189639u, 72057594037927u, 14411518807585u,
          2882303761517u, 576460752303u, 115292150460u, 23058430092u, 4611686018u, 922337203u, 184467440u,
          36893488u, 7378697u, 1475739u, 295147u, 59029u, 11805u, 2361u, 472u, 94u, 18u, 3u };
        auto trailing_zero_bits = hamon::countr_zero(v.mantissa);	// v.mantissa is guaranteed nonzero
        const uint64_t shifted_mantissa = v.mantissa >> trailing_zero_bits;
        can_use_ryu = shifted_mantissa <= max_shifted_mantissa[ryu_exponent];
      }

      if (!can_use_ryu) {
        // Print the integer exactly.
        // Performance note: This will redundantly perform bounds checking.
        // Performance note: This will redundantly decompose the IEEE representation.
        return d2fixed_buffered_n(first, last, f, 0);
      }

      // can_use_ryu
      // Print the decimal digits, left-aligned within [first, first + total_fixed_length).
      mid = first + olength;
    } else { // cases "1729", "17.29", and "0.001729"
      // Print the decimal digits, right-aligned within [first, first + total_fixed_length).
      mid = first + total_fixed_length;
    }

    // We prefer 32-bit operations, even on 64-bit platforms.
    // We have at most 17 digits, and uint32_t can store 9 digits.
    // If output doesn't fit into uint32_t, we cut off 8 digits,
    // so the rest will fit into uint32_t.
    if ((output >> 32) != 0) {
      // Expensive 64-bit division.
      const uint64_t q = div1e8(output);
      uint32_t output2 = static_cast<uint32_t>(output - 100000000 * q);
      output = q;

      const uint32_t c = output2 % 10000;
      output2 /= 10000;
      const uint32_t d = output2 % 10000;
      const uint32_t c0 = (c % 100) << 1;
      const uint32_t c1 = (c / 100) << 1;
      const uint32_t d0 = (d % 100) << 1;
      const uint32_t d1 = (d / 100) << 1;

      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c0, 2);
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c1, 2);
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + d0, 2);
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + d1, 2);
    }
    uint32_t output2 = static_cast<uint32_t>(output);
    while (output2 >= 10000) {
#ifdef __clang__ // TRANSITION, LLVM-38217
      const uint32_t c = output2 - 10000 * (output2 / 10000);
#else
      const uint32_t c = output2 % 10000;
#endif
      output2 /= 10000;
      const uint32_t c0 = (c % 100) << 1;
      const uint32_t c1 = (c / 100) << 1;
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c0, 2);
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c1, 2);
    }
    if (output2 >= 100) {
      const uint32_t c = (output2 % 100) << 1;
      output2 /= 100;
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c, 2);
    }
    if (output2 >= 10) {
      const uint32_t c = output2 << 1;
      hamon::ct::memcpy(mid -= 2, DIGIT_TABLE + c, 2);
    } else {
      *--mid = static_cast<char>('0' + output2);
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

  const uint32_t total_scientific_length = olength + (olength > 1) // digits + possible decimal point
    + (-100 < scientific_exponent && scientific_exponent < 100 ? 4 : 5); // + scientific exponent
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
  // We prefer 32-bit operations, even on 64-bit platforms.
  // We have at most 17 digits, and uint32_t can store 9 digits.
  // If output doesn't fit into uint32_t, we cut off 8 digits,
  // so the rest will fit into uint32_t.
  if ((output >> 32) != 0) {
    // Expensive 64-bit division.
    const uint64_t q = div1e8(output);
    uint32_t output2 = ((uint32_t) output) - 100000000 * ((uint32_t) q);
    output = q;

    const uint32_t c = output2 % 10000;
    output2 /= 10000;
    const uint32_t d = output2 % 10000;
    const uint32_t c0 = (c % 100) << 1;
    const uint32_t c1 = (c / 100) << 1;
    const uint32_t d0 = (d % 100) << 1;
    const uint32_t d1 = (d / 100) << 1;
    hamon::ct::memcpy(result + olength - i - 1, DIGIT_TABLE + c0, 2);
    hamon::ct::memcpy(result + olength - i - 3, DIGIT_TABLE + c1, 2);
    hamon::ct::memcpy(result + olength - i - 5, DIGIT_TABLE + d0, 2);
    hamon::ct::memcpy(result + olength - i - 7, DIGIT_TABLE + d1, 2);
    i += 8;
  }
  uint32_t output2 = (uint32_t) output;
  while (output2 >= 10000) {
#ifdef __clang__ // https://bugs.llvm.org/show_bug.cgi?id=38217
    const uint32_t c = output2 - 10000 * (output2 / 10000);
#else
    const uint32_t c = output2 % 10000;
#endif
    output2 /= 10000;
    const uint32_t c0 = (c % 100) << 1;
    const uint32_t c1 = (c / 100) << 1;
    hamon::ct::memcpy(result + olength - i - 1, DIGIT_TABLE + c0, 2);
    hamon::ct::memcpy(result + olength - i - 3, DIGIT_TABLE + c1, 2);
    i += 4;
  }
  if (output2 >= 100) {
    const uint32_t c = (output2 % 100) << 1;
    output2 /= 100;
    hamon::ct::memcpy(result + olength - i - 1, DIGIT_TABLE + c, 2);
    i += 2;
  }
  if (output2 >= 10) {
    const uint32_t c = output2 << 1;
    // We can't use memcpy here: the decimal dot goes between these two digits.
    result[2] = DIGIT_TABLE[c + 1];
    result[0] = DIGIT_TABLE[c];
  } else {
    result[0] = static_cast<char>('0' + output2);
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

  if (scientific_exponent >= 100) {
    const int32_t c = scientific_exponent % 10;
    hamon::ct::memcpy(result + index, DIGIT_TABLE + 2 * (scientific_exponent / 10), 2);
    result[index + 2] = static_cast<char>('0' + c);
    index += 3;
  } else {
    hamon::ct::memcpy(result + index, DIGIT_TABLE + 2 * scientific_exponent, 2);
    index += 2;
  }

  return { first + total_scientific_length, errc{} };
}

static inline HAMON_CXX20_CONSTEXPR bool d2d_small_int(const uint64_t ieeeMantissa, const uint32_t ieeeExponent,
  floating_decimal_64* const v) {
  const uint64_t m2 = (1ull << DOUBLE_MANTISSA_BITS) | ieeeMantissa;
  const int32_t e2 = (int32_t) ieeeExponent - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS;

  if (e2 > 0) {
    // f = m2 * 2^e2 >= 2^53 is an integer.
    // Ignore this case for now.
    return false;
  }

  if (e2 < -52) {
    // f < 1.
    return false;
  }

  // Since 2^52 <= m2 < 2^53 and 0 <= -e2 <= 52: 1 <= f = m2 / 2^-e2 < 2^53.
  // Test if the lower -e2 bits of the significand are 0, i.e. whether the fraction is 0.
  const uint64_t mask = (1ull << -e2) - 1;
  const uint64_t fraction = m2 & mask;
  if (fraction != 0) {
    return false;
  }

  // f is an integer in the range [1, 2^53).
  // Note: mantissa might contain trailing (decimal) 0's.
  // Note: since 2^53 < 10^16, there is no need to adjust decimalLength17().
  v->mantissa = m2 >> -e2;
  v->exponent = 0;
  return true;
}

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result d2s_buffered_n(char* const first, char* const last, const double f,
  const chars_format fmt) {

  // Step 1: Decode the floating-point number, and unify normalized and subnormal cases.
  const uint64_t bits = double_to_bits(f);

#ifdef RYU_DEBUG
  printf("IN=");
  for (int32_t bit = 63; bit >= 0; --bit) {
    printf("%d", (int) ((bits >> bit) & 1));
  }
  printf("\n");
#endif

  // Case distinction; exit early for the easy cases.
  if (bits == 0) {
    if (fmt == chars_format::scientific) {
      if (last - first < 5) {
        return { last, errc::value_too_large };
      }

      hamon::ct::memcpy(first, "0e+00", 5);

      return { first + 5, errc{} };
    }

    // Print "0" for chars_format::fixed, chars_format::general, and chars_format{}.
    if (first == last) {
      return { last, errc::value_too_large };
    }

    *first = '0';

    return { first + 1, errc{} };
  }

  // Decode bits into sign, mantissa, and exponent.
  const bool ieeeSign = ((bits >> (DOUBLE_MANTISSA_BITS + DOUBLE_EXPONENT_BITS)) & 1) != 0;
  const uint64_t ieeeMantissa = bits & ((1ull << DOUBLE_MANTISSA_BITS) - 1);
  const uint32_t ieeeExponent = (uint32_t) ((bits >> DOUBLE_MANTISSA_BITS) & ((1u << DOUBLE_EXPONENT_BITS) - 1));
  // Case distinction; exit early for the easy cases.
  if (ieeeExponent == ((1u << DOUBLE_EXPONENT_BITS) - 1u) || (ieeeExponent == 0 && ieeeMantissa == 0)) {
    return copy_special_str(first, last, ieeeSign, ieeeExponent, ieeeMantissa);
  }

  if (fmt == chars_format::fixed) {
    // const uint64_t mantissa2 = ieeeMantissa | (1ull << DOUBLE_MANTISSA_BITS); // restore implicit bit
    const int32_t exponent2 = static_cast<int32_t>(ieeeExponent)
      - DOUBLE_BIAS - DOUBLE_MANTISSA_BITS; // bias and normalization

    // Normal values are equal to mantissa2 * 2^exponent2.
    // (Subnormals are different, but they'll be rejected by the exponent2 test here, so they can be ignored.)

    // For nonzero integers, exponent2 >= -52. (The minimum value occurs when mantissa2 * 2^exponent2 is 1.
    // In that case, mantissa2 is the implicit 1 bit followed by 52 zeros, so exponent2 is -52 to shift away
    // the zeros.) The dense range of exactly representable integers has negative or zero exponents
    // (as positive exponents make the range non-dense). For that dense range, Ryu will always be used:
    // every digit is necessary to uniquely identify the value, so Ryu must print them all.

    // Positive exponents are the non-dense range of exactly representable integers. This contains all of the values
    // for which Ryu can't be used (and a few Ryu-friendly values). We can save time by detecting positive
    // exponents here and skipping Ryu. Calling d2fixed_buffered_n() with precision 0 is valid for all integers
    // (so it's okay if we call it with a Ryu-friendly value).
    if (exponent2 > 0) {
      return d2fixed_buffered_n(first, last, f, 0);
    }
  }

  floating_decimal_64 v;
  const bool isSmallInt = d2d_small_int(ieeeMantissa, ieeeExponent, &v);
  if (isSmallInt) {
    // For small integers in the range [1, 2^53), v.mantissa might contain trailing (decimal) zeros.
    // For scientific notation we need to move these zeros into the exponent.
    // (This is not needed for fixed-point notation, so it might be beneficial to trim
    // trailing zeros in to_chars only if needed - once fixed-point notation output is implemented.)
    for (;;) {
      const uint64_t q = div10(v.mantissa);
      const uint32_t r = ((uint32_t) v.mantissa) - 10 * ((uint32_t) q);
      if (r != 0) {
        break;
      }
      v.mantissa = q;
      ++v.exponent;
    }
  } else {
    v = d2d(ieeeMantissa, ieeeExponent);
  }

  return to_chars(first, last, v, fmt, f);
}

}	// namespace ryu
}	// namespace detail
}	// namespace hamon

#endif // RYU_D2S_HPP
