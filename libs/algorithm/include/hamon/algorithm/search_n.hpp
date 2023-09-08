/**
 *	@file	search_n.hpp
 *
 *	@brief	search_n の定義
 */

#ifndef HAMON_ALGORITHM_SEARCH_N_HPP
#define HAMON_ALGORITHM_SEARCH_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::search_n;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <
	typename BinaryPredicate,
	typename ForwardIterator,
	typename Size,
	typename T
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
search_n_impl(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred,
	hamon::forward_iterator_tag*)
{
	if (count <= 0)
	{
		return first;
	}

	for (;;)
	{
		for (;;)
		{
			if (first == last)
			{
				return last;
			}

			if (pred(*first, value))
			{
				break;
			}

			++first;
		}

		auto m = first;
		Size c(0);

		for (;;)
		{
			if (++c == count)
			{
				return first;
			}

			if (++m == last)
			{
				return last;
			}

			if (!pred(*m, value))
			{
				first = m;
				++first;
				break;
			}
		}
	}
}

template <
	typename BinaryPredicate,
	typename RandomAccessIterator,
	typename Size,
	typename T
>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
search_n_impl(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred,
	hamon::random_access_iterator_tag*)
{
	if (count <= 0)
	{
		return first;
	}

	auto const len = static_cast<Size>(last - first);
	if (len < count)
	{
		return last;
	}

	auto const s = last - (count - 1);

	for (;;)
	{
		for (;;)
		{
			if (first >= s)
			{
				return last;
			}

			if (pred(*first, value))
			{
				break;
			}

			++first;
		}

		auto m = first;
		Size c(0);

		for (;;)
		{
			if (++c == count)
			{
				return first;
			}

			++m;

			if (!pred(*m, value))
			{
				first = m;
				++first;
				break;
			}
		}
	}
}

}	// namespace detail

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator
 *	@tparam	Size
 *	@tparam	T
 *	@tparam	BinaryPredicate
 *
 *	@param	first
 *	@param	last
 *	@param	count
 *	@param	value
 *	@param	pred
 *
 *	@require	Sizeは整数型に変換できる型である必要がある。
 *
 *	@return
 *		[first,last-count) 内のイテレータ i があるとき、0 以上 count 未満の整数 n について、
 *		それぞれ pred(*(i + n),value) != false であるようなサブシーケンスを探し、
 *		見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last を返す。
 *
 *	@complexity	最大で last - first 回の対応する述語が適用される。
 */
template <
	typename ForwardIterator,
	typename Size,
	typename T,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred)
{
	using Category = hamon::iterator_category<ForwardIterator>*;
	return hamon::detail::search_n_impl(
		first, last, count, value, pred, Category());
}

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator
 *	@tparam	Size
 *	@tparam	T
 *
 *	@param	first
 *	@param	last
 *	@param	count
 *	@param	value
 *
 *	@require	Sizeは整数型に変換できる型である必要がある。
 *
 *	@return
 *		[first,last-count) 内のイテレータ i があるとき、0 以上 count 未満の整数 n について、
 *		それぞれ *(i + n) == value であるようなサブシーケンスを探し、
 *		見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last を返す。
 *
 *	@complexity	最大で last - first 回の対応する比較が適用される。
 */
template <
	typename ForwardIterator,
	typename Size,
	typename T
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value)
{
	return hamon::search_n(
		first, last, count, value, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SEARCH_N_HPP
