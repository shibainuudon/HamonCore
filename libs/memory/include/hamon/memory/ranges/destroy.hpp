/**
 *	@file	destroy.hpp
 *
 *	@brief	ranges::destroy を定義
 */

#ifndef HAMON_MEMORY_RANGES_DESTROY_HPP
#define HAMON_MEMORY_RANGES_DESTROY_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20) &&	\
	!defined(HAMON_STDLIB_LIBCPP)	/* libc++ の ranges::destroy は first と last が違う型の場合に対応していない*/

namespace hamon
{
namespace ranges
{

using std::ranges::destroy;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/concepts/destructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/memory/ranges/detail/nothrow_input_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_input_range.hpp>
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

// 27.11.9 destroy[specialized.destroy]

struct destroy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_sentinel_for, I, S),
		typename = hamon::enable_if_t<hamon::destructible_t<hamon::iter_value_t<I>>::value>
	>
//	requires hamon::destructible<hamon::iter_value_t<I>>
	HAMON_CXX14_CONSTEXPR I
	operator()(I first, S last) const HAMON_NOEXCEPT
	{
		return hamon::detail::destroy_impl(first, last);
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_input_range, R),
		typename = hamon::enable_if_t<hamon::destructible_t<hamon::ranges::range_value_t<R>>::value>
	>
//	requires hamon::destructible<hamon::ranges::range_value_t<R>>
	HAMON_CXX14_CONSTEXPR hamon::ranges::borrowed_iterator_t<R>
	operator()(R&& r) const HAMON_NOEXCEPT
	{
		return hamon::detail::destroy_impl(hamon::ranges::begin(r), hamon::ranges::end(r));
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::destroy_fn destroy{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_DESTROY_HPP
