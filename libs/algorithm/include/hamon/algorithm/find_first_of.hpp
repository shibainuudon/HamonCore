/**
 *	@file	find_first_of.hpp
 *
 *	@brief	find_first_of の定義
 */

#ifndef HAMON_ALGORITHM_FIND_FIRST_OF_HPP
#define HAMON_ALGORITHM_FIND_FIRST_OF_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::find_first_of;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		ある集合の1つとマッチする最初の要素を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		ForwardIterator
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		pred
 *
 *	@return		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *				[first2,last2) 内のイテレータ j について、
 *				どれかが pred(*i,*j) であるような最初のイテレータを返す。
 *				そのようなイテレータが見つからない、もしくは [first2,last2) が空である場合は last1 を返す。
 *
 *	@complexity	最大で (last1 - first1) * (last2 - first2) 回の、対応する述語が適用される。
 */
template <
	typename InputIterator,
	typename ForwardIterator,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR InputIterator
find_first_of(
	InputIterator   first1, InputIterator   last1,
	ForwardIterator first2, ForwardIterator last2,
	BinaryPredicate pred)
{
	for (; first1 != last1; ++first1)
	{
		for (auto it = first2; it != last2; ++it)
		{
			if (pred(*first1, *it))
			{
				return first1;
			}
		}
	}

	return last1;
}

/**
 *	@brief		ある集合の1つとマッチする最初の要素を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		ForwardIterator
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *				[first2,last2) 内のイテレータ j について、
 *				どれかが *i == *j であるような最初のイテレータを返す。
 *				そのようなイテレータが見つからない、もしくは [first2,last2) が空である場合は last1 を返す。
 *
 *	@complexity	最大で (last1 - first1) * (last2 - first2) 回の、対応する比較が適用される。
 */
template <
	typename InputIterator,
	typename ForwardIterator
>
inline HAMON_CXX14_CONSTEXPR InputIterator
find_first_of(
	InputIterator   first1, InputIterator   last1,
	ForwardIterator first2, ForwardIterator last2)
{
	return hamon::find_first_of(
		first1, last1, first2, last2, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FIND_FIRST_OF_HPP
