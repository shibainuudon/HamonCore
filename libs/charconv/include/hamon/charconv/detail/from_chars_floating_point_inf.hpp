/**
 *	@file	from_chars_floating_point_inf.hpp
 *
 *	@brief	from_chars_floating_point_inf の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_INF_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_INF_HPP

#include <hamon/charconv/detail/starts_with_case_insensitive.hpp>
#include <hamon/charconv/detail/make_floating_point_infinity.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point_inf(const char* first, const char* last, F& value, bool negative) HAMON_NOEXCEPT
{
	// pre: first points at 'i' (case-insensitively)

	if (!starts_with_case_insensitive(first + 1, last, "nf"))
	{
		// definitely invalid
		return { first, hamon::errc::invalid_argument };
	}

	// definitely inf
	first += 3;

	if (starts_with_case_insensitive(first, last, "inity"))
	{
		// definitely infinity
		first += 5;
	}

	value = make_floating_point_infinity<F>(negative);

	return { first, hamon::errc{} };
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_INF_HPP
