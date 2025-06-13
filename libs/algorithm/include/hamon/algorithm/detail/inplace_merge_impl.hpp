/**
 *	@file	inplace_merge_impl.hpp
 *
 *	@brief	inplace_merge_impl の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_INPLACE_MERGE_IMPL_HPP
#define HAMON_ALGORITHM_DETAIL_INPLACE_MERGE_IMPL_HPP

#include <hamon/algorithm/iter_swap.hpp>
#include <hamon/algorithm/lower_bound.hpp>
#include <hamon/algorithm/rotate.hpp>
#include <hamon/algorithm/upper_bound.hpp>
#include <hamon/iterator/advance.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename BidirectionalIterator, typename Distance, typename Compare>
HAMON_CXX14_CONSTEXPR void
inplace_merge_without_buffer(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Distance len1,
	Distance len2,
	Compare comp)
{
	if (len1 == 0 || len2 == 0)
	{
		return;
	}

	if (len1 + len2 == 2)
	{
		if (comp(*middle, *first))
		{
			hamon::iter_swap(first, middle);
		}
		return;
	}

	BidirectionalIterator first_cut = first;
	BidirectionalIterator second_cut = middle;
	Distance len11 = 0;
	Distance len22 = 0;
	if (len1 > len2)
	{
		len11 = len1 / 2;
		hamon::advance(first_cut, len11);
		second_cut = hamon::lower_bound(middle, last, *first_cut, comp);
		len22 = hamon::distance(middle, second_cut);
	}
	else
	{
		len22 = len2 / 2;
		hamon::advance(second_cut, len22);
		first_cut = hamon::upper_bound(first, middle, *second_cut, comp);
		len11 = hamon::distance(first, first_cut);
	}

	BidirectionalIterator new_middle = hamon::rotate(first_cut, middle, second_cut);
	hamon::detail::inplace_merge_without_buffer(first, first_cut, new_middle, len11, len22, comp);
	hamon::detail::inplace_merge_without_buffer(new_middle, second_cut, last, len1 - len11, len2 - len22, comp);
}

template <typename BidirectionalIterator, typename Compare>
HAMON_CXX14_CONSTEXPR void
inplace_merge_impl(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Compare comp)
{
	if (first == middle || middle == last)
	{
		return;
	}

	auto const len1 = hamon::distance(first, middle);
	auto const len2 = hamon::distance(middle, last);

	return hamon::detail::inplace_merge_without_buffer(first, middle, last, len1, len2, comp);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_INPLACE_MERGE_IMPL_HPP
