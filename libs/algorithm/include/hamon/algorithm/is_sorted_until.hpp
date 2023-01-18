/**
 *	@file	is_sorted_until.hpp
 *
 *	@brief	is_sorted_until の定義
 */

#ifndef HAMON_ALGORITHM_IS_SORTED_UNTIL_HPP
#define HAMON_ALGORITHM_IS_SORTED_UNTIL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::is_sorted_until;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		ソート済みか判定し、ソートされていない位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		distance(first, last) < 2 なら last を返す。
 *				そうでない場合、[first,last] の中でソートされている範囲を [first,i) としたとき、
 *				そのイテレータ i を返す。
 *
 *	@complexity	線形時間
 */
template <typename ForwardIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp)
{
	if (first != last)
	{
		auto next_it = first;

		while (++next_it != last)
		{
			if (comp(*next_it, *first))
			{
				return next_it;
			}

			first = next_it;
		}
	}

	return last;
}

/**
 *	@brief		ソート済みか判定し、ソートされていない位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		distance(first, last) < 2 なら last を返す。
 *				そうでない場合、[first,last] の中でソートされている範囲を [first,i) としたとき、
 *				そのイテレータ i を返す。
 *
 *	@complexity	線形時間
 */
template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
is_sorted_until(ForwardIterator first, ForwardIterator last)
{
	return hamon::is_sorted_until(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_IS_SORTED_UNTIL_HPP
