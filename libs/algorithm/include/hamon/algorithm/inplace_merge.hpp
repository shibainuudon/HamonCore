/**
 *	@file	inplace_merge.hpp
 *
 *	@brief	inplace_merge の定義
 */

#ifndef HAMON_ALGORITHM_INPLACE_MERGE_HPP
#define HAMON_ALGORITHM_INPLACE_MERGE_HPP

#include <algorithm>

#if defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 202306L)

namespace hamon
{

using std::inplace_merge;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/inplace_merge_impl.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

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
template <typename BidirectionalIterator, typename Compare>
HAMON_CXX14_CONSTEXPR void
inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Compare comp)
{
	hamon::detail::inplace_merge_impl(hamon::move(first), hamon::move(middle), hamon::move(last), comp);
}

template <typename BidirectionalIterator>
HAMON_CXX14_CONSTEXPR void
inplace_merge(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last)
{
	hamon::detail::inplace_merge_impl(hamon::move(first), hamon::move(middle), hamon::move(last), hamon::less<>{});
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_INPLACE_MERGE_HPP
