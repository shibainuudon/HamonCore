/**
 *	@file	move.hpp
 *
 *	@brief	move の定義
 */

#ifndef HAMON_ALGORITHM_MOVE_HPP
#define HAMON_ALGORITHM_MOVE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

template <
	typename InputIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
move(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	return std::move(first, last, result);
}

}	// namespace hamon

#else

#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された範囲の要素をムーブする
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
 *	@effect		[first,last) 内の要素を、それぞれ [result,result + (last - first)) へムーブする。
 *				ムーブは first から順番に行い、0 以上 last - first 未満であるそれぞれの n について、
 *				*(result + n) = move(*(first + n)) を行う
 *
 *	@complexity	正確に last - first 回ムーブ代入が行われる。
 */
template <
	typename InputIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
move(
	InputIterator first,
	InputIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*result++ = hamon::move(*first++);
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MOVE_HPP
