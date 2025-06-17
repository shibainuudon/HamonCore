/**
 *	@file	stable_partition.hpp
 *
 *	@brief	stable_partition の定義
 */

#ifndef HAMON_ALGORITHM_STABLE_PARTITION_HPP
#define HAMON_ALGORITHM_STABLE_PARTITION_HPP

#include <algorithm>

#if defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 202306L)

namespace hamon
{

using std::stable_partition;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/stable_partition_impl.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

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
template <typename BidirectionalIterator, typename Predicate>
HAMON_CXX14_CONSTEXPR BidirectionalIterator
stable_partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
{
	return hamon::detail::stable_partition_impl(hamon::move(first), hamon::move(last), pred);
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_STABLE_PARTITION_HPP
