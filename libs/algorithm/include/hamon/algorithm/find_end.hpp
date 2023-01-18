/**
 *	@file	find_end.hpp
 *
 *	@brief	find_end の定義
 */

#ifndef HAMON_ALGORITHM_FIND_END_HPP
#define HAMON_ALGORITHM_FIND_END_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::find_end;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/config.hpp>
#include <iterator>

namespace hamon
{

namespace detail
{

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator1
find_end_impl(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred,
	std::forward_iterator_tag*,
	std::forward_iterator_tag*)
{
	// modeled after search algorithm
	auto r = last1;  // last1 is the "default" answer

	if (first2 == last2)
	{
		return r;
	}

	for (;;)
	{
		for (;;)
		{
			// if source exhausted return last correct answer
			if (first1 == last1)
			{
				return r;	//    (or last1 if never found)
			}

			if (pred(*first1, *first2))
			{
				break;
			}

			++first1;
		}

		// *first1 matches *first2, now match elements after here
		auto m1 = first1;
		auto m2 = first2;

		for (;;)
		{
			// Pattern exhaused, record answer and search for another one
			if (++m2 == last2)
			{
				r = first1;
				++first1;
				break;
			}

			// Source exhausted, return last answer
			if (++m1 == last1)
			{
				return r;
			}

			// mismatch, restart with a new first
			if (!pred(*m1, *m2))
			{
				++first1;
				break;
			}  // else there is a match, check next elements
		}
	}
}

template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR BidirectionalIterator1
find_end_impl(
	BidirectionalIterator1 first1, BidirectionalIterator1 last1,
	BidirectionalIterator2 first2, BidirectionalIterator2 last2,
	BinaryPredicate pred,
	std::bidirectional_iterator_tag*,
	std::bidirectional_iterator_tag*)
{
	// modeled after search algorithm (in reverse)
	if (first2 == last2)
	{
		return last1;  // Everything matches an empty sequence
	}

	auto l1 = last1;
	auto l2 = last2;
	--l2;

	for (;;)
	{
		// Find last element in sequence 1 that matchs *(last2-1), with a mininum of loop checks
		for (;;)
		{
			if (first1 == l1)  // return last1 if no element matches *first2
			{
				return last1;
			}

			if (pred(*--l1, *l2))
			{
				break;
			}
		}

		// *l1 matches *l2, now match elements before here
		auto m1 = l1;
		auto m2 = l2;

		for (;;)
		{
			// If pattern exhausted, m1 is the answer (works for 1 element pattern)
			if (m2 == first2)
			{
				return m1;
			}

			// Otherwise if source exhaused, pattern not found
			if (m1 == first1)
			{
				return last1;
			}

			// if there is a mismatch, restart with a new l1
			if (!pred(*--m1, *--m2))
			{
				break;
			}  // else there is a match, check next elements
		}
	}
}

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator1
find_end_impl(
	RandomAccessIterator1 first1, RandomAccessIterator1 last1,
	RandomAccessIterator2 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	std::random_access_iterator_tag*,
	std::random_access_iterator_tag*)
{
	// Take advantage of knowing source and pattern lengths.
	// Stop short when source is smaller than pattern
	auto const len2 = last2 - first2;
	if (len2 == 0)
	{
		return last1;
	}

	auto const len1 = last1 - first1;
	if (len1 < len2)
	{
		return last1;
	}

	// End of pattern match can't go before here
	auto const s = first1 + (len2 - 1);
	auto l1 = last1;
	auto l2 = last2;
	--l2;

	for (;;)
	{
		for (;;)
		{
			if (s == l1)
			{
				return last1;
			}

			if (pred(*--l1, *l2))
			{
				break;
			}
		}

		auto m1 = l1;
		auto m2 = l2;

		for (;;)
		{
			if (m2 == first2)
			{
				return m1;
			}

			// no need to check range on m1 because s guarantees we have enough source
			if (!pred(*--m1, *--m2))
			{
				break;
			}
		}
	}
}

}	// namespace detail

/**
 *	@brief		範囲の中から、特定のサブシーケンスを検索する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		pred
 *
 *	@return		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *				0 以上 last2 - first2 未満の全ての整数 n について、
 *				それぞれ pred(*(i + n), *(first2 + n)) != false であるようなサブシーケンスを探し、
 *				見つかった 最後の サブシーケンスの先頭のイテレータを返す。
 *				そのようなイテレータが見つからない、もしくは [first2,last2) が空である場合は last1 を返す。
 *
 *	@complexity	最大で (last2 - first2) * (last1 - first1 - (last2 - first2) + 1) 回の、
 *				対応する述語が適用される
 *
 *	@note		search() と find_end() は共にサブシーケンスを検索する関数だが、以下の点が異なる。
 *				・search() は見つかった最初のサブシーケンスを返すが
 *				  find_end() は見つかった最後のサブシーケンスを返す
 *				・[first2,last2) が空であるときに search() は first1 を返すが、find_end() は last1 を返す
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = hamon::iterator_category<ForwardIterator1>*;
	using Category2 = hamon::iterator_category<ForwardIterator2>*;
	return hamon::detail::find_end_impl(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

/**
 *	@brief		範囲の中から、特定のサブシーケンスを検索する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *				0 以上 last2 - first2 未満の全ての整数 n について、
 *				それぞれ *(i + n) == *(first2 + n) であるようなサブシーケンスを探し、
 *				見つかった 最後の サブシーケンスの先頭のイテレータを返す。
 *				そのようなイテレータが見つからない、もしくは [first2,last2) が空である場合は last1 を返す。
 *
 *	@complexity	最大で (last2 - first2) * (last1 - first1 - (last2 - first2) + 1) 回の、
 *				対応する比較が適用される
 *
 *	@note		search() と find_end() は共にサブシーケンスを検索する関数だが、以下の点が異なる。
 *				・search() は見つかった最初のサブシーケンスを返すが
 *				  find_end() は見つかった最後のサブシーケンスを返す
 *				・[first2,last2) が空であるときに search() は first1 を返すが、find_end() は last1 を返す
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2)
{
	return hamon::find_end(
		first1, last1, first2, last2, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_FIND_END_HPP
