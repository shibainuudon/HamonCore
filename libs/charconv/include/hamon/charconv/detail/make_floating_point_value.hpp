/**
 *	@file	make_floating_point_value.hpp
 *
 *	@brief	make_floating_point_value の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_HPP
#define HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_HPP

#include <hamon/charconv/detail/right_shift_with_rounding.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/ieee754.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

#include <hamon/bit/bit_cast.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::errc
make_floating_point_value(hamon::uint64_t mantissa, hamon::int32_t exponent, bool negative, bool has_zero_tail, F& value) HAMON_NOEXCEPT
{
	using Binary = hamon::ieee754::binary<F>;
//	using FractionType = typename Binary::fraction_type;
	using UIntType = typename Binary::uint_type;

	int shift = (Binary::fraction_bits + 1) - hamon::bit_width(mantissa);
	exponent += Binary::fraction_bits;
	exponent -= shift;

	if (exponent > Binary::exponent_max)
	{
		return hamon::errc::result_out_of_range;
	}

	constexpr UIntType fraction_max = (1ULL << (Binary::fraction_bits + 1)) - 1;

	if (exponent < Binary::exponent_min)
	{
		shift += exponent - Binary::exponent_min;
		exponent = Binary::exponent_min;
		if (shift < 0)
		{
			mantissa = right_shift_with_rounding(mantissa, static_cast<hamon::uint32_t>(-shift), has_zero_tail);
			if (mantissa == 0)
			{
				return hamon::errc::result_out_of_range;
			}
		}
		else
		{
			mantissa <<= shift;
		}
	}
	else
	{
		if (shift < 0)
		{
			mantissa = right_shift_with_rounding(mantissa, static_cast<hamon::uint32_t>(-shift), has_zero_tail);
			if (mantissa > fraction_max && exponent == Binary::exponent_max)
			{
				return hamon::errc::result_out_of_range;
			}
		}
		else
		{
			mantissa <<= shift;
		}
	}

	UIntType sign_component = UIntType(negative ? 1 : 0) << Binary::sign_shift;
	UIntType exponent_component = UIntType(exponent + Binary::exponent_bias - 1) << Binary::exponent_shift;
	UIntType mantissa_component = static_cast<UIntType>(mantissa);

	value = hamon::bit_cast<F>(sign_component | (exponent_component + mantissa_component));
	return hamon::errc{};
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_MAKE_FLOATING_POINT_VALUE_HPP
