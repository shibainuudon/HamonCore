/**
 *	@file	to_chars_floating_point_precision.hpp
 *
 *	@brief	to_chars_floating_point_precision の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/detail/ryu/f2s.hpp>
#include <hamon/charconv/detail/ryu/d2s.hpp>
#include <hamon/charconv/detail/ryu/d2fixed.hpp>
#include <hamon/charconv/detail/to_chars_floating_point_precision_hex.hpp>
#include <hamon/charconv/detail/to_chars_floating_point_precision_scientific.hpp>
#include <hamon/charconv/detail/to_chars_floating_point_precision_fixed.hpp>
#include <hamon/charconv/detail/to_chars_floating_point_precision_general.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstring/memcpy.hpp>
#include <hamon/cstring/strlen.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/system_error/errc.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_floating_point_precision_impl(char* first, char* last, T value, hamon::chars_format fmt, int precision)
{
	hamon::ieee754::binary<T> const bin(value);
	if (bin.sign() != 0)
	{
		if (first == last)
		{
			return {last, hamon::errc::value_too_large};
		}
		*first++ = '-';
		value = -value;
	}

	if (bin.is_zero() || !bin.is_finite())
	{
		const char* str = [&]()
		{
			if (bin.is_infinity())
			{
				return "inf";
			}
			if (bin.is_quiet_nan())
			{
				return "nan";
			}
			if (bin.is_signaling_nan())
			{
				return "nan(snan)";
			}
			if (fmt == hamon::chars_format::general)
			{
				return "0";
			}
			return static_cast<const char*>(nullptr);
		}();

		if (str != nullptr)
		{
			auto len = hamon::strlen(str);
			if (last - first < static_cast<hamon::ptrdiff_t>(len))
			{
				return {last, hamon::errc::value_too_large};
			}

			hamon::ct::memcpy(first, str, len);

			return {first + len, hamon::errc{}};
		}
	}

	switch (fmt)
	{
	case hamon::chars_format::scientific:
		return to_chars_floating_point_precision_scientific(first, last, value, precision);
	case hamon::chars_format::fixed:
		return to_chars_floating_point_precision_fixed(first, last, value, precision);
	case hamon::chars_format::hex:
		return to_chars_floating_point_precision_hex(first, last, value, precision);
	case hamon::chars_format::general:
	default:
		return to_chars_floating_point_precision_general(first, last, value, precision);
	}
}

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_floating_point_precision(char* first, char* last, float value, hamon::chars_format fmt, int precision)
{
	return to_chars_floating_point_precision_impl(first, last, value, fmt, precision);
}

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_floating_point_precision(char* first, char* last, double value, hamon::chars_format fmt, int precision)
{
	return to_chars_floating_point_precision_impl(first, last, value, fmt, precision);
}

inline HAMON_CXX20_CONSTEXPR hamon::to_chars_result
to_chars_floating_point_precision(char* first, char* last, long double value, hamon::chars_format fmt, int precision)
{
	return to_chars_floating_point_precision_impl(first, last, static_cast<double>(value), fmt, precision);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_PRECISION_HPP
