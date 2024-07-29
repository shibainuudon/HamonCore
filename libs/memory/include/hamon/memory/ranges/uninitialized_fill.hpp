/**
 *	@file	uninitialized_fill.hpp
 *
 *	@brief	ranges::uninitialized_fill を定義
 */

#ifndef HAMON_MEMORY_RANGES_UNINITIALIZED_FILL_HPP
#define HAMON_MEMORY_RANGES_UNINITIALIZED_FILL_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::uninitialized_fill;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/memory/detail/uninitialized_fill_impl.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_range.hpp>
#include <hamon/memory/ranges/detail/nothrow_sentinel_for.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{
namespace ranges
{

namespace detail
{

// 27.11.7 uninitialized_fill[uninitialized.fill]

struct uninitialized_fill_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_sentinel_for, I, S),
		typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::iter_value_t<I>, T const&>::value
		>
	>
//	requires hamon::constructible_from<hamon::iter_value_t<I>, T const&>
	I operator()(I first, S last, T const& x) const
	{
		return hamon::detail::uninitialized_fill_impl(
			first, last, x);
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_range, R),
		typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::ranges::range_value_t<R>, T const&>::value
		>
	>
//	requires hamon::constructible_from<hamon::ranges::range_value_t<R>, T const&>
	hamon::ranges::borrowed_iterator_t<R>
	operator()(R&& r, T const& x) const
	{
		return hamon::detail::uninitialized_fill_impl(
			hamon::ranges::begin(r), hamon::ranges::end(r), x);
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::uninitialized_fill_fn uninitialized_fill{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_UNINITIALIZED_FILL_HPP
