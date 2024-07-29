/**
 *	@file	uninitialized_fill_n.hpp
 *
 *	@brief	ranges::uninitialized_fill_n を定義
 */

#ifndef HAMON_MEMORY_RANGES_UNINITIALIZED_FILL_N_HPP
#define HAMON_MEMORY_RANGES_UNINITIALIZED_FILL_N_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::uninitialized_fill_n;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/memory/ranges/uninitialized_fill.hpp>
#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{
namespace ranges
{

namespace detail
{

// 27.11.7 uninitialized_fill[uninitialized.fill]

struct uninitialized_fill_n_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_iterator, I),
		typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::iter_value_t<I>, T const&>::value
		>
	>
//	requires hamon::constructible_from<hamon::iter_value_t<I>, T const&>
	I operator()(I first, hamon::iter_difference_t<I> n, T const& x) const
	{
		// [uninitialized.fill]/4
		return hamon::ranges::uninitialized_fill(
			hamon::make_counted_iterator(first, n),
			hamon::default_sentinel, x).base();
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::uninitialized_fill_n_fn uninitialized_fill_n{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_UNINITIALIZED_FILL_N_HPP
