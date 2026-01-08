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
HAMON_NODISCARD inline hamon::from_chars_result
from_chars_floating_point_inf(const char* first, const char* last, F& value, bool negative, const char* ptr) noexcept
{
	// pre: ptr points at 'i' (case-insensitively)

	if (!starts_with_case_insensitive(ptr + 1, last, "nf"))
	{
		// definitely invalid
		return { first, hamon::errc::invalid_argument };
	}

	// definitely inf
	ptr += 3;

	if (starts_with_case_insensitive(ptr, last, "inity"))
	{
		// definitely infinity
		ptr += 5;
	}

	value = make_floating_point_infinity<F>(negative);

	return { ptr, hamon::errc{} };
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_INF_HPP
