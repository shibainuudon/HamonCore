/**
 *	@file	is_heap.hpp
 *
 *	@brief	is_heap の定義
 */

#ifndef HAMON_ALGORITHM_IS_HEAP_HPP
#define HAMON_ALGORITHM_IS_HEAP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::is_heap;

}	// namespace hamon

#else

#include <hamon/algorithm/is_heap_until.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲がヒープ化されているか判定する
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		is_heap_until(first, last, comp) == last
 *
 *	@complexity	線形時間
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR bool
is_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	return hamon::is_heap_until(first, last, comp) == last;
}

/**
 *	@brief		範囲がヒープ化されているか判定する
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		is_heap_until(first, last) == last
 *
 *	@complexity	線形時間
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR bool
is_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	return hamon::is_heap(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_IS_HEAP_HPP
