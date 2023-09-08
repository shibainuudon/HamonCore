/**
 *	@file	unique_copy.hpp
 *
 *	@brief	unique_copy の定義
 */

#ifndef HAMON_ALGORITHM_UNIQUE_COPY_HPP
#define HAMON_ALGORITHM_UNIQUE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::unique_copy;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <
	typename BinaryPredicate,
	typename InputIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
unique_copy_impl(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryPredicate pred,
	hamon::input_iterator_tag*,
	hamon::output_iterator_tag*)
{
	if (first != last)
	{
		hamon::iter_value_t<InputIterator> t(*first);
		*result = t;
		++result;

		while (++first != last)
		{
			if (!pred(t, *first))
			{
				t = *first;
				*result = t;
				++result;
			}
		}
	}

	return result;
}

template <
	typename BinaryPredicate,
	typename ForwardIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
unique_copy_impl(
	ForwardIterator first,
	ForwardIterator last,
	OutputIterator result,
	BinaryPredicate pred,
	std::forward_iterator_tag*,
	hamon::output_iterator_tag*)
{
	if (first != last)
	{
		auto i = first;
		*result = *i;
		++result;

		while (++first != last)
		{
			if (!pred(*i, *first))
			{
				*result = *first;
				++result;
				i = first;
			}
		}
	}

	return result;
}

template <
	typename BinaryPredicate,
	typename InputIterator,
	typename ForwardIterator
>
inline HAMON_CXX14_CONSTEXPR ForwardIterator
unique_copy_impl(
	InputIterator first,
	InputIterator last,
	ForwardIterator result,
	BinaryPredicate pred,
	hamon::input_iterator_tag*,
	std::forward_iterator_tag*)
{
	if (first != last)
	{
		*result = *first;

		while (++first != last)
		{
			if (!pred(*result, *first))
			{
				*++result = *first;
			}
		}

		++result;
	}

	return result;
}

}	// namespace detail

/**
 *	@brief		重複した要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		BinaryPredicate
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		pred
 *
 *	@require	比較関数は等価関係を持っていなければならない。
 *				[first,last) と [result,result + (last - first)) は重なっていてはならない。
 *				*result = *first は有効な式でなければならない。
 *				InputIterator と OutputIterator のどちらも forward iterator の要求を満たしていない場合、
 *				InputIterator の value type は CopyConstructible かつ CopyAssignable でなければならない。
 *				そうでない場合は CopyConstructible は要求されない。
 *
 *	@effect		[first,last) 内のイテレータ i について、pred(*(i - 1), *i) != false
 *				による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭を result へコピーする。
 *
 *	@return		結果の範囲の終端を返す。
 *
 *	@complexity	[first,last) が空の範囲でない場合、正確に last - first - 1 回の述語の適用を行う
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
unique_copy(
	InputIterator first, InputIterator last,
	OutputIterator result,
	BinaryPredicate pred)
{
	using Category1 = hamon::iterator_category<InputIterator>*;
	using Category2 = hamon::iterator_category<OutputIterator>*;
	return hamon::detail::unique_copy_impl(
		first, last, result, pred, Category1(), Category2());
}

/**
 *	@brief		重複した要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	比較関数は等価関係を持っていなければならない。
 *				[first,last) と [result,result + (last - first)) は重なっていてはならない。
 *				*result = *first は有効な式でなければならない。
 *				InputIterator と OutputIterator のどちらも forward iterator の要求を満たしていない場合、
 *				InputIterator の value type は CopyConstructible かつ CopyAssignable でなければならない。
 *				そうでない場合は CopyConstructible は要求されない。
 *
 *	@effect		[first,last) 内のイテレータ i について、*(i - 1) == *i
 *				による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭を result へコピーする。
 *
 *	@return		結果の範囲の終端を返す。
 *
 *	@complexity	[first,last) が空の範囲でない場合、正確に last - first - 1 回の比較を行う
 */
template <
	typename InputIterator,
	typename OutputIterator
>
inline HAMON_CXX14_CONSTEXPR OutputIterator
unique_copy(
	InputIterator first, InputIterator last,
	OutputIterator result)
{
	return hamon::unique_copy(
		first, last, result, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_UNIQUE_COPY_HPP
