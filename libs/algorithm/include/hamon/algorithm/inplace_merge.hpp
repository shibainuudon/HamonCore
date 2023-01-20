/**
 *	@file	inplace_merge.hpp
 *
 *	@brief	inplace_merge の定義
 */

#ifndef HAMON_ALGORITHM_INPLACE_MERGE_HPP
#define HAMON_ALGORITHM_INPLACE_MERGE_HPP

#include <algorithm>

namespace hamon
{

/**
 *	@brief		2つの連続したソート済み範囲をマージする
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,middle) と [middle,last) の範囲はそれぞれ comp でソートされていること。
 *				BidirectionalIterator は ValueSwappable の要件を満たしていること。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしていること。
 *
 *	@effect		[first,middle), [middle,last) という、連続した２つの範囲をマージし、結果を [first,last) へ格納する。
 *				結果の範囲 [first,last) は昇順になる。
 *				つまり、first を除く [first,last) 内の全てのイテレータ i について、
 *				comp(*i, *(i - 1)) が false になる。
 *
 *	@complexity	N log(N) （N は last - first）回程度比較する
 */
using std::inplace_merge;

}	// namespace hamon

#endif // HAMON_ALGORITHM_INPLACE_MERGE_HPP
