/**
 *	@file	equal_range.hpp
 *
 *	@brief	ranges::equal_range の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_EQUAL_RANGE_HPP
#define HAMON_ALGORITHM_RANGES_EQUAL_RANGE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::equal_range;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/lower_bound.hpp>
#include <hamon/algorithm/ranges/upper_bound.hpp>
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
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.8.4.4 equal_range[equal.range]

struct equal_range_fn
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
	HAMON_CXX14_CONSTEXPR ranges::subrange<I> operator()(
		I first, S last,
		T const& value, Comp comp = {}, Proj proj = {}) const
	{
		auto len = ranges::distance(first, last);

		while (len > 0)
		{
			auto half = len / 2;
			auto middle = first;
			ranges::advance(middle, half);
			if (hamon::invoke(comp, hamon::invoke(proj, *middle), value))
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else if (hamon::invoke(comp, value, hamon::invoke(proj, *middle)))
			{
				len = half;
			}
			else
			{
				auto left = ranges::lower_bound(
					first, middle, value, comp, proj);
				ranges::advance(first, len);
				auto right = ranges::upper_bound(
					++middle, first, value, comp, proj);
				return { left, right };
			}
		}

		return { first, first };
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, R),
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
	HAMON_CXX14_CONSTEXPR ranges::borrowed_subrange_t<R>
	operator()(R&& r, T const& value, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, hamon::move(comp), hamon::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR equal_range_fn equal_range{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_EQUAL_RANGE_HPP
