/**
 *	@file	reverse_copy.hpp
 *
 *	@brief	reverse_copy の定義
 */

#ifndef HAMON_ALGORITHM_REVERSE_COPY_HPP
#define HAMON_ALGORITHM_REVERSE_COPY_HPP

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		要素の並びを逆にし、その結果を出力の範囲へコピーする
 *
 *	@tparam		BidirectionalIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	[first,last) と [result,result+(last-first)) は領域が重なっていてはならない。
 *
 *	@effect		0 以上 last - first 未満の整数 i について、
 *				*(result + (last - first) -1 - i) = *(first + i) を行うことで、
 *				[first,last) の範囲を [result,result+(last-first)) へコピーする。
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に last - first 回代入する
 */
template <
	typename BidirectionalIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
reverse_copy(
	BidirectionalIterator first,
	BidirectionalIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*result++ = *--last;
	}

	return result;
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_REVERSE_COPY_HPP
