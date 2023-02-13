/**
 *	@file	partition_point.hpp
 *
 *	@brief	ranges::partition_point の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_PARTITION_POINT_HPP
#define HAMON_ALGORITHM_RANGES_PARTITION_POINT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::partition_point;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_unary_predicate.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct partition_point_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last,
		Pred pred, Proj proj = {}) const
	{
		auto len = ranges::distance(first, last);

		while (len > 0)
		{
			auto half = len / 2;
			auto middle = first;
			ranges::advance(middle, half);
			if (hamon::invoke(pred, hamon::invoke(proj, *middle)))
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter =
			hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM(
			hamon::indirect_unary_predicate, ProjectedIter, Pred)
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Pred pred, Proj proj ={}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR partition_point_fn partition_point{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_PARTITION_POINT_HPP
