﻿/**
 *	@file	includes.hpp
 *
 *	@brief	includes の定義
 */

#ifndef HAMON_ALGORITHM_INCLUDES_HPP
#define HAMON_ALGORITHM_INCLUDES_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::includes;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		2つのソート済み範囲において、一方の範囲の要素がもう一方の範囲に全て含まれているかを判定する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		Compare
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		comp
 *
 *	@return		[first2,last2) が empty であるか、
 *				[first2,last2) の全ての要素が [first1,last1) に含まれている場合は true、
 *				そうでない場合は false を返す。
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回比較する
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
inline HAMON_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp)
{
	for (; first2 != last2; ++first1)
	{
		if (first1 == last1 || comp(*first2, *first1))
		{
			return false;
		}

		if (!comp(*first1, *first2))
		{
			++first2;
		}
	}

	return true;
}

/**
 *	@brief		2つのソート済み範囲において、一方の範囲の要素がもう一方の範囲に全て含まれているかを判定する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		[first2,last2) が empty であるか、
 *				[first2,last2) の全ての要素が [first1,last1) に含まれている場合は true、
 *				そうでない場合は false を返す。
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回比較する
 */
template <
	typename InputIterator1,
	typename InputIterator2
>
inline HAMON_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	return hamon::includes(
		first1, last1, first2, last2, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_INCLUDES_HPP
