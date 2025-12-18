/**
 *	@file	to_chars_floating_point.hpp
 *
 *	@brief	to_chars_floating_point の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_HPP
#define HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/to_chars_result.hpp>
#include <hamon/charconv/detail/ryu/f2s.hpp>
#include <hamon/charconv/detail/ryu/d2s.hpp>
#include <hamon/charconv/detail/to_chars_floating_point_hex_shortest.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstring/memcpy.hpp>
#include <hamon/cstring/strlen.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/system_error/errc.hpp>

namespace hamon
{

namespace detail
{

inline hamon::to_chars_result
to_chars_floating_point_ryu(char* first, char* last, float value, hamon::chars_format fmt)
{
	return ryu::f2s_buffered_n(first, last, value, fmt);
}

inline hamon::to_chars_result
to_chars_floating_point_ryu(char* first, char* last, double value, hamon::chars_format fmt)
{
	return ryu::d2s_buffered_n(first, last, value, fmt);
}

template <typename T>
inline hamon::to_chars_result
to_chars_floating_point_impl(char* first, char* last, T value, hamon::chars_format fmt)
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
			if (fmt == hamon::chars_format::scientific)
			{
				return "0e+00";
			}
			if (fmt == hamon::chars_format::hex)
			{
				return "0p+0";
			}
			return "0";
		}();
		auto len = hamon::strlen(str);
		if (last - first < static_cast<hamon::ptrdiff_t>(len))
		{
			return {last, hamon::errc::value_too_large};
		}

		hamon::memcpy(first, str, len);

		return {first + len, errc{}};
	}

	if (fmt == hamon::chars_format::hex)
	{
		return to_chars_floating_point_hex_shortest(first, last, value);
	}

	return to_chars_floating_point_ryu(first, last, value, fmt);
}

inline hamon::to_chars_result
to_chars_floating_point(char* first, char* last, float value, hamon::chars_format fmt)
{
	return to_chars_floating_point_impl(first, last, value, fmt);
}

inline hamon::to_chars_result
to_chars_floating_point(char* first, char* last, double value, hamon::chars_format fmt)
{
	return to_chars_floating_point_impl(first, last, value, fmt);
}

inline hamon::to_chars_result
to_chars_floating_point(char* first, char* last, long double value, hamon::chars_format fmt)
{
	return to_chars_floating_point_impl(first, last, static_cast<double>(value), fmt);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_TO_CHARS_FLOATING_POINT_HPP
