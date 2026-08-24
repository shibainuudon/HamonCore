/**
 *	@file	for_each.hpp
 *
 *	@brief	ranges::for_each の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOR_EACH_HPP
#define HAMON_ALGORITHM_RANGES_FOR_EACH_HPP

#include <hamon/algorithm/ranges/in_fun_result.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_unary_invocable.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename F>
using for_each_result = in_fun_result<Iter, F>;

struct for_each_fn
{
	template <
		HAMON_CONSTRAINT(hamon::input_iterator, Iter),
		HAMON_CONSTRAINT(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINT(
			hamon::indirectly_unary_invocable,
			ProjectedIter,
			Fun)
	>
	HAMON_CXX14_CONSTEXPR for_each_result<Iter, Fun>
	operator()(Iter first, Sent last, Fun f, Proj proj ={}) const
	{
		for (; first != last; ++first)
		{
			hamon::invoke(f, hamon::invoke(proj, *first));
		}

		return { hamon::move(first), hamon::move(f) };
	}

	template <
		HAMON_CONSTRAINT(hamon::ranges::input_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINT(
			hamon::indirectly_unary_invocable,
			ProjectedIter,
			Fun)
	>
	HAMON_CXX14_CONSTEXPR for_each_result<ranges::borrowed_iterator_t<Range>, Fun>
	operator()(Range&& r, Fun f, Proj proj ={}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(f), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR for_each_fn for_each{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_FOR_EACH_HPP
