/**
 *	@file	uninitialized_value_construct_n.hpp
 *
 *	@brief	ranges::uninitialized_value_construct_n を定義
 */

#ifndef HAMON_MEMORY_RANGES_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
#define HAMON_MEMORY_RANGES_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::uninitialized_value_construct_n;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/memory/ranges/uninitialized_value_construct.hpp>
#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.4 uninitialized_value_construct[uninitialized.construct.value]

struct uninitialized_value_construct_n_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_iterator, I),
		typename = hamon::enable_if_t<hamon::default_initializable_t<hamon::iter_value_t<I>>::value>
	>
//	requires hamon::default_initializable<hamon::iter_value_t<I>>
	I operator()(I first, hamon::iter_difference_t<I> n) const
	{
		// [uninitialized.construct.value]/4
		return hamon::ranges::uninitialized_value_construct(
			hamon::make_counted_iterator(first, n),
			hamon::default_sentinel).base();
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::uninitialized_value_construct_n_fn uninitialized_value_construct_n{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_UNINITIALIZED_VALUE_CONSTRUCT_N_HPP
