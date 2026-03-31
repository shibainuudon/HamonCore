/**
 *	@file	isgraph.hpp
 *
 *	@brief	isgraph の定義
 */

#ifndef HAMON_CCTYPE_ISGRAPH_HPP
#define HAMON_CCTYPE_ISGRAPH_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct isgraph_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator()(T c) const HAMON_NOEXCEPT
	{
		return 0x21 <= c && c <= 0x7E;
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::isgraph_fn isgraph{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISGRAPH_HPP
