/**
 *	@file	find_if.hpp
 *
 *	@brief	find_if の定義
 */

#ifndef HAMON_ALGORITHM_FIND_IF_HPP
#define HAMON_ALGORITHM_FIND_IF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::find_if;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲の中から、指定された条件を満たす最初の要素を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について、pred(*i) != false である最初のイテレータを返す。
 *				そのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	最大で last - first 回述語による比較を行う
 */
template <typename InputIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR InputIterator
find_if(
	InputIterator first,
	InputIterator last,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			break;
		}
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FIND_IF_HPP
