/**
 *	@file	from_chars_floating_point.hpp
 *
 *	@brief	from_chars_floating_point の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_dec.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_hex.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_inf.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_nan.hpp>
#include <hamon/cctype/tolower.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point_impl(const char* first, const char* last, F& value, hamon::chars_format fmt) HAMON_NOEXCEPT
{
	if (first == last) /*[[unlikely]]*/
	{
		return {first, hamon::errc::invalid_argument};
	}

	const char* ptr = first;
	bool const negative = (*ptr == '-');
	if (negative)
	{
		++ptr;

		if (ptr == last || *ptr == '-') /*[[unlikely]]*/
		{
			return {first, hamon::errc::invalid_argument};
		}
	}

	switch (hamon::tolower(*ptr))
	{
	case 'i':
		return hamon::detail::from_chars_floating_point_inf(first, last, value, negative, ptr);
	case 'n':
		return hamon::detail::from_chars_floating_point_nan(first, last, value, negative, ptr);
	}

	if (fmt == hamon::chars_format::hex)
	{
		return hamon::detail::from_chars_floating_point_hex(first, last, value, negative, ptr);
	}
	else
	{
		return hamon::detail::from_chars_floating_point_dec(first, last, value, fmt, negative, ptr);
	}
}

inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point(const char* first, const char* last, float& value, hamon::chars_format fmt) HAMON_NOEXCEPT
{
	return hamon::detail::from_chars_floating_point_impl(first, last, value, fmt);
}

inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point(const char* first, const char* last, double& value, hamon::chars_format fmt) HAMON_NOEXCEPT
{
	return hamon::detail::from_chars_floating_point_impl(first, last, value, fmt);
}

inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point(const char* first, const char* last, long double& value, hamon::chars_format fmt) HAMON_NOEXCEPT
{
	double dbl{};
	auto const ret = hamon::detail::from_chars_floating_point_impl(first, last, dbl, fmt);

	if (ret.ec == hamon::errc{})
	{
		value = dbl;
	}

	return ret;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP
