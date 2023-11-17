/**
 *	@file	possibly_const_range.hpp
 *
 *	@brief	possibly_const_range の定義
 */

#ifndef HAMON_RANGES_DETAIL_POSSIBLY_CONST_RANGE_HPP
#define HAMON_RANGES_DETAIL_POSSIBLY_CONST_RANGE_HPP

#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/constant_range.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.as.const], as const view

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <hamon::ranges::input_range R>
constexpr auto& possibly_const_range(R& r) noexcept
{
	if constexpr (
		 hamon::ranges::constant_range<const R> &&
		!hamon::ranges::constant_range<R>)
	{
		return const_cast<const R&>(r);
	}
	else
	{
		return r;
	}
}

#else

template <typename R,
	typename = hamon::enable_if_t<
		 hamon::ranges::constant_range_t<const R>::value &&
		!hamon::ranges::constant_range_t<R>::value>>
constexpr const R&
possibly_const_range_impl(R& r, hamon::detail::overload_priority<1>) noexcept
{
	return const_cast<const R&>(r);
}

template <typename R>
constexpr R&
possibly_const_range_impl(R& r, hamon::detail::overload_priority<0>) noexcept
{
	return r;
}

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R)>
constexpr auto
possibly_const_range(R& r) noexcept
->decltype(possibly_const_range_impl(r, hamon::detail::overload_priority<1>{}))
{
	return possibly_const_range_impl(r, hamon::detail::overload_priority<1>{});
}

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_POSSIBLY_CONST_RANGE_HPP
