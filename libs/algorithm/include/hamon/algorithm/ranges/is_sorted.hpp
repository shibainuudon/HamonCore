/**
 *	@file	is_sorted.hpp
 *
 *	@brief	ranges::is_sorted の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_IS_SORTED_HPP
#define HAMON_ALGORITHM_RANGES_IS_SORTED_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::is_sorted;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirect_strict_weak_order.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct is_sorted_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<Iter, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			hamon::ranges::less)
	>
	HAMON_CXX14_CONSTEXPR bool
	operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return true;
		}

		auto next_it = first;
		for (++next_it; next_it != last; first = next_it, (void)++next_it)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj, *next_it),
				hamon::invoke(proj, *first)))
			{
				return false;
			}
		}

		return true;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			hamon::ranges::less)
	>
	HAMON_CXX14_CONSTEXPR bool
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR is_sorted_fn is_sorted{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_IS_SORTED_HPP
