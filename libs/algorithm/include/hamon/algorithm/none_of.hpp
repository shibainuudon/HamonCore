/**
 *	@file	none_of.hpp
 *
 *	@brief	none_of の定義
 */

#ifndef HAMON_ALGORITHM_NONE_OF_HPP
#define HAMON_ALGORITHM_NONE_OF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::none_of;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲の全ての要素が条件を満たさないかを判定する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) が空であったり、[first,last) 内の全てのイテレータ i について
 *				 pred(*i) が false である場合は true を返し、そうでない場合は false を返す。
 *
 *	@complexity	最大で last - first 回 pred を実行する。
 */
template <typename InputIterator, typename Predicate>
inline HAMON_CXX14_CONSTEXPR bool
none_of(
	InputIterator first,
	InputIterator last,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			return false;
		}
	}

	return true;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_NONE_OF_HPP
