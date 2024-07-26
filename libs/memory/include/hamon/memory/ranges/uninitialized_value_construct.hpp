/**
 *	@file	uninitialized_value_construct.hpp
 *
 *	@brief	ranges::uninitialized_value_construct を定義
 */

#ifndef HAMON_MEMORY_RANGES_UNINITIALIZED_VALUE_CONSTRUCT_HPP
#define HAMON_MEMORY_RANGES_UNINITIALIZED_VALUE_CONSTRUCT_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::uninitialized_value_construct;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_impl.hpp>
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

// 27.11.4 uninitialized_value_construct[uninitialized.construct.value]

struct uninitialized_value_construct_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_sentinel_for, I, S),
		typename = hamon::enable_if_t<hamon::default_initializable_t<hamon::iter_value_t<I>>::value>
	>
	//requires hamon::default_initializable<hamon::iter_value_t<I>>
	I operator()(I first, S last) const
	{
		return hamon::detail::uninitialized_value_construct_impl(first, last);
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_range, R),
		typename = hamon::enable_if_t<hamon::default_initializable_t<hamon::ranges::range_value_t<R>>::value>
	>
	//requires hamon::default_initializable<hamon::ranges::range_value_t<R>>
	hamon::ranges::borrowed_iterator_t<R> operator()(R&& r) const
	{
		return hamon::detail::uninitialized_value_construct_impl(hamon::ranges::begin(r), hamon::ranges::end(r));
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::uninitialized_value_construct_fn uninitialized_value_construct{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_UNINITIALIZED_VALUE_CONSTRUCT_HPP
