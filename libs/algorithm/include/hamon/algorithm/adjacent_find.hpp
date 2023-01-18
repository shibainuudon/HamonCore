/**
 *	@file	adjacent_find.hpp
 *
 *	@brief	adjacent_find の定義
 */

#ifndef HAMON_ALGORITHM_ADJACENT_FIND_HPP
#define HAMON_ALGORITHM_ADJACENT_FIND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::adjacent_find;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		隣接する要素で条件を満たしている最初の要素を検索する
 *
 *	@tparam		ForwardIterator
 *	@tparam		BinaryPredicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内にあるイテレータ i について、
 *				pred(*i, *(i + 1)) != false であるような最初のイテレータを返す。
 *				もしそのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	与えられたシーケンスが空でない場合、
 *				正確に min((i - first) + 1, (last - first) - 1) 回
 *				（i は adjacent_find の戻り値）の述語が適用される
 */
template <
	typename ForwardIterator,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
adjacent_find(
	ForwardIterator first,
	ForwardIterator last,
	BinaryPredicate pred)
{
	if (first != last)
	{
		auto next_it = first;

		while (++next_it != last)
		{
			if (pred(*first, *next_it))
			{
				return first;
			}

			first = next_it;
		}
	}

	return last;
}

/**
 *	@brief		隣接する要素で条件を満たしている最初の要素を検索する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		[first,last) 内にあるイテレータ i について、
 *				*i == *(i + 1) であるような最初のイテレータを返す。
 *				もしそのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	与えられたシーケンスが空でない場合、
 *				正確に min((i - first) + 1, (last - first) - 1) 回
 *				（i は adjacent_find の戻り値）の比較が適用される
 */
template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last)
{
	return hamon::adjacent_find(
		first, last, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_ADJACENT_FIND_HPP
