/**
 *	@file	as_const.hpp
 *
 *	@brief	as_const の定義
 */

#ifndef HAMON_RANGES_DETAIL_AS_CONST_HPP
#define HAMON_RANGES_DETAIL_AS_CONST_HPP

#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <typename T>
HAMON_CONSTEXPR hamon::remove_reference_t<T> const&
as_const(T& t) HAMON_NOEXCEPT
{
	return static_cast<hamon::remove_reference_t<T> const&>(t);
}

template <typename T>
HAMON_CONSTEXPR T const&&
as_const(T&& t) HAMON_NOEXCEPT
{
	return static_cast<T const&&>(t);
}

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_AS_CONST_HPP
