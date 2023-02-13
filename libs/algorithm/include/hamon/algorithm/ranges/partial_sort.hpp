/**
 *	@file	partial_sort.hpp
 *
 *	@brief	ranges::partial_sort の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_PARTIAL_SORT_HPP
#define HAMON_ALGORITHM_RANGES_PARTIAL_SORT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::partial_sort;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/make_heap.hpp>
#include <hamon/algorithm/ranges/pop_heap.hpp>
#include <hamon/algorithm/ranges/push_heap.hpp>
#include <hamon/algorithm/ranges/sort_heap.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sortable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
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

struct partial_sort_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Comp = ranges::less,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Iter middle, Sent last,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		Iter,
		hamon::sortable<Iter, Comp, Proj>)
	{
		if (first == middle)
		{
			return ranges::next(first, last);
		}

		ranges::make_heap(first, middle, comp, proj);
		auto i = middle;
		for (; i != last; ++i)
		{
			if (hamon::invoke(comp,
				hamon::invoke(proj, *i),
				hamon::invoke(proj, *first)))
			{
				ranges::pop_heap(first, middle, comp, proj);
				ranges::iter_swap(middle-1, i);
				ranges::push_heap(first, middle, comp, proj);
			}
		}

		ranges::sort_heap(first, middle, comp, proj);

		return i;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::random_access_range, Range),
		typename Comp = ranges::less,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, ranges::iterator_t<Range> middle,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_iterator_t<Range>,
		hamon::sortable<ranges::iterator_t<Range>, Comp, Proj>)
	{
		return (*this)(
			ranges::begin(r),
			std::move(middle),
			ranges::end(r),
			std::move(comp),
			std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR partial_sort_fn partial_sort{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_PARTIAL_SORT_HPP
