/**
 *	@file	remove_trailing_zeros.hpp
 *
 *	@brief	remove_trailing_zeros の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_REMOVE_TRAILING_ZEROS_HPP
#define HAMON_CHARCONV_DETAIL_REMOVE_TRAILING_ZEROS_HPP

#include <hamon/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR hamon::string_view
remove_trailing_zeros(hamon::string_view sv) HAMON_NOEXCEPT
{
	const char* first = sv.data();
	const char* last = first + sv.size();
	for (; first != last; --last)
	{
		if (*(last - 1) != '0')
		{
			break;
		}
	}
	return {first, last};
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_REMOVE_TRAILING_ZEROS_HPP
