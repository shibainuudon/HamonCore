/**
 *	@file	statically_widen.hpp
 *
 *	@brief	STATICALLY-WIDEN の定義
 */

#ifndef HAMON_DETAIL_STATICALLY_WIDEN_HPP
#define HAMON_DETAIL_STATICALLY_WIDEN_HPP

#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 29.1 General[time.general]

template <typename CharT>
struct statically_widen;

template <>
struct statically_widen<char>
{
	static HAMON_CXX11_CONSTEXPR
	char const* invoke(char const* s, wchar_t const*)
	{
		return s;
	}
};

template <>
struct statically_widen<wchar_t>
{
	static HAMON_CXX11_CONSTEXPR
	wchar_t const* invoke(char const*, wchar_t const* s)
	{
		return s;
	}
};

#define HAMON_STATICALLY_WIDEN(C, S) \
	hamon::detail::statically_widen<C>::invoke(S, L##S)

}	// namespace detail
}	// namespace hamon

#endif // HAMON_DETAIL_STATICALLY_WIDEN_HPP
