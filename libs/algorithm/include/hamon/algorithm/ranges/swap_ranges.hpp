/**
 *	@file	swap_ranges.hpp
 *
 *	@brief	ranges::swap_ranges の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SWAP_RANGES_HPP
#define HAMON_ALGORITHM_RANGES_SWAP_RANGES_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::swap_ranges;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_in_result.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

template <typename Iter1, typename Iter2>
using swap_ranges_result = in_in_result<Iter1, Iter2>;

struct swap_ranges_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter1),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter1, Sent1),
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter2),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter2, Sent2)
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::indirectly_swappable<Iter1, Iter2>::value
		>
	>
#else
	>
	requires hamon::indirectly_swappable<Iter1, Iter2>
#endif
	HAMON_CXX14_CONSTEXPR swap_ranges_result<Iter1, Iter2>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2) const
	{
		for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
		{
			ranges::iter_swap(first1, first2);
		}

		return { std::move(first1), std::move(first2) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range1),
		HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, Range2)
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<
			hamon::indirectly_swappable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>
			>::value
		>
	>
#else
	>
	requires hamon::indirectly_swappable<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>
	>
#endif
	HAMON_CXX14_CONSTEXPR swap_ranges_result<
		ranges::borrowed_iterator_t<Range1>,
		ranges::borrowed_iterator_t<Range2>>
	operator()(Range1&& r1, Range2&& r2) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR swap_ranges_fn swap_ranges{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_SWAP_RANGES_HPP
