/**
 *	@file	move_backward.hpp
 *
 *	@brief	move_backward の定義
 */

#ifndef HAMON_ALGORITHM_MOVE_BACKWARD_HPP
#define HAMON_ALGORITHM_MOVE_BACKWARD_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::move_backward;

}	// namespace hamon

#else

#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された範囲の要素を後ろからムーブする
 *
 *	@tparam		BidirectionalIterator1
 *	@tparam		BidirectionalIterator2
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	result は (first,last] の範囲に含まれてはならない
 *
 *	@return		result - (last - first)
 *
 *	@effect		[first,last) 内にある要素を、それぞれ [result - (last-first),result) へムーブする。
 *				ムーブは last - 1 から順番に行い、1 以上 last - first 以下であるそれぞれの n について、
 *				*(result - n) = move(*(last - n)) を行う。
 *
 *	@complexity	正確に last - first 回ムーブ代入が行われる。
 *
 *	@note		last が [result - (last-first),result) の範囲内にあるときには、
 *				move() の代わりに move_backward() を使うべきである。
 */
template <typename BidirectionalIterator1, typename BidirectionalIterator2>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator2
move_backward(
	BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result)
{
	while (first != last)
	{
		*--result = hamon::move(*--last);
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MOVE_BACKWARD_HPP
