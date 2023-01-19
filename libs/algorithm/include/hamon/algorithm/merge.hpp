/**
 *	@file	merge.hpp
 *
 *	@brief	merge の定義
 */

#ifndef HAMON_ALGORITHM_MERGE_HPP
#define HAMON_ALGORITHM_MERGE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::merge;

}	// namespace hamon

#else

#include <hamon/algorithm/copy.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		2つのソート済み範囲をマージする。
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		OutputIterator
 *	@tparam		Compare
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *	@param		comp
 *
 *	@require	[first1,last1) と [first2,last2) は comp でソートされていること。
 *				結果の範囲と入力の範囲は重なっていてはならない。
 *
 *	@effect		[first1,last1) と [first2,last2) の２つの要素を全て [result,result_last) へコピーする。
 *				その際に、is_sorted(result, result_last, comp) の条件を満たすようにコピーする
 *				（result_last は result + (last1 - first1) + (last2 - first2) とする）。
 *
 *	@return		result + (last1 - first1) + (last2 - first2)
 *
 *	@complexity	最大で (last1 - first1) + (last2 - first2) - 1 回比較する。
 *
 *	@note		この操作は安定である。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
merge(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2,
	OutputIterator result,
	Compare comp)
{
	for (; first1 != last1; ++result)
	{
		if (first2 == last2)
		{
			return hamon::copy(first1, last1, result);
		}

		if (comp(*first2, *first1))
		{
			*result = *first2;
			++first2;
		}
		else
		{
			*result = *first1;
			++first1;
		}
	}

	return hamon::copy(first2, last2, result);
}

/**
 *	@brief		2つのソート済み範囲をマージする。
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		OutputIterator
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *
 *	@require	[first1,last1) と [first2,last2) は operator< でソートされていること。
 *				結果の範囲と入力の範囲は重なっていてはならない。
 *
 *	@effect		[first1,last1) と [first2,last2) の２つの要素を全て [result,result_last) へコピーする。
 *				その際に、is_sorted(result, result_last) の条件を満たすようにコピーする
 *				（result_last は result + (last1 - first1) + (last2 - first2) とする）。
 *
 *	@return		result + (last1 - first1) + (last2 - first2)
 *
 *	@complexity	最大で (last1 - first1) + (last2 - first2) - 1 回比較する。
 *
 *	@note		この操作は安定である。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
merge(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result)
{
	return hamon::merge(
		first1, last1, first2, last2, result, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_MERGE_HPP
