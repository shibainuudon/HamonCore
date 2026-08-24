/**
 *	@file	all_of.hpp
 *
 *	@brief	ranges::all_of の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_ALL_OF_HPP
#define HAMON_ALGORITHM_RANGES_ALL_OF_HPP

#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct all_of_fn
{
	template <
		HAMON_CONSTRAINT(hamon::input_iterator, Iter),
		HAMON_CONSTRAINT(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINT(hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Iter first, Sent last,
		Pred pred, Proj proj ={}) const
	{
		for (; first != last; ++first)
		{
			if (!(bool)hamon::invoke(pred, hamon::invoke(proj, *first)))
			{
				return false;
			}
		}

		return true;
	}

	template <
		HAMON_CONSTRAINT(hamon::ranges::input_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINT(hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Range&& r, Pred pred, Proj proj ={}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(pred), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR all_of_fn all_of{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_ALL_OF_HPP
