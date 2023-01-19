/**
 *	@file	push_heap.hpp
 *
 *	@brief	push_heap の定義
 */

#ifndef HAMON_ALGORITHM_PUSH_HEAP_HPP
#define HAMON_ALGORITHM_PUSH_HEAP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::push_heap;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace detail
{

template <
	typename RandomAccessIterator,
	typename Distance,
	typename T,
	typename Compare
>
inline HAMON_CXX14_CONSTEXPR void
push_heap_impl(
	RandomAccessIterator first,
	Distance hole_index,
	Distance top_index,
	T value,
	Compare& comp)
{
	Distance parent = (hole_index - 1) / 2;
	while (hole_index > top_index && comp(*(first + parent), value))
	{
		*(first + hole_index) = std::move(*(first + parent));
		hole_index = parent;
		parent = (hole_index - 1) / 2;
	}
	*(first + hole_index) = std::move(value);
}

}	// namespace detail

/**
 *	@brief		ヒープ化された範囲に要素を追加したヒープ範囲を得る
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,last - 1) は有効な heap である必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		last - 1 の値を、[first,last) が有効な heap となるように配置する
 *
 *	@complexity	最大で log(last - first) 回比較する。
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using value_t = hamon::iter_value_t<RandomAccessIterator>;
	using difference_t = hamon::iter_difference_t<RandomAccessIterator>;

	value_t value = std::move(*(last - 1));
	hamon::detail::push_heap_impl(
		first,
		difference_t((last - first) - 1),
		difference_t(0),
		std::move(value),
		comp);
}

/**
 *	@brief		ヒープ化された範囲に要素を追加したヒープ範囲を得る
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	[first,last - 1) は有効な heap である必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		last - 1 の値を、[first,last) が有効な heap となるように配置する
 *
 *	@complexity	最大で log(last - first) 回比較する。
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR void
push_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	hamon::push_heap(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_PUSH_HEAP_HPP
