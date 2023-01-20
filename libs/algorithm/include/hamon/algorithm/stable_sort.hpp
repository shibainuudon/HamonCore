/**
 *	@file	stable_sort.hpp
 *
 *	@brief	stable_sort の定義
 */

#ifndef HAMON_ALGORITHM_STABLE_SORT_HPP
#define HAMON_ALGORITHM_STABLE_SORT_HPP

#include <algorithm>

namespace hamon
{

/**
 *	@brief		範囲を安定ソートで並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	最大で N log^2(N) （N == last - first）回の比較を行う。
 *				ただし、十分なメモリがあれば N log(N) になる。
 */
using std::stable_sort;

}	// namespace hamon

#endif // HAMON_ALGORITHM_STABLE_SORT_HPP
