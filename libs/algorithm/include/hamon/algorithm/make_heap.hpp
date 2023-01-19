/**
 *	@file	make_heap.hpp
 *
 *	@brief	make_heap の定義
 */

#ifndef HAMON_ALGORITHM_MAKE_HEAP_HPP
#define HAMON_ALGORITHM_MAKE_HEAP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::make_heap;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/adjust_heap.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		範囲をヒープ化する
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	*first の型は MoveConstructible と MoveAssignable の要件を満たしていること
 *
 *	@effect		[first,last) の範囲で heap を構築する
 *
 *	@complexity	最大で 3 * (last - first) 回比較する
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	using value_t = hamon::iter_value_t<RandomAccessIterator>;
	using difference_t = hamon::iter_difference_t<RandomAccessIterator>;

	if (last - first < 2)
	{
		return;
	}

	const difference_t len = last - first;
	difference_t parent = (len - 2) / 2;
	for (;;)
	{
		value_t value = std::move(*(first + parent));
		hamon::detail::adjust_heap(first, parent, len, std::move(value), comp);

		if (parent == 0)
		{
			return;
		}

		parent--;
	}
}

/**
 *	@brief		範囲をヒープ化する
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	*first の型は MoveConstructible と MoveAssignable の要件を満たしていること
 *
 *	@effect		[first,last) の範囲で heap を構築する
 *
 *	@complexity	最大で 3 * (last - first) 回比較する
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR void
make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	hamon::make_heap(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MAKE_HEAP_HPP
