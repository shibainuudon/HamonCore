/**
 *	@file	unique.hpp
 *
 *	@brief	unique の定義
 */

#ifndef HAMON_ALGORITHM_UNIQUE_HPP
#define HAMON_ALGORITHM_UNIQUE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::unique;

}	// namespace hamon

#else

#include <hamon/algorithm/adjacent_find.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		重複した要素を取り除く
 *
 *	@tparam		ForwardIterator
 *	@tparam		BinaryPredicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	*first は MoveAssignable の要求を満たす必要がある。
 *				比較関数は equivalence relation でなければならない。
 *
 *	@effect		[first,last) が空の範囲でない場合、
 *				[first + 1,last) 内のイテレータ i について、
 *				pred(*(i - 1), *i) != false による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭以外を削除する。
 *
 *	@return		結果の範囲の終端を返す
 *
 *	@complexity	[first,last) が空の範囲でない場合、
 *				正確に last - first - 1 回の述語の適用を行う
 */
template <
	typename ForwardIterator,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
unique(
	ForwardIterator first,
	ForwardIterator last,
	BinaryPredicate pred)
{
	first = hamon::adjacent_find(first, last, pred);

	if (first != last)
	{
		// ...  a  a  ?  ...
		//      f     i
		auto i = first;
		for (++i; ++i != last;)
		{
			if (!pred(*first, *i))
			{
				*++first = std::move(*i);
			}
		}

		++first;
	}

	return first;
}

/**
 *	@brief		重複した要素を取り除く
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	*first は MoveAssignable の要求を満たす必要がある。
 *				比較関数は equivalence relation でなければならない。
 *
 *	@effect		[first,last) が空の範囲でない場合、
 *				[first + 1,last) 内のイテレータ i について、
 *				*(i - 1) == *i による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭以外を削除する。
 *
 *	@return		結果の範囲の終端を返す
 *
 *	@complexity	[first,last) が空の範囲でない場合、
 *				正確に last - first - 1 回の比較を行う
 */
template <typename ForwardIterator>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
unique(ForwardIterator first, ForwardIterator last)
{
	return hamon::unique(
		first, last, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_UNIQUE_HPP
