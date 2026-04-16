/**
 *	@file	from_chars_floating_point_nan.hpp
 *
 *	@brief	from_chars_floating_point_nan の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_NAN_HPP
#define HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_NAN_HPP

#include <hamon/charconv/detail/starts_with_case_insensitive.hpp>
#include <hamon/charconv/detail/make_floating_point_nan.hpp>
#include <hamon/charconv/from_chars_result.hpp>
#include <hamon/cctype/isalnum.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename F>
inline HAMON_CXX14_CONSTEXPR hamon::from_chars_result
from_chars_floating_point_nan(const char* first, const char* last, F& value, bool negative) HAMON_NOEXCEPT
{
	// pre: first points at 'n' (case-insensitively)

	if (!starts_with_case_insensitive(first + 1, last, "an"))
	{
		// definitely invalid
		return { first, hamon::errc::invalid_argument };
	}

	// definitely nan
	first += 3;

	if (last - first >= 2 && first[0] == '(')
	{
		size_t offset = 1;
		do
		{
			if (first[offset] == ')')
			{
				first += offset + 1;
				break;
			}

			if (first[offset] != '_' && !hamon::isalnum(first[offset]))
			{
				break;
			}

			++offset;
		}
		while (first + offset != last);
	}

	value = make_floating_point_nan<F>(negative);

	return { first, hamon::errc{} };
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_NAN_HPP
