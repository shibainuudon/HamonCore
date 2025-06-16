/**
 *	@file	next_permutation.hpp
 *
 *	@brief	next_permutation の定義
 */

#ifndef HAMON_ALGORITHM_NEXT_PERMUTATION_HPP
#define HAMON_ALGORITHM_NEXT_PERMUTATION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::next_permutation;

}	// namespace hamon

#else

#include <hamon/algorithm/reverse.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>

namespace hamon
{

/**
 *	@brief		次の順列を生成する
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
 *	@effect		[first, last)の範囲を次の順列に変換する。
 *				compによって辞書順に並んでいる全ての順列の集合があると仮定すると、
 *				次の順列が発見される。
 *
 *	@return		次の順列が存在する場合はtrueを返し、そうでなければfalseを返す。
 *
 *	@complexity	高々(last - first)/2回の要素の交換
 */
template <typename BidirectionalIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR bool
next_permutation(
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

		if (comp(*--i, *ip1))
		{
			auto j = last;
			while (!comp(*i, *--j))
			{
				;
			}

			hamon::ranges::iter_swap(i, j);
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
 *	@brief		次の順列を生成する
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	BidriectionalIteratorがValueSwappableの要件を満たしていること。
 *
 *	@effect		[first, last)の範囲を次の順列に変換する。
 *				operator<によって辞書順に並んでいる全ての順列の集合があると仮定すると、
 *				次の順列が発見される。
 *
 *	@return		次の順列が存在する場合はtrueを返し、そうでなければfalseを返す。
 *
 *	@complexity	高々(last - first)/2回の要素の交換
 */
template <typename BidirectionalIterator>
inline HAMON_CXX14_CONSTEXPR bool
next_permutation(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	return hamon::next_permutation(
		first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_NEXT_PERMUTATION_HPP
