/**
 *	@file	isupper.hpp
 *
 *	@brief	isupper の定義
 */

#ifndef HAMON_CCTYPE_ISUPPER_HPP
#define HAMON_CCTYPE_ISUPPER_HPP

#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct isupper_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator()(T c) const HAMON_NOEXCEPT
	{
		return 'A' <= c && c <= 'Z';
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::isupper_fn isupper{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISUPPER_HPP
