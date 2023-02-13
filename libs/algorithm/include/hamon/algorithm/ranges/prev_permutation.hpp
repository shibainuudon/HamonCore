/**
 *	@file	prev_permutation.hpp
 *
 *	@brief	ranges::prev_permutation の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_PREV_PERMUTATION_HPP
#define HAMON_ALGORITHM_RANGES_PREV_PERMUTATION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::prev_permutation;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_found_result.hpp>
#include <hamon/algorithm/ranges/reverse.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sortable.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
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
using prev_permutation_result = in_found_result<Iter>;

struct prev_permutation_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename Comp = ranges::less,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		prev_permutation_result<Iter>,
		hamon::sortable<Iter, Comp, Proj>)
	{
		if (first == last)
		{
			return { std::move(first), false };
		}

		auto i = first;
		++i;
		if (i == last)
		{
			return { std::move(i), false };
		}

		auto lasti = ranges::next(first, last);
		i = lasti;
		--i;

		for (;;)
		{
			auto ii = i;
			--i;
			if (hamon::invoke(comp,
				hamon::invoke(proj, *ii),
				hamon::invoke(proj, *i)))
			{
				auto j = lasti;
				while (!(bool)hamon::invoke(comp,
					hamon::invoke(proj, *--j),
					hamon::invoke(proj, *i)))
				{
					;
				}

				ranges::iter_swap(i, j);
				ranges::reverse(ii, last);
				return { std::move(lasti), true };
			}

			if (i == first)
			{
				ranges::reverse(first, last);
				return { std::move(lasti), false };
			}
		}
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::bidirectional_range, Range),
		typename Comp = ranges::less,
		typename Proj = hamon::identity
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		prev_permutation_result<ranges::borrowed_iterator_t<Range>>,
		hamon::sortable<ranges::iterator_t<Range>, Comp, Proj>)
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR prev_permutation_fn prev_permutation{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_PREV_PERMUTATION_HPP
