/**
 *	@file	to_chars_floating_point_hex_shortest.hpp
 *
 *	@brief	to_chars_floating_point_hex_shortest の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_HEX_SHORTEST_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_HEX_SHORTEST_HPP

#include <hamon/charconv/detail/to_chars_integer.hpp>
#include <hamon/cmath/round_up.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_hex_fraction(char* first, char* last, T value, int bits)
{
	HAMON_ASSERT(bits % 4 == 0);

	for (;;)
	{
		HAMON_ASSERT(bits >= 4);
		bits -= 4;

		const auto nibble = static_cast<hamon::uint32_t>(value >> bits);
		HAMON_ASSERT(nibble < 16u);
		const char hexit = "0123456789abcdefghijklmnopqrstuvwxyz"[nibble];

		if (first == last)
		{
			return { last, hamon::errc::value_too_large };
		}

		*first++ = hexit;

		const T mask = (T{ 1 } << bits) - 1;
		value &= mask;

		if (value == 0)
		{
			break;
		}
	}

	return { first, hamon::errc{} };
}

template <typename Floating>
inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_floating_point_hex_shortest(char* first, char* last, Floating value) noexcept
{
	// This prints "1.728p+0" instead of "2.e5p-1".
	// This prints "0.000002p-126" instead of "1p-149" for float.
	// This prints "0.0000000000001p-1022" instead of "1p-1074" for double.
	// This prioritizes being consistent with printf's de facto behavior (and hex-precision's behavior)
	// over minimizing the number of characters printed.

	hamon::ieee754::binary<Floating> const bits(value);

	// 負の値、ゼロ、NaN、Infinityはこの関数より前で処理されていなければならない
	HAMON_ASSERT(bits.sign() == 0u);
	HAMON_ASSERT(!bits.is_zero());
	HAMON_ASSERT(bits.is_finite());

	// Performance note: Consider avoiding per-character bounds checking when there's plenty of space.

	if (first == last)
	{
		return { last, hamon::errc::value_too_large };
	}

	char const leadinghexit = bits.is_subnormal() ? '0' : '1'; // implicit bit
	*first++ = leadinghexit;

	auto const ieee_fraction = bits.fraction();
	if (ieee_fraction == 0)
	{
		// The fraction bits are all 0. Trim them away, including the decimal point.
	}
	else
	{
		if (first == last)
		{
			return { last, hamon::errc::value_too_large };
		}

		*first++ = '.';

		auto const adjusted_fraction_bits = hamon::round_up(bits.fraction_bits, 4);
		auto const adjusted_fraction = ieee_fraction << (adjusted_fraction_bits - bits.fraction_bits);

		auto ret = hamon::detail::to_chars_hex_fraction(first, last, adjusted_fraction, adjusted_fraction_bits);
		if (ret.ec != hamon::errc{})
		{
			return ret;
		}
		first = ret.ptr;
	}

	// C11 7.21.6.1 "The fprintf function"/8: "The exponent always contains at least one digit, and only as many more
	// digits as necessary to represent the decimal exponent of 2."

	// Performance note: We should take advantage of the known ranges of possible exponents.

	// float: unbiased_exponent is within [-126, 127].
	// double: unbiased_exponent is within [-1022, 1023].

	if (last - first < 2)
	{
		return { last, hamon::errc::value_too_large };
	}

	*first++ = 'p';

	hamon::int32_t unbiased_exponent = bits.unbiased_exponent();
	if (unbiased_exponent < 0)
	{
		*first++ = '-';
		unbiased_exponent = -unbiased_exponent;
	}
	else
	{
		*first++ = '+';
	}

	// We've already printed '-' if necessary, so static_cast<uint32_t> avoids testing that again.
	return hamon::detail::to_chars_unsigned_integer(first, last, static_cast<hamon::uint32_t>(unbiased_exponent), 10);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_HEX_SHORTEST_HPP
