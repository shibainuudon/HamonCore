/**
 *	@file	binary_search.hpp
 *
 *	@brief	binary_search の定義
 */

#ifndef HAMON_ALGORITHM_BINARY_SEARCH_HPP
#define HAMON_ALGORITHM_BINARY_SEARCH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::binary_search;

}	// namespace hamon

#else

#include <hamon/algorithm/lower_bound.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		二分探索法による検索を行う
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *	@param		comp
 *
 *	@require	[first,last) の要素 e は comp(e, value) および !comp(value, e) によって区分化されていなければならない。
 *				また、[first, last) の全ての要素 e は、comp(e, value) であれば !comp(value, e) である必要がある。
 *
 *	@return		[first,last) 内のイテレータ i について、
 *				comp(*i, value) == false && comp(value, *i) == false であるようなイテレータが見つかった場合は true を返す。
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <typename ForwardIterator, typename T, typename Compare>
inline HAMON_CXX14_CONSTEXPR bool
binary_search(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	first = hamon::lower_bound(first, last, value, comp);
	return first != last && !comp(value, *first);
}

/**
 *	@brief		二分探索法による検索を行う
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	[first,last) の要素 e は e < value および !(value < e) によって区分化されていなければならない。
 *				また、[first, last) の全ての要素 e は、e < value であれば !(value < e) である必要がある。
 *
 *	@return		[first,last) 内のイテレータ i について、
 *				!(*i < value) && !(value < *i) であるようなイテレータが見つかった場合は true を返す。
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <typename ForwardIterator, typename T>
inline HAMON_CXX14_CONSTEXPR bool
binary_search(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return hamon::binary_search(
		first, last, value, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_BINARY_SEARCH_HPP
