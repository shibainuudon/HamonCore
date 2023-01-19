/**
 *	@file	remove_copy_if.hpp
 *
 *	@brief	remove_copy_if の定義
 */

#ifndef HAMON_ALGORITHM_REMOVE_COPY_IF_HPP
#define HAMON_ALGORITHM_REMOVE_COPY_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::remove_copy_if;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		条件を満たす要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		pred
 *
 *	@require	[first,last) と [result,result + (last - first) は重なってはならない。
 *				*result = *first という式が有効でなければならない。
 *
 *	@return		実行結果の範囲の終端を返す
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				pred(*i) != false でない要素を result へコピーする
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 *
 *	@note		安定。
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
remove_copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (!pred(*first))
		{
			*result++ = *first;
		}
	}

	return result;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_REMOVE_COPY_IF_HPP
