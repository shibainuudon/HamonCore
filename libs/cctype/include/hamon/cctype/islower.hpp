/**
 *	@file	islower.hpp
 *
 *	@brief	islower の定義
 */

#ifndef HAMON_CCTYPE_ISLOWER_HPP
#define HAMON_CCTYPE_ISLOWER_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct islower_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator()(T c) const HAMON_NOEXCEPT
	{
		return 'a' <= c && c <= 'z';
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::islower_fn islower{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISLOWER_HPP
