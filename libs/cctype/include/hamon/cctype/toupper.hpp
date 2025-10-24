/**
 *	@file	toupper.hpp
 *
 *	@brief	toupper の定義
 */

#ifndef HAMON_CCTYPE_TOUPPER_HPP
#define HAMON_CCTYPE_TOUPPER_HPP

#include <hamon/cctype/islower.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

struct toupper_fn
{
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T
	operator()(T c) const HAMON_NOEXCEPT
	{
		return hamon::islower(c) ? (c ^ 0x20) : c;
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR detail::toupper_fn toupper{};

}	// inline namespace cpo

}	// namespace hamon

#endif // HAMON_CCTYPE_TOUPPER_HPP
