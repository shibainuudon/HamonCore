/**
 *	@file	stable_partition.hpp
 *
 *	@brief	stable_partition の定義
 */

#ifndef HAMON_ALGORITHM_STABLE_PARTITION_HPP
#define HAMON_ALGORITHM_STABLE_PARTITION_HPP

#include <algorithm>

namespace hamon
{

/**
 *	@brief		与えられた範囲を相対順序を保ちながら条件によって区分化する。
 *
 *	@tparam		BidirectionalIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	BidirectionalIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) 内にある pred を満たす全ての要素を、pred を満たさない全ての要素より前に移動させる。
 *
 *	@return		[first,i) 内にあるイテレータ j について pred(*j) != false を満たし、
 *				[i,last) 内にあるイテレータ k について pred(*k) == false を満たすような、
 *				イテレータ i を返す。
 *				つまり、区分化された境界を指すイテレータを返す。
 *
 *	@complexity	最大で (last - first) * log(last - first) 回 swap が行われる。
 *				正確に last - first 回述語が適用される。
 *
 *	@note		条件を満たす・満たさない両グループ内での要素間の相対順序は保たれる。
 */
using std::stable_partition;

}	// namespace hamon

#endif // HAMON_ALGORITHM_STABLE_PARTITION_HPP
