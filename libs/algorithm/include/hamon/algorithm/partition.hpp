/**
 *	@file	partition.hpp
 *
 *	@brief	partition の定義
 */

#ifndef HAMON_ALGORITHM_PARTITION_HPP
#define HAMON_ALGORITHM_PARTITION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::partition;

}	// namespace hamon

#else

#include <hamon/concepts/swap.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/config.hpp>
#include <iterator>

namespace hamon
{

namespace detail
{

template <typename Predicate, typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
partition_impl(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred,
	hamon::forward_iterator_tag const*)
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

	for (auto p = first; ++p != last;)
	{
		if (pred(*p))
		{
			hamon::ranges::swap(*first, *p);
			++first;
		}
	}

	return first;
}

template <typename Predicate, typename BidirectionalIterator>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator
partition_impl(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Predicate pred,
	hamon::bidirectional_iterator_tag const*)
{
	for (;;)
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
		do
		{
			if (first == --last)
			{
				return first;
			}
		}
		while (!pred(*last));

		hamon::ranges::swap(*first, *last);
		++first;
	}
}

}	// namespace detail

/**
 *	@brief		与えられた範囲を条件によって区分化する。
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	ForwardIterator は ValueSwappable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) 内にある pred を満たす全ての要素を、
 *				pred を満たさない全ての要素より前に移動させる。
 *
 *	@return		[first,i) 内にあるイテレータ j について pred(*j) != false を満たし、
 *				[i,last) 内にあるイテレータ k について pred(*k) == false を満たすような、
 *				イテレータ i を返す。
 *				つまり、区分化された境界を指すイテレータを返す。
 *
 *	@complexity	ForwardIterator が BidirectionalIterator の要求を満たしている場合、
 *				最大で (last - first) / 2 回 swap される。
 *				そうでない場合、最大で last - first 回 swap される。
 *				正確に last - first 回述語が適用される。
 */
template <typename ForwardIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
partition(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	using Category = hamon::iterator_category<ForwardIterator>*;
	return hamon::detail::partition_impl(
		first, last, pred, Category());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_PARTITION_HPP
