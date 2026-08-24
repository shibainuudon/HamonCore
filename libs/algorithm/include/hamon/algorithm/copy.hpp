/**
 *	@file	copy.hpp
 *
 *	@brief	copy の定義
 */

#ifndef HAMON_ALGORITHM_COPY_HPP
#define HAMON_ALGORITHM_COPY_HPP

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
