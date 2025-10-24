/**
 *	@file	tolower.hpp
 *
 *	@brief	tolower の定義
 */

#ifndef HAMON_CCTYPE_TOLOWER_HPP
#define HAMON_CCTYPE_TOLOWER_HPP

#include <hamon/cctype/isupper.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct tolower_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T
	operator()(T c) const HAMON_NOEXCEPT
	{
		return hamon::isupper(c) ? (c ^ 0x20) : c;
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::tolower_fn tolower{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_TOLOWER_HPP
