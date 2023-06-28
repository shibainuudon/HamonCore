/**
 *	@file	any_of.hpp
 *
 *	@brief	any_of の定義
 */

#ifndef HAMON_ALGORITHM_ANY_OF_HPP
#define HAMON_ALGORITHM_ANY_OF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::any_of;

}	// namespace hamon

#else

#include <hamon/iterator/next.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲のいずれかの要素が条件を満たすかを判定する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について
 *				pred(*i) が true になるような要素があればtrueを返し、
 *				そうでなければfalseを返す。 
 *				[first,last)の範囲が空の場合はfalseを返す。
 *
 *	@complexity	最大で last - first 回 pred を実行する。
 */
template <typename InputIterator, typename Predicate>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
any_of(InputIterator first, InputIterator last, Predicate pred)
{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			return true;
		}
	}

	return false;
#else
	return first != last &&
		(pred(*first) || hamon::any_of(hamon::next(first), last, pred));
#endif
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_ANY_OF_HPP
