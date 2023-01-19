/**
 *	@file	partial_sort.hpp
 *
 *	@brief	partial_sort の定義
 */

#ifndef HAMON_ALGORITHM_PARTIAL_SORT_HPP
#define HAMON_ALGORITHM_PARTIAL_SORT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::partial_sort;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/heap_select.hpp>
#include <hamon/algorithm/sort_heap.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲を部分的にソートし、先頭N個を並んだ状態にする。
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、middle - first 個の要素を
 *				ソート済みの状態で [first,middle) に配置する。
 *				残りの [middle,last) にある要素は unspecified order に配置される。
 *
 *	@complexity	ほぼ (last - first) * log(middle - first) 回の比較を行う
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	hamon::detail::heap_select(first, middle, last, comp);
	hamon::sort_heap(first, middle, comp);
}

/**
 *	@brief		範囲を部分的にソートし、先頭N個を並んだ状態にする。
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、middle - first 個の要素を
 *				ソート済みの状態で [first,middle) に配置する。
 *				残りの [middle,last) にある要素は unspecified order に配置される。
 *
 *	@complexity	ほぼ (last - first) * log(middle - first) 回の比較を行う
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last)
{
	return hamon::partial_sort(
		first, middle, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_PARTIAL_SORT_HPP
