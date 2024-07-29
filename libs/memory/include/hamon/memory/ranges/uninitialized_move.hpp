/**
 *	@file	uninitialized_move.hpp
 *
 *	@brief	ranges::uninitialized_move を定義
 */

#ifndef HAMON_MEMORY_RANGES_UNINITIALIZED_MOVE_HPP
#define HAMON_MEMORY_RANGES_UNINITIALIZED_MOVE_HPP

#include <hamon/config.hpp>
#include <memory>

#if defined(__cpp_lib_ranges) && (__cpp_lib_ranges >= 201911L) && (HAMON_CXX_STANDARD >= 20)

namespace hamon
{
namespace ranges
{

using std::ranges::uninitialized_move_result;
using std::ranges::uninitialized_move;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/memory/detail/uninitialized_move_impl.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_range.hpp>
#include <hamon/memory/ranges/detail/nothrow_sentinel_for.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>

namespace hamon
{
namespace ranges
{

template <typename I, typename O>
using uninitialized_move_result = hamon::ranges::in_out_result<I, O>;

namespace detail
{

// 27.11.6 uninitialized_move[uninitialized.move]

struct uninitialized_move_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_iterator, O),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_sentinel_for, O, S2),
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<
				hamon::iter_value_t<O>,
				hamon::iter_rvalue_reference_t<I>
			>::value
		>
	>
//	requires hamon::constructible_from<hamon::iter_value_t<O>, hamon::iter_rvalue_reference_t<I>>
	uninitialized_move_result<I, O>
	operator()(I ifirst, S1 ilast, O ofirst, S2 olast) const
	{
		return hamon::detail::uninitialized_move_impl(ifirst, ilast, ofirst, olast);
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, IR),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::detail::nothrow_forward_range, OR),
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<
				hamon::ranges::range_value_t<OR>,
				hamon::ranges::range_rvalue_reference_t<IR>
			>::value
		>
	>
//	requires hamon::constructible_from<hamon::ranges::range_value_t<OR>, hamon::ranges::range_rvalue_reference_t<IR>>
	uninitialized_move_result<hamon::ranges::borrowed_iterator_t<IR>, hamon::ranges::borrowed_iterator_t<OR>>
	operator()(IR&& in_range, OR&& out_range) const
	{
		return hamon::detail::uninitialized_move_impl(
			hamon::ranges::begin(in_range),  hamon::ranges::end(in_range),
			hamon::ranges::begin(out_range), hamon::ranges::end(out_range));
	}
};

}	// namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::uninitialized_move_fn uninitialized_move{};

}	// inline namespace cpo

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_MEMORY_RANGES_UNINITIALIZED_MOVE_HPP
