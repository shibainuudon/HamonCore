/**
 *	@file	rotate_copy.hpp
 *
 *	@brief	rotate_copy の定義
 */

#ifndef HAMON_ALGORITHM_ROTATE_COPY_HPP
#define HAMON_ALGORITHM_ROTATE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::rotate_copy;

}	// namespace hamon

#else

#include <hamon/algorithm/copy.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		要素の並びを回転させ、その結果を出力の範囲へコピーする。
 *
 *	@tparam		ForwardIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *	@param		result
 *
 *	@require	[first,last) と [result,result + (last - first)) の範囲は重なっていてはならない。
 *
 *	@effect		0 以上 last - first 未満の整数 i について、
 *				*(result + i) = *(first + (i + (middle - first)) % (last - first)) という操作によって
 *				[first,last) の範囲を [result,result + (last - first)) の範囲へコピーする
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に last - first 回代入する。
 */
template <typename ForwardIterator, typename OutputIterator>
inline HAMON_CXX14_CONSTEXPR OutputIterator
rotate_copy(
	ForwardIterator first,
	ForwardIterator middle,
	ForwardIterator last,
	OutputIterator result)
{
	return hamon::copy(
		first,
		middle,
		hamon::copy(
			middle,
			last,
			result
		)
	);
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_ROTATE_COPY_HPP
