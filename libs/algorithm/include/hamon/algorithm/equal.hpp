﻿/**
 *	@file	equal.hpp
 *
 *	@brief	equal の定義
 */

#ifndef HAMON_ALGORITHM_EQUAL_HPP
#define HAMON_ALGORITHM_EQUAL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::equal;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX11_CONSTEXPR bool
equal_impl_1(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred)
{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			return false;
		}
	}

	return true;
#else
	return first1 == last1 ||
		(pred(*first1, *first2) &&
		 equal_impl_1(hamon::next(first1), last1, hamon::next(first2), pred));
#endif
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX11_CONSTEXPR bool
equal_impl_1(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred)
{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			return false;
		}
	}

	return first1 == last1 && first2 == last2;
#else
	return
		first1 != last1 && first2 != last2 ?
			pred(*first1, *first2) &&
			equal_impl_1(hamon::next(first1), last1, hamon::next(first2), last2, pred) :
		first1 == last1 && first2 == last2;
#endif
}

template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX11_CONSTEXPR bool
equal_impl_2(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred,
	hamon::input_iterator_tag const*,
	hamon::input_iterator_tag const*)
{
	return equal_impl_1(first1, last1, first2, last2, pred);
}

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX11_CONSTEXPR bool
equal_impl_2(
	RandomAccessIterator1 first1, RandomAccessIterator1 last1,
	RandomAccessIterator2 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	hamon::random_access_iterator_tag const*,
	hamon::random_access_iterator_tag const*)
{
	return
		hamon::distance(first1, last1) == hamon::distance(first2, last2) &&
		hamon::detail::equal_impl_1(first1, last1, first2, pred);
}

}	// namespace detail

/**
 *	@brief	2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		pred
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2,
	BinaryPredicate pred)
{
	return hamon::detail::equal_impl_1(
		first1, last1, first2, pred);
}

/**
 *	@brief	2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 */
template <
	typename InputIterator1,
	typename InputIterator2
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2)
{
	return hamon::equal(
		first1, last1, first2, hamon::equal_to<>());
}

/**
 *	@brief	2つの範囲を等値比較する
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
 *	@return		もしlast1 - first1 != last2 - first2 であれば、falseを返す。
 *				そうでない場合、[first1, last1)のイテレータi、[first2, last2)のイテレータjについて、
 *				pred(*i, *j) が全て満たされるのであればtrueを返す。
 *				そうでない場合はfalseを返す。
 *
 *	@complexity	もし InputIterator1 と InputIterator2 が共にランダムアクセスイテレータの要件を満たす場合で、
 *				かつ、last1 - first1 != last2 - first2 の場合、1 度も述語は適用されない。
 *				そうでない場合、最大で min(last1 - first1, last2 - first2) 回の述語が適用される。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename BinaryPredicate
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = hamon::iterator_category<InputIterator1>*;
	using Category2 = hamon::iterator_category<InputIterator2>*;
	return hamon::detail::equal_impl_2(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

/**
 *	@brief		2つの範囲を等値比較する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		もしlast1 - first1 != last2 - first2 であれば、falseを返す。
 *				そうでない場合、[first1, last1)のイテレータi、[first2, last2)のイテレータjについて、
 *				*i == *j が全て満たされるのであればtrueを返す。
 *				そうでない場合はfalseを返す。
 *
 *	@complexity	もし InputIterator1 と InputIterator2 が共にランダムアクセスイテレータの要件を満たす場合で、
 *				かつ、last1 - first1 != last2 - first2 の場合、1 度も比較は適用されない。
 *				そうでない場合、最大で min(last1 - first1, last2 - first2) 回の比較が適用される。
 */
template <
	typename InputIterator1,
	typename InputIterator2
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
equal(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	return hamon::equal(
		first1, last1, first2, last2, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_EQUAL_HPP
