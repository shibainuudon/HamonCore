/**
 *	@file	includes.hpp
 *
 *	@brief	ranges::includes の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_INCLUDES_HPP
#define HAMON_ALGORITHM_RANGES_INCLUDES_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::includes;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct includes_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename ProjectedIter1 = hamon::projected<Iter1, Proj1>,
		typename ProjectedIter2 = hamon::projected<Iter2, Proj2>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter1,
			ProjectedIter2,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		while (first1 != last1 && first2 != last2)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj2, *first2),
				hamon::invoke(proj1, *first1)))
			{
				return false;
			}
			else if (hamon::invoke(comp,
				hamon::invoke(proj1, *first1),
				hamon::invoke(proj2, *first2)))
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		return first2 == last2;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range2),
		typename Proj1 = hamon::identity,
		typename Proj2 = hamon::identity,
		typename ProjectedIter1 =
			hamon::projected<ranges::iterator_t<Range1>, Proj1>,
		typename ProjectedIter2 =
			hamon::projected<ranges::iterator_t<Range2>, Proj2>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter1,
			ProjectedIter2,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR bool operator()(
		Range1&& r1, Range2&& r2,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			std::move(comp),
			std::move(proj1), std::move(proj2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR includes_fn includes{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_INCLUDES_HPP
