/**
 *	@file	swap_ranges.hpp
 *
 *	@brief	swap_ranges の定義
 */

#ifndef HAMON_ALGORITHM_SWAP_RANGES_HPP
#define HAMON_ALGORITHM_SWAP_RANGES_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::swap_ranges;

}	// namespace hamon

#else

#include <hamon/algorithm/iter_swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された2つの範囲同士を swap する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *
 *	以下、last1 - first1 を N とする。
 *
 *	@return		first2 + N
 *
 *	@require	[first1,last1) と [first2,first2 + N) の範囲が重なってはならない。
 *				0 以上 N 未満のそれぞれの n について、
 *				*(first1 + n) と *(first2 + n) は Swappable でなければならない。
 *
 *	@effect		0 以上 N 以下のそれぞれの n について
 *				swap(*(first1 + n), *(first2 + n)) を行う
 *
 *	@complexity	正確に N 回のスワップが行われる
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator2
swap_ranges(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2)
{
	while (first1 != last1)
	{
		hamon::iter_swap(first1++, first2++);
	}

	return first2;
}

}	// namespace hamon

#endif

#include <hamon/algorithm/iter_swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された2つの範囲同士を swap する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	以下、min(last1 - first1, last2 - first2) を N とする。
 *
 *	@return		first2 + N
 *
 *	@require	[first1,last1) と [first2,last2) の範囲が重なってはならない。
 *				0 以上 N 未満のそれぞれの n について、
 *				*(first1 + n) と *(first2 + n) は Swappable でなければならない。
 *
 *	@effect		0 以上 N 以下のそれぞれの n について
 *				swap(*(first1 + n), *(first2 + n)) を行う
 *
 *	@complexity	正確に N 回のスワップが行われる
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator2
swap_ranges(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2)
{
	while (first1 != last1 && first2 != last2)
	{
		hamon::iter_swap(first1++, first2++);
	}

	return first2;
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_SWAP_RANGES_HPP
