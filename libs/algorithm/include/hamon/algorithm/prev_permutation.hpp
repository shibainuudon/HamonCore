/**
 *	@file	prev_permutation.hpp
 *
 *	@brief	prev_permutation の定義
 */

#ifndef HAMON_ALGORITHM_PREV_PERMUTATION_HPP
#define HAMON_ALGORITHM_PREV_PERMUTATION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::prev_permutation;

}	// namespace hamon

#else

#include <hamon/algorithm/reverse.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		前の順列を生成する
 *
 *	@tparam		BidirectionalIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	BidriectionalIteratorがValueSwappableの要件を満たしていること。
 *
 *	@effect		[first, last)の範囲を前の順列に変換する。
 *				compによって辞書順に並んでいる全ての順列の集合があると仮定すると、
 *				前の順列が発見される。
 *
 *	@return		前の順列が存在する場合はtrueを返し、そうでなければfalseを返す。
 *
 *	@complexity	高々(last - first)/2回の要素の交換
 */
template <typename BidirectionalIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR bool
prev_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Compare comp)
{
	auto i = last;

	if (first == last || first == --i)
	{
		return false;
	}

	for (;;)
	{
		auto ip1 = i;

		if (comp(*ip1, *--i))
		{
			auto j = last;

			while (!comp(*--j, *i))
			{
				;
			}

			hamon::ranges::swap(*i, *j);
			hamon::reverse(ip1, last);
			return true;
		}

		if (i == first)
		{
			hamon::reverse(first, last);
			return false;
		}
	}
}

/**
 *	@brief		前の順列を生成する
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	BidriectionalIteratorがValueSwappableの要件を満たしていること。
 *
 *	@effect		[first, last)の範囲を前の順列に変換する。
 *				operator<によって辞書順に並んでいる全ての順列の集合があると仮定すると、
 *				前の順列が発見される。
 *
 *	@return		前の順列が存在する場合はtrueを返し、そうでなければfalseを返す。
 *
 *	@complexity	高々(last - first)/2回の要素の交換
 */
template <typename BidirectionalIterator>
inline HAMON_CXX14_CONSTEXPR bool
prev_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	return hamon::prev_permutation(
		first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_PREV_PERMUTATION_HPP
