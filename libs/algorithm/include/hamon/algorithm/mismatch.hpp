/**
 *	@file	mismatch.hpp
 *
 *	@brief	mismatch の定義
 */

#ifndef HAMON_ALGORITHM_MISMATCH_HPP
#define HAMON_ALGORITHM_MISMATCH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::mismatch;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

/**
 *	@brief		2つのシーケンスが一致していない場所を検索する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		pred
 *
 *	@return		last2が渡されなかった場合は、last2 = first2 + (last1 - first1)とする。
 *				[first1,last1) 内にあるイテレータ i と、
 *				j == first2 + (i - first1) であるイテレータ j について、
 *				jが範囲[first2, last2)に含まれており、
 *				!(*i == *j) もしくは pred(*i, *j) == false であるような、最初のイテレータのペアを返す。
 *				そのようなイテレータが見つからなかった場合は
 *				last1 と first2 + (last1 - first1) のペアを返す。
 *
 *	@complexity	最大で last1 - first1 回の対応する比較もしくは述語が適用される。
 */
template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
inline HAMON_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred)
{
	while (first1 != last1 && pred(*first1, *first2))
	{
		++first1, ++first2;
	}

	return std::make_pair(first1, first2);
}

/**
 *	@overload
 */
template <typename InputIterator1, typename InputIterator2>
inline HAMON_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2)
{
	return hamon::mismatch(
		first1, last1, first2, hamon::equal_to<>());
}

/**
 *	@overload
 */
template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
inline HAMON_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred)
{
	while (first1 != last1 && first2 != last2 && pred(*first1, *first2))
	{
		++first1, ++first2;
	}

	return std::make_pair(first1, first2);
}

/**
 *	@overload
 */
template <typename InputIterator1, typename InputIterator2>
inline HAMON_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2>
mismatch(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	return hamon::mismatch(
		first1, last1, first2, last2, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MISMATCH_HPP
