﻿/**
 *	@file	upper_bound.hpp
 *
 *	@brief	ranges::upper_bound の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_UPPER_BOUND_HPP
#define HAMON_ALGORITHM_RANGES_UPPER_BOUND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::upper_bound;

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
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/iterator/projected_value_t.hpp>
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

// 27.8.4.3 upper_bound[upper.bound]

struct upper_bound_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<I, Proj>,
		typename ProjectedIter = hamon::projected<I, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			T const*,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR I operator()(
		I first, S last,
		T const& value, Comp comp = {}, Proj proj = {}) const
	{
		auto len = ranges::distance(first, last);

		while (len > 0)
		{
			auto half = len / 2;
			auto middle = first;
			ranges::advance(middle, half);
			if (hamon::invoke(comp, value, hamon::invoke(proj, *middle)))
			{
				len = half;
			}
			else
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
		}

		return first;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, R),
		typename Proj = hamon::identity,
		typename T = hamon::projected_value_t<ranges::iterator_t<R>, Proj>,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<R>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			T const*,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<R>
	operator()(R&& r, T const& value, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, hamon::move(comp), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR upper_bound_fn upper_bound{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_UPPER_BOUND_HPP
