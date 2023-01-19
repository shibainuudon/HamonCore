/**
 *	@file	pop_heap.hpp
 *
 *	@brief	pop_heap の定義
 */

#ifndef HAMON_ALGORITHM_POP_HEAP_HPP
#define HAMON_ALGORITHM_POP_HEAP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::pop_heap;

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

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
pop_heap_impl(
	RandomAccessIterator first,
	RandomAccessIterator last,
	RandomAccessIterator result,
	Compare& comp)
{
	using value_t = hamon::iter_value_t<RandomAccessIterator>;
	using difference_t = hamon::iter_difference_t<RandomAccessIterator>;

	value_t value = std::move(*result);
	*result = std::move(*first);
	hamon::detail::adjust_heap(
		first,
		difference_t(0),
		difference_t(last - first),
		std::move(value),
		comp);
}

}	// namespace detail

/**
 *	@brief		ヒープ化された範囲の先頭と末尾を入れ替え、ヒープ範囲を作り直す
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,last) は空でない heap でなければならない。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		first にある値を last - 1 と交換し、その後 [first,last - 1) が有効な heap となるように配置する。
 *
 *	@complexity	最大で 2 * log(last - first) 回比較する
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	if (last - first > 1)
	{
		--last;
		hamon::detail::pop_heap_impl(first, last, last, comp);
	}
}

/**
 *	@brief		ヒープ化された範囲の先頭と末尾を入れ替え、ヒープ範囲を作り直す
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	[first,last) は空でない heap でなければならない。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		first にある値を last - 1 と交換し、その後 [first,last - 1) が有効な heap となるように配置する。
 *
 *	@complexity	最大で 2 * log(last - first) 回比較する
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	hamon::pop_heap(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_POP_HEAP_HPP
