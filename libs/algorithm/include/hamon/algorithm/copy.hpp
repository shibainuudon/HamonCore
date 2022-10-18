/**
 *	@file	copy.hpp
 *
 *	@brief	copy の定義
 */

#ifndef HAMON_ALGORITHM_COPY_HPP
#define HAMON_ALGORITHM_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) &&	\
	!(defined(HAMON_MSVC) && (HAMON_MSVC == 1930) && (HAMON_MSVC_FULL_VER <= 193030705))

// 以下のコード
// char a[] { 1, 2, 3 };
// hamon::copy(a+1, a+3, a);
// で、
// Visual Studio 2022 Version 17.0.(0-1) かつ、
// Releaseビルドかつ、
// 実行時(非constexpr)
// のときのみ、a[0]の値が想定通りにならない。
// Visual Studio 2022 のバグと思われる。
// (配列の型を変えると大丈夫な時があったりする。int型は大丈夫なときが多い)

#include <algorithm>

namespace hamon
{

using std::copy;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された範囲の要素をコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	result は [first,last) の範囲に含まれてはならない
 *
 *	@return		result + (last - first)
 *
 *	@effect		[first,last) 内の要素を、それぞれ [result,result + (last - first)) へコピーする。
 *				コピーは first から順番に行い、0 以上 last - first 未満であるそれぞれの n について、
 *				*(result + n) = *(first + n) を行う
 *
 *	@complexity	正確に last - first 回代入が行われる。
 */
template <
	typename InputIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*result++ = *first++;
	}

	return result;
}

}	// namespace hamon

#endif

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief
 */
template <
	typename InputIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result_first,
	OutputIterator result_last)
{
	while (first != last && result_first != result_last)
	{
		*result_first++ = *first++;
	}

	return result_first;
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_COPY_HPP
