/**
 *	@file	unguarded_partition_pivot.hpp
 *
 *	@brief	unguarded_partition_pivot の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_UNGUARDED_PARTITION_PIVOT_HPP
#define HAMON_ALGORITHM_DETAIL_UNGUARDED_PARTITION_PIVOT_HPP

#include <hamon/algorithm/iter_swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Iterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
move_median_to_first(
	Iterator result,
	Iterator a,
	Iterator b,
	Iterator c,
	Compare comp)
{
	if (comp(*a, *b))
	{
		if (comp(*b, *c))
		{
			hamon::iter_swap(result, b);
		}
		else if (comp(*a, *c))
		{
			hamon::iter_swap(result, c);
		}
		else
		{
			hamon::iter_swap(result, a);
		}
	}
	else if (comp(*a, *c))
	{
		hamon::iter_swap(result, a);
	}
	else if (comp(*b, *c))
	{
		hamon::iter_swap(result, c);
	}
	else
	{
		hamon::iter_swap(result, b);
	}
}

template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
unguarded_partition(
	RandomAccessIterator first,
	RandomAccessIterator last,
	RandomAccessIterator pivot,
	Compare comp)
{
	while (true)
	{
		while (comp(*first, *pivot))
		{
			++first;
		}

		--last;
		while (comp(*pivot, *last))
		{
			--last;
		}

		if (!(first < last))
		{
			return first;
		}

		hamon::iter_swap(first, last);
		++first;
	}
}

template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
unguarded_partition_pivot(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	auto mid = first + (last - first) / 2;
	hamon::detail::move_median_to_first(first, first + 1, mid, last - 1, comp);
	return hamon::detail::unguarded_partition(first + 1, last, first, comp);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_UNGUARDED_PARTITION_PIVOT_HPP
