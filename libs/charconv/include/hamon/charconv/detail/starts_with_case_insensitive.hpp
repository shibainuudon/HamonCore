/**
 *	@file	starts_with_case_insensitive.hpp
 *
 *	@brief	starts_with_case_insensitive の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_STARTS_WITH_CASE_INSENSITIVE_HPP
#define HAMON_CHARCONV_DETAIL_STARTS_WITH_CASE_INSENSITIVE_HPP

#include <hamon/cctype/tolower.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_NODISCARD inline bool
starts_with_case_insensitive(const char* first, const char* last, const char* lowercase) noexcept
{
	// pre: lowercase contains only ['a', 'z'] and is null-terminated

	for (; first != last && *lowercase != '\0'; ++first, ++lowercase)
	{
		if (hamon::tolower(*first) != *lowercase)
		{
			return false;
		}
	}

	return *lowercase == '\0';
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_STARTS_WITH_CASE_INSENSITIVE_HPP
