/**
 *	@file	isalnum.hpp
 *
 *	@brief	isalnum の定義
 */

#ifndef HAMON_CCTYPE_ISALNUM_HPP
#define HAMON_CCTYPE_ISALNUM_HPP

#include <hamon/cctype/isalpha.hpp>
#include <hamon/cctype/isdigit.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct isalnum_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
	operator()(T c) const HAMON_NOEXCEPT
	{
		return hamon::isalpha(c) || hamon::isdigit(c);
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::isalnum_fn isalnum{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_ISALNUM_HPP
