/**
 *	@file	to_unsigned_like.hpp
 *
 *	@brief	to_unsigned_like の定義
 */

#ifndef HAMON_RANGES_DETAIL_TO_UNSIGNED_LIKE_HPP
#define HAMON_RANGES_DETAIL_TO_UNSIGNED_LIKE_HPP

#include <hamon/ranges/detail/max_size_type.hpp>
#include <hamon/ranges/detail/max_diff_type.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

HAMON_CONSTEXPR hamon::ranges::detail::max_size_type
to_unsigned_like(hamon::ranges::detail::max_size_type t) HAMON_NOEXCEPT
{
	return t;
}

HAMON_CONSTEXPR hamon::ranges::detail::max_size_type
to_unsigned_like(hamon::ranges::detail::max_diff_type t) HAMON_NOEXCEPT
{
	return hamon::ranges::detail::max_size_type(t);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
HAMON_CONSTEXPR hamon::make_unsigned_t<T>
to_unsigned_like(T t) HAMON_NOEXCEPT
{
	return static_cast<hamon::make_unsigned_t<T>>(t);
}

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_TO_UNSIGNED_LIKE_HPP
