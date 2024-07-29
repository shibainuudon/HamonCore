/**
 *	@file	uninitialized_move_n.hpp
 *
 *	@brief	ranges::uninitialized_move_n を定義
 */

#ifndef HAMON_MEMORY_RANGES_UNINITIALIZED_MOVE_N_HPP
#define HAMON_MEMORY_RANGES_UNINITIALIZED_MOVE_N_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::uninitialized_move_n_result;
using std::ranges::uninitialized_move_n;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_sentinel_for.hpp>
#include <hamon/memory/ranges/uninitialized_move.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{
namespace ranges
{

template <typename I, typename O>
using uninitialized_move_n_result = hamon::ranges::in_out_result<I, O>;

namespace detail
{

// 27.11.6 uninitialized_move[uninitialized.move]

struct uninitialized_move_n_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_iterator, O),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_sentinel_for, O, S),
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<
				hamon::iter_value_t<O>,
				hamon::iter_rvalue_reference_t<I>
			>::value
		>
	>
//	requires hamon::constructible_from<hamon::iter_value_t<O>, hamon::iter_rvalue_reference_t<I>>
	uninitialized_move_n_result<I, O>
	operator()(I ifirst, hamon::iter_difference_t<I> n, O ofirst, S olast) const
	{
		// [uninitialized.move]/9
		auto t = hamon::ranges::uninitialized_move(
			hamon::make_counted_iterator(hamon::move(ifirst), n),
			hamon::default_sentinel, ofirst, olast);
		return {hamon::move(t.in).base(), t.out};
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::uninitialized_move_n_fn uninitialized_move_n{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_UNINITIALIZED_MOVE_N_HPP
