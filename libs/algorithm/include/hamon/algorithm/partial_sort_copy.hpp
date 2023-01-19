/**
 *	@file	partial_sort_copy.hpp
 *
 *	@brief	partial_sort_copy の定義
 */

#ifndef HAMON_ALGORITHM_PARTIAL_SORT_COPY_HPP
#define HAMON_ALGORITHM_PARTIAL_SORT_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::partial_sort_copy;

}	// namespace hamon

#else

#include <hamon/algorithm/make_heap.hpp>
#include <hamon/algorithm/sort_heap.hpp>
#include <hamon/algorithm/detail/adjust_heap.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲を部分的にソートした結果を他の範囲にコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		result_first
 *	@param		result_last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*result_first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、
 *				min(last - first, result_last - result_first) 個の要素をソート済みの状態で
 *				[result_first,result_first + min(last - first, result_last - result_first)) に配置する。
 *
 *	@return		result_last と result_first + (last - first) で小さい方が返される
 *
 *	@complexity	ほぼ (last - first) * log(min(last - first, result_last - result_- first)) 回の比較を行う
 */
template <
	typename InputIterator,
	typename RandomAccessIterator,
	typename Compare
>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
partial_sort_copy(
	InputIterator        first,        InputIterator        last,
	RandomAccessIterator result_first, RandomAccessIterator result_last,
	Compare comp)
{
	using input_value_t = hamon::iter_value_t<InputIterator>;
	using difference_t = hamon::iter_difference_t<RandomAccessIterator>;

	if (result_first == result_last)
	{
		return result_last;
	}

	auto result_real_last = result_first;
	while (first != last && result_real_last != result_last)
	{
		*result_real_last = *first;
		++result_real_last;
		++first;
	}

	hamon::make_heap(result_first, result_real_last, comp);

	while (first != last)
	{
		if (comp(*first, *result_first))
		{
			hamon::detail::adjust_heap(
				result_first,
				difference_t(0),
				difference_t(result_real_last - result_first),
				input_value_t(*first),
				comp);
		}

		++first;
	}

	hamon::sort_heap(result_first, result_real_last, comp);
	return result_real_last;
}

/**
 *	@brief		範囲を部分的にソートした結果を他の範囲にコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result_first
 *	@param		result_last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*result_first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、
 *				min(last - first, result_last - result_first) 個の要素をソート済みの状態で
 *				[result_first,result_first + min(last - first, result_last - result_first)) に配置する。
 *
 *	@return		result_last と result_first + (last - first) で小さい方が返される
 *
 *	@complexity	ほぼ (last - first) * log(min(last - first, result_last - result_- first)) 回の比較を行う
 */
template <
	typename InputIterator,
	typename RandomAccessIterator
>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
partial_sort_copy(
	InputIterator        first,        InputIterator        last,
	RandomAccessIterator result_first, RandomAccessIterator result_last)
{
	return hamon::partial_sort_copy(
		first, last, result_first, result_last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_PARTIAL_SORT_COPY_HPP
