/**
 *	@file	to_chars_floating_point_precision_hex.hpp
 *
 *	@brief	to_chars_floating_point_precision_hex の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_HEX_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_HEX_HPP

#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/detail/to_chars_integer.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

namespace detail
{

template <typename Floating>
hamon::to_chars_result
to_chars_floating_point_precision_hex(char* first, char* const last, const Floating value, int precision) noexcept
{
	// * Determine the effective precision.
	// * Later, we'll decrement precision when printing each hexit after the decimal point.

	// The hexits after the decimal point correspond to the explicitly stored fraction bits.
	// float explicitly stores 23 fraction bits. 23 / 4 == 5.75, which is 6 hexits.
	// double explicitly stores 52 fraction bits. 52 / 4 == 13, which is 13 hexits.
	constexpr int full_precision = hamon::is_same<Floating, float>::value ? 6 : 13;
	constexpr int adjusted_explicit_bits = full_precision * 4;

	if (precision < 0)
	{
		// C11 7.21.6.1 "The fprintf function"/5: "A negative precision argument is taken as if the precision were
		// omitted." /8: "if the precision is missing and FLT_RADIX is a power of 2, then the precision is sufficient
		// for an exact representation of the value"
		precision = full_precision;
	}

	using Binary = hamon::ieee754::binary<Floating>;
	using uint_type = typename Binary::uint_type;

	Binary const bits(value);

	// 負の値、NaN、Infinityはこの関数より前で処理されていなければならない
	HAMON_ASSERT(bits.sign() == 0u);
	HAMON_ASSERT(bits.is_finite());

	// * Prepare the adjusted_fraction. This is aligned to hexit boundaries,
	// * with the implicit bit restored (0 for zero values and subnormal values, 1 for normal values).
	// * Also calculate the unbiased_exponent. This unifies the processing of zero, subnormal, and normal values.
	auto const adjusted_fraction_bits = hamon::round_up(bits.fraction_bits, 4);
	auto adjusted_fraction = bits.unbiased_fraction() << (adjusted_fraction_bits - bits.fraction_bits);
	int32_t unbiased_exponent = bits.unbiased_exponent();

	// unbiased_exponent is within [-126, 127] for float, [-1022, 1023] for double.

	// * Decompose unbiased_exponent into sign_character and absolute_exponent.
	char sign_character;
	uint32_t absolute_exponent;

	if (unbiased_exponent < 0)
	{
		sign_character = '-';
		absolute_exponent = static_cast<uint32_t>(-unbiased_exponent);
	}
	else
	{
		sign_character = '+';
		absolute_exponent = static_cast<uint32_t>(unbiased_exponent);
	}

	// absolute_exponent is within [0, 127] for float, [0, 1023] for double.

	// * Perform a single bounds check.
	{
		int32_t exponent_length;

		if (absolute_exponent < 10)
		{
			exponent_length = 1;
		}
		else if (absolute_exponent < 100)
		{
			exponent_length = 2;
		}
		else if (absolute_exponent < 1000)
		{
			exponent_length = 3;
		}
		else
		{
			exponent_length = 4;
		}

		// precision might be enormous; avoid integer overflow by testing it separately.
		ptrdiff_t buffer_size = last - first;

		if (buffer_size < precision)
		{
			return { last, errc::value_too_large };
		}

		buffer_size -= precision;

		const int32_t length_excluding_precision = 1 // leading hexit
			+ static_cast<int32_t>(precision > 0) // possible decimal point
			// excluding `+ precision`, hexits after decimal point
			+ 2 // "p+" or "p-"
			+ exponent_length; // exponent

		if (buffer_size < length_excluding_precision)
		{
			return { last, errc::value_too_large };
		}
	}

	// * Perform rounding when we've been asked to omit hexits.
	if (precision < full_precision)
	{
		// precision is within [0, 5] for float, [0, 12] for double.

		// dropped_bits is within [4, 24] for float, [4, 52] for double.
		const int dropped_bits = (full_precision - precision) * 4;

		// Perform rounding by adding an appropriately-shifted bit.

		// This can propagate carries all the way into the leading hexit. Examples:
		// "0.ff9" rounded to a precision of 2 is "1.00".
		// "1.ff9" rounded to a precision of 2 is "2.00".

		// Note that the leading hexit participates in the rounding decision. Examples:
		// "0.8" rounded to a precision of 0 is "0".
		// "1.8" rounded to a precision of 0 is "2".

		// Reference implementation with suboptimal codegen:
		// bool _Should_round_up(bool lsb_bit, bool round_bit, bool has_tail_bits) {
		//    // If there are no insignificant set bits, the value is exactly-representable and should not be rounded.
		//    //
		//    // If there are insignificant set bits, we need to round according to round_to_nearest.
		//    // We need to handle two cases: we round up if either [1] the value is slightly greater
		//    // than the midpoint between two exactly-representable values or [2] the value is exactly the midpoint
		//    // between two exactly-representable values and the greater of the two is even (this is "round-to-even").
		//    return round_bit && (has_tail_bits || lsb_bit);
		//}
		// const bool lsb_bit       = (adjusted_fraction & (uint_type{1} << dropped_bits)) != 0;
		// const bool round_bit     = (adjusted_fraction & (uint_type{1} << (dropped_bits - 1))) != 0;
		// const bool has_tail_bits = (adjusted_fraction & ((uint_type{1} << (dropped_bits - 1)) - 1)) != 0;
		// const bool should_round = _Should_round_up(lsb_bit, round_bit, has_tail_bits);
		// adjusted_fraction += uint_type{should_round} << dropped_bits;

		// Example for optimized implementation: Let dropped_bits be 8.
		//          Bit index: ...[8]76543210
		// adjusted_fraction: ...[L]RTTTTTTT (not depicting known details, like hexit alignment)
		// By focusing on the bit at index dropped_bits, we can avoid unnecessary branching and shifting.

		// Bit index: ...[8]76543210
		//  lsb_bit: ...[L]RTTTTTTT
		const uint_type lsb_bit = adjusted_fraction;

		//  Bit index: ...9[8]76543210
		// round_bit: ...L[R]TTTTTTT0
		const uint_type round_bit = adjusted_fraction << 1;

		// We can detect (without branching) whether any of the trailing bits are set.
		// Due to should_round below, this computation will be used if and only if R is 1, so we can assume that here.
		//      Bit index: ...9[8]76543210
		//     round_bit: ...L[1]TTTTTTT0
		// has_tail_bits: ....[H]........

		// If all of the trailing bits T are 0, then `round_bit - 1` will produce 0 for H (due to R being 1).
		// If any of the trailing bits T are 1, then `round_bit - 1` will produce 1 for H (due to R being 1).
		const uint_type has_tail_bits = round_bit - 1;

		// Finally, we can use _Should_round_up() logic with bitwise-AND and bitwise-OR,
		// selecting just the bit at index dropped_bits. This is the appropriately-shifted bit that we want.
		const uint_type should_round = round_bit & (has_tail_bits | lsb_bit) & (uint_type{ 1 } << dropped_bits);

		// This rounding technique is dedicated to the memory of Peppermint. =^..^=
		adjusted_fraction += should_round;
	}

	// * Print the leading hexit, then mask it away.
	{
		const uint32_t nibble = static_cast<uint32_t>(adjusted_fraction >> adjusted_explicit_bits);
		HAMON_ASSERT(nibble < 3u);
		const char leading_hexit = static_cast<char>('0' + nibble);

		*first++ = leading_hexit;

		constexpr uint_type mask = (uint_type{ 1 } << adjusted_explicit_bits) - 1;
		adjusted_fraction &= mask;
	}

	// * Print the decimal point and trailing hexits.

	// C11 7.21.6.1 "The fprintf function"/8:
	// "if the precision is zero and the # flag is not specified, no decimal-point character appears."
	if (precision > 0)
	{
		*first++ = '.';

		int32_t number_of_bits_remaining = adjusted_explicit_bits; // 24 for float, 52 for double

		for (;;)
		{
			HAMON_ASSERT(number_of_bits_remaining >= 4);
			HAMON_ASSERT(number_of_bits_remaining % 4 == 0);
			number_of_bits_remaining -= 4;

			const uint32_t nibble = static_cast<uint32_t>(adjusted_fraction >> number_of_bits_remaining);
			HAMON_ASSERT(nibble < 16u);
			const char hexit = "0123456789abcdefghijklmnopqrstuvwxyz"[nibble];

			*first++ = hexit;

			// precision is the number of hexits that still need to be printed.
			--precision;
			if (precision == 0)
			{
				break; // We're completely done with this phase.
			}
			// Otherwise, we need to keep printing hexits.

			if (number_of_bits_remaining == 0)
			{
				// We've finished printing adjusted_fraction, so all remaining hexits are '0'.
				std::memset(first, '0', static_cast<size_t>(precision));
				first += precision;
				break;
			}

			// Mask away the hexit that we just printed, then keep looping.
			// (We skip this when breaking out of the loop above, because adjusted_fraction isn't used later.)
			const uint_type mask = (uint_type{ 1 } << number_of_bits_remaining) - 1;
			adjusted_fraction &= mask;
		}
	}

	// * Print the exponent.

	// C11 7.21.6.1 "The fprintf function"/8: "The exponent always contains at least one digit, and only as many more
	// digits as necessary to represent the decimal exponent of 2."

	// Performance note: We should take advantage of the known ranges of possible exponents.

	*first++ = 'p';
	*first++ = sign_character;

	// We've already printed '-' if necessary, so uint32_t absolute_exponent avoids testing that again.
	return hamon::detail::to_chars_unsigned_integer(first, last, absolute_exponent, 10);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_HEX_HPP
