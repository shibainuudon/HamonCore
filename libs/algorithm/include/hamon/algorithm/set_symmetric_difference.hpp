/**
 *	@file	set_symmetric_difference.hpp
 *
 *	@brief	set_symmetric_difference の定義
 */

#ifndef HAMON_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP
#define HAMON_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::set_symmetric_difference;

}	// namespace hamon

#else

#include <hamon/algorithm/copy.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		2つのソート済み範囲の互いに素な集合を得る
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		OutputIterator
 *	@tparam		Compare
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *	@param		comp
 *
 *	@require	結果の範囲は両方の入力の範囲と重なっていてはならない。
 *
 *	@effect		[first1,last1) から [first2,last2) に存在していない要素と、
 *				[first2,last2) から [first2,last2) に存在していない要素を result へコピーする。
 *				構築された要素はソートされている。
 *
 *	@return		構築された範囲の終端
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回の比較を行う
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
set_symmetric_difference(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2)
		{
			return hamon::copy(first1, last1, result);
		}

		if (comp(*first1, *first2))
		{
			*result = *first1;
			++result;
			++first1;
		}
		else
		{
			if (comp(*first2, *first1))
			{
				*result = *first2;
				++result;
			}
			else
			{
				++first1;
			}

			++first2;
		}
	}

	return hamon::copy(first2, last2, result);
}

/**
 *	@brief		2つのソート済み範囲の互いに素な集合を得る
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		OutputIterator
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *
 *	@require	結果の範囲は両方の入力の範囲と重なっていてはならない。
 *
 *	@effect		[first1,last1) から [first2,last2) に存在していない要素と、
 *				[first2,last2) から [first2,last2) に存在していない要素を result へコピーする。
 *				構築された要素はソートされている。
 *
 *	@return		構築された範囲の終端
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回の比較を行う
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
set_symmetric_difference(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result)
{
	return hamon::set_symmetric_difference(
		first1, last1, first2, last2, result, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP
