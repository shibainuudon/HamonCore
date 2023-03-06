/**
 *	@file	adjacent_find.hpp
 *
 *	@brief	ranges::adjacent_find の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_ADJACENT_FIND_HPP
#define HAMON_ALGORITHM_RANGES_ADJACENT_FIND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::adjacent_find;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_binary_predicate.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
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

struct adjacent_find_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_binary_predicate,
			ProjectedIter,
			ProjectedIter,
			Pred,
			ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last, Pred pred = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return first;
		}

		auto next_it = first;
		for (; ++next_it != last; first = next_it)
		{
			if (hamon::invoke(pred,
				hamon::invoke(proj, *first),
				hamon::invoke(proj, *next_it)))
			{
				return first;
			}
		}

		return next_it;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_binary_predicate,
			ProjectedIter,
			ProjectedIter,
			Pred,
			ranges::equal_to)
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Pred pred = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(pred), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR adjacent_find_fn adjacent_find{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_ADJACENT_FIND_HPP
