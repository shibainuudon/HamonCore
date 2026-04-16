/**
 *	@file	right_shift_with_rounding.hpp
 *
 *	@brief	right_shift_with_rounding の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_RIGHT_SHIFT_WITH_ROUNDING_HPP
#define HAMON_CHARCONV_DETAIL_RIGHT_SHIFT_WITH_ROUNDING_HPP

#include <hamon/cstdint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// Computes value / 2^shift, then rounds the result according to round_to_nearest.
// By the time we call this function, we will already have discarded most digits.
// The caller must pass true for has_zero_tail if all discarded bits were zeroes.
HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR hamon::uint64_t
right_shift_with_rounding(hamon::uint64_t value, hamon::uint32_t shift, bool has_zero_tail) HAMON_NOEXCEPT
{
	hamon::uint32_t const total_number_of_bits = 64;
	if (shift >= total_number_of_bits)
	{
		if (shift == total_number_of_bits)
		{
			hamon::uint64_t const extra_bits_mask = (1ULL << (total_number_of_bits - 1)) - 1;
			hamon::uint64_t const round_bit_mask  = (1ULL << (total_number_of_bits - 1));

			bool const round_bit = (value & round_bit_mask) != 0;
			bool const tail_bits = !has_zero_tail || (value & extra_bits_mask) != 0;

			// We round up the answer to 1 if the answer is greater than 0.5. Otherwise, we round down the answer to 0
			// if either [1] the answer is less than 0.5 or [2] the answer is exactly 0.5.
			return static_cast<hamon::uint64_t>(round_bit && tail_bits);
		}
		else
		{
			// If we'd need to shift 65 or more bits, the answer is less than 0.5 and is always rounded to zero:
			return 0;
		}
	}

	// Reference implementation with suboptimal codegen:
	// const hamon::uint64_t extra_bits_mask = (1ULL << (shift - 1)) - 1;
	// const hamon::uint64_t round_bit_mask  = (1ULL << (shift - 1));
	// const hamon::uint64_t _Lsb_bit_mask    = 1ULL << shift;

	// const bool lsb_bit   = (value & _Lsb_bit_mask) != 0;
	// const bool round_bit = (value & round_bit_mask) != 0;
	// const bool tail_bits = !has_zero_tail || (value & extra_bits_mask) != 0;

	// return (value >> shift) + _Should_round_up(lsb_bit, round_bit, tail_bits);

	// Example for optimized implementation: Let shift be 8.
	// Bit index: ...[8]76543210
	//    value: ...[L]RTTTTTTT
	// By focusing on the bit at index shift, we can avoid unnecessary branching and shifting.

	// Bit index: ...[8]76543210
	//  lsb_bit: ...[L]RTTTTTTT
	hamon::uint64_t const lsb_bit = value;

	//  Bit index: ...9[8]76543210
	// round_bit: ...L[R]TTTTTTT0
	hamon::uint64_t const round_bit = value << 1;

	// We can detect (without branching) whether any of the trailing bits are set.
	// Due to should_round below, this computation will be used if and only if R is 1, so we can assume that here.
	//      Bit index: ...9[8]76543210
	//     round_bit: ...L[1]TTTTTTT0
	// has_tail_bits: ....[H]........

	// If all of the trailing bits T are 0, and has_zero_tail is true,
	// then `round_bit - static_cast<hamon::uint64_t>(has_zero_tail)` will produce 0 for H (due to R being 1).
	// If any of the trailing bits T are 1, or has_zero_tail is false,
	// then `round_bit - static_cast<hamon::uint64_t>(has_zero_tail)` will produce 1 for H (due to R being 1).
	hamon::uint64_t const has_tail_bits = round_bit - static_cast<hamon::uint64_t>(has_zero_tail);

	// Finally, we can use _Should_round_up() logic with bitwise-AND and bitwise-OR,
	// selecting just the bit at index shift.
	hamon::uint64_t const should_round = ((round_bit & (has_tail_bits | lsb_bit)) >> shift) & hamon::uint64_t{1};

	// This rounding technique is dedicated to the memory of Peppermint. =^..^=
	return (value >> shift) + should_round;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_RIGHT_SHIFT_WITH_ROUNDING_HPP
