/**
 *	@file	remove_copy.hpp
 *
 *	@brief	remove_copy の定義
 */

#ifndef HAMON_ALGORITHM_REMOVE_COPY_HPP
#define HAMON_ALGORITHM_REMOVE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::remove_copy;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief	指定された要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		value
 *
 *	@require	[first,last) と [result,result + (last - first) は重なってはならない。
 *				*result = *first という式が有効でなければならない。
 *
 *	@return		実行結果の範囲の終端を返す
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				*i == value でない要素を result へコピーする
 *
 *	@complexity	正確に last - first 回の比較を行う
 *
 *	@note		安定。
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename T
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
remove_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T const& value)
{
	for (; first != last; ++first)
	{
		if (!(*first == value))
		{
			*result++ = *first;
		}
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REMOVE_COPY_HPP
