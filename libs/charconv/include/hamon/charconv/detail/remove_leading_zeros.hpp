/**
 *	@file	remove_leading_zeros.hpp
 *
 *	@brief	remove_leading_zeros の定義
 */

#ifndef HAMON_CHARCONV_DETAIL_REMOVE_LEADING_ZEROS_HPP
#define HAMON_CHARCONV_DETAIL_REMOVE_LEADING_ZEROS_HPP

#include <hamon/memory/to_address.hpp>
#include <hamon/string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_NODISCARD inline HAMON_CXX14_CONSTEXPR hamon::string_view
remove_leading_zeros(hamon::string_view sv) HAMON_NOEXCEPT
{
	// MSVC-STLのstring_viewだと、to_address(sv.end()) を呼び出したときに
	// 実行時エラーになるのでそうならないように対処しないといけない。

	if (sv.empty())
	{
		return sv;
	}

	const char* first = hamon::to_address(sv.begin());
	const char* last = first + sv.size();
	for (; first != last; ++first)
	{
		if (*first != '0')
		{
			break;
		}
	}
	return {first, last};
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CHARCONV_DETAIL_REMOVE_LEADING_ZEROS_HPP
