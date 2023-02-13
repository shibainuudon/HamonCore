/**
 *	@file	sort.hpp
 *
 *	@brief	sort の定義
 */

#ifndef HAMON_ALGORITHM_SORT_HPP
#define HAMON_ALGORITHM_SORT_HPP

#include <algorithm>

namespace hamon
{

/**
 *	@brief		範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	N log N (N == last - first) 回の比較
 */
using std::sort;

}	// namespace hamon

#endif // HAMON_ALGORITHM_SORT_HPP
