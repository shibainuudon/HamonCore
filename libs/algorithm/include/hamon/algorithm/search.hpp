/**
 *	@file	search.hpp
 *
 *	@brief	search の定義
 */

#ifndef HAMON_ALGORITHM_SEARCH_HPP
#define HAMON_ALGORITHM_SEARCH_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::search;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <
	typename BinaryPredicate,
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator1
search_impl(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred,
	hamon::forward_iterator_tag*,
	hamon::forward_iterator_tag*)
{
	if (first2 == last2)
	{
		return first1;
	}

	for (;;)
	{
		for (;;)
		{
			if (first1 == last1)
			{
				return last1;
			}

			if (pred(*first1, *first2))
			{
				break;
			}

			++first1;
		}

		auto m1 = first1;
		auto m2 = first2;

		for (;;)
		{
			if (++m2 == last2)
			{
				return first1;
			}

			if (++m1 == last1)
			{
				return last1;
			}

			if (!pred(*m1, *m2))
			{
				++first1;
				break;
			}
		}
	}
}

template <
	typename BinaryPredicate,
	typename RandomAccessIterator1,
	typename RandomAccessIterator2
>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator1
search_impl(
	RandomAccessIterator1 first1, RandomAccessIterator1 last1,
	RandomAccessIterator2 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	std::random_access_iterator_tag*,
	std::random_access_iterator_tag*)
{
	auto const len2 = last2 - first2;
	if (len2 == 0)
	{
		return first1;
	}

	auto const len1 = last1 - first1;
	if (len1 < len2)
	{
		return last1;
	}

	auto const s = last1 - (len2 - 1);

	for (;;)
	{
		for (;;)
		{
			if (first1 == s)
			{
				return last1;
			}

			if (pred(*first1, *first2))
			{
				break;
			}

			++first1;
		}

		auto m1 = first1;
		auto m2 = first2;

		for (;;)
		{
			if (++m2 == last2)
			{
				return first1;
			}

			++m1;

			if (!pred(*m1, *m2))
			{
				++first1;
				break;
			}
		}
	}
}

}	// namespace detail

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator1
 *	@tparam	ForwardIterator2
 *	@tparam	BinaryPredicate
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *	@param	pred
 *
 *	@return
 *		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *		0 以上 last2 - first2 未満の整数 n について、それぞれ pred(*(i + n), *(first2 + n)) != false
 *		であるようなサブシーケンスを探し、見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last1 を返し、[first2,last2) が空である場合には first1 を返す。
 *
 *	@complexity	最大で (last1 - first1) * (last2 - first2) 回の、対応する述語が適用される
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = hamon::iterator_category<ForwardIterator1>*;
	using Category2 = hamon::iterator_category<ForwardIterator2>*;
	return hamon::detail::search_impl(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator1
 *	@tparam	ForwardIterator2
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *
 *	@return
 *		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *		0 以上 last2 - first2 未満の整数 n について、それぞれ *(i + n) == *(first2 + n)
 *		であるようなサブシーケンスを探し、見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last1 を返し、[first2,last2) が空である場合には first1 を返す。
 *
 *	@complexity	最大で (last1 - first1) * (last2 - first2) 回の、対応する比較が適用される
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2)
{
	return hamon::search(
		first1, last1, first2, last2, hamon::equal_to<>());
}

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator
 *	@tparam	Searcher
 *
 *	@param	first
 *	@param	last
 *	@param	searcher
 *
 *	@return	searcher.operator() の結果を返す。
 *
 *	@complexity	searcher に依存する
 */
template <typename ForwardIterator, typename Searcher>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
search(
	ForwardIterator first,
	ForwardIterator last,
	Searcher const& searcher)
{
	return searcher(first, last).first;
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SEARCH_HPP
