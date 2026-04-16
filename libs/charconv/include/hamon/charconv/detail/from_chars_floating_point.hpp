/**
 *	@file	from_chars_floating_point.hpp
 *
 *	@brief	from_chars_floating_point の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP

#include <hamon/charconv/chars_format.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_inf.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_nan.hpp>
#include <hamon/charconv/detail/from_chars_floating_point_ordinary.hpp>
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
	if (first == last)
	{
		return {first, hamon::errc::invalid_argument};
	}

	const char* ptr = first;
	bool const negative = (*ptr == '-');
	if (negative)
	{
		++ptr;

		if (ptr == last || *ptr == '-')
		{
			return {first, hamon::errc::invalid_argument};
		}
	}

	hamon::from_chars_result result;
	switch (hamon::tolower(*ptr))
	{
	case 'i':
		result = hamon::detail::from_chars_floating_point_inf(ptr, last, value, negative);
		break;
	case 'n':
		result = hamon::detail::from_chars_floating_point_nan(ptr, last, value, negative);
		break;
	default:
		result = hamon::detail::from_chars_floating_point_ordinary(ptr, last, value, fmt, negative);
		break;
	}

	if (result.ec == hamon::errc::invalid_argument)
	{
		result.ptr = first;
	}

	return result;
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

	if (ret)
	{
		value = dbl;
	}

	return ret;
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_HPP
