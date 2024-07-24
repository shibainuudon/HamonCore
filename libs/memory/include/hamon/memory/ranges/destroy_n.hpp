/**
 *	@file	destroy_n.hpp
 *
 *	@brief	ranges::destroy_n を定義
 */

#ifndef HAMON_MEMORY_RANGES_DESTROY_N_HPP
#define HAMON_MEMORY_RANGES_DESTROY_N_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::destroy_n;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/destructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/memory/ranges/destroy.hpp>
#include <hamon/memory/ranges/detail/nothrow_input_iterator.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.9 destroy[specialized.destroy]

struct destroy_n_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_input_iterator, I),
		typename = hamon::enable_if_t<hamon::destructible_t<hamon::iter_value_t<I>>::value>
	>
//	requires hamon::destructible<hamon::iter_value_t<I>>
	HAMON_CXX14_CONSTEXPR I
	operator()(I first, hamon::iter_difference_t<I> n) const HAMON_NOEXCEPT
	{
		// [specialized.destroy]/5
		return hamon::ranges::destroy(
			hamon::make_counted_iterator(hamon::move(first), n), hamon::default_sentinel).base();
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::destroy_n_fn destroy_n{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_DESTROY_N_HPP
