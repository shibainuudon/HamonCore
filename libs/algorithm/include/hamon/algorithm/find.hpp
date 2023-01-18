/**
 *	@file	find.hpp
 *
 *	@brief	find の定義
 */

#ifndef HAMON_ALGORITHM_FIND_HPP
#define HAMON_ALGORITHM_FIND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::find;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された値を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@return		[first,last) 内のイテレータ i について、*i == value であるような最初のイテレータを返す。
 *				そのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	最大で last - first 回比較を行う
 */
template <typename InputIterator, typename T>
inline HAMON_CXX14_CONSTEXPR InputIterator
find(
	InputIterator first,
	InputIterator last,
	T const& value)
{
	for (; first != last; ++first)
	{
		if (*first == value)
		{
			break;
		}
	}

	return first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FIND_HPP
