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
HAMON_NODISCARD hamon::from_chars_result
from_chars_floating_point_nan(const char* first, const char* last, F& value, bool negative, const char* ptr) noexcept
{
	// pre: ptr points at 'n' (case-insensitively)

	if (!starts_with_case_insensitive(ptr + 1, last, "an"))
	{
		// definitely invalid
		return { first, hamon::errc::invalid_argument };
	}

	// definitely nan
	ptr += 3;

	if (last - ptr >= 2 && ptr[0] == '(')
	{
		size_t offset = 1;
		do
		{
			if (ptr[offset] == ')')
			{
				ptr += offset + 1;
				break;
			}

			if (ptr[offset] != '_' && !hamon::isalnum(ptr[offset]))
			{
				break;
			}

			++offset;
		}
		while (ptr + offset != last);
	}

	value = make_floating_point_nan<F>(negative);

	return { ptr, hamon::errc{} };
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_FROM_CHARS_FLOATING_POINT_NAN_HPP
