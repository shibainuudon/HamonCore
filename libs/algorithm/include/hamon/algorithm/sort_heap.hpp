/**
 *	@file	sort_heap.hpp
 *
 *	@brief	sort_heap の定義
 */

#ifndef HAMON_ALGORITHM_SORT_HEAP_HPP
#define HAMON_ALGORITHM_SORT_HEAP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::sort_heap;

}	// namespace hamon

#else

#include <hamon/algorithm/pop_heap.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		ヒープ化された範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,last) は有効なヒープである必要がある。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		ヒープ化されている [first,last) をソートする
 *
 *	@complexity	最大で N log(N) 回比較する（N == last - first）
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	while (last - first > 1)
	{
		--last;
		hamon::detail::pop_heap_impl(first, last, last, comp);
	}
}

/**
 *	@brief		ヒープ化された範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	[first,last) は有効なヒープである必要がある。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		ヒープ化されている [first,last) をソートする
 *
 *	@complexity	最大で N log(N) 回比較する（N == last - first）
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	hamon::sort_heap(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SORT_HEAP_HPP
