/**
 *	@file	minmax_element.hpp
 *
 *	@brief	ranges::minmax_element の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_MINMAX_ELEMENT_HPP
#define HAMON_ALGORITHM_RANGES_MINMAX_ELEMENT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::minmax_element;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/min_max_result.hpp>
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
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter>
using minmax_element_result = min_max_result<Iter>;

struct minmax_element_fn
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
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR minmax_element_result<Iter>
	operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return { first, first };
		}

		minmax_element_result<Iter> result = { first, first };
		auto i = first;
		while (++i != last)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj, *i),
				hamon::invoke(proj, *result.min)))
			{
				result.min = i;
			}

			if (!(bool)hamon::invoke(comp,
				hamon::invoke(proj, *i),
				hamon::invoke(proj, *result.max)))
			{
				result.max = i;
			}
		}

		return result;
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::forward_range, Range),
		typename Proj = hamon::identity,
		typename ProjectedIter = hamon::projected<ranges::iterator_t<Range>, Proj>,
		HAMON_CONSTRAINED_PARAM_D(
			hamon::indirect_strict_weak_order,
			ProjectedIter,
			Comp,
			ranges::less)
	>
	HAMON_CXX14_CONSTEXPR minmax_element_result<ranges::borrowed_iterator_t<Range>>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR minmax_element_fn minmax_element{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_MINMAX_ELEMENT_HPP
