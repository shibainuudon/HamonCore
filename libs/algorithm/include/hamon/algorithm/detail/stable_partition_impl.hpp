/**
 *	@file	stable_partition_impl.hpp
 *
 *	@brief	stable_partition_impl の実装
 */

#ifndef HAMON_ALGORITHM_DETAIL_STABLE_PARTITION_IMPL_HPP
#define HAMON_ALGORITHM_DETAIL_STABLE_PARTITION_IMPL_HPP

#include <hamon/algorithm/rotate.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Predicate, typename BidirectionalIterator>
HAMON_CXX14_CONSTEXPR BidirectionalIterator
stable_partition_impl_2(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Predicate pred)
{
	auto const len = hamon::ranges::distance(first, last) + 1;
	auto const mid = hamon::ranges::next(first, len / 2);

	BidirectionalIterator left = mid;
	for (;;)
	{
		--left;

		if (first == left)
		{
			break;
		}

		if (pred(*left))
		{
			left = hamon::detail::stable_partition_impl_2(first, left, pred);
			break;
		}
	}

	BidirectionalIterator right = mid;
	for (;;)
	{
		if (right == last)
		{
			++right;
			break;
		}

		if (!pred(*right))
		{
			right = hamon::detail::stable_partition_impl_2(right, last, pred);
			break;
		}

		++right;
	}

	return hamon::rotate(left, mid, right);
}

template <typename BidirectionalIterator, typename Predicate>
HAMON_CXX14_CONSTEXPR BidirectionalIterator
stable_partition_impl(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
{
	for (;;)
	{
		if (first == last)
		{
			return first;
		}

		if (!pred(*first))
		{
			break;
		}

		++first;
	}

	for (;;)
	{
		--last;

		if (first == last)
		{
			return first;
		}

		if (pred(*last))
		{
			break;
		}
	}

	return hamon::detail::stable_partition_impl_2(first, last, pred);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ALGORITHM_DETAIL_STABLE_PARTITION_IMPL_HPP
