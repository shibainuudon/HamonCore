/**
 *	@file	is_permutation.hpp
 *
 *	@brief	is_permutation の定義
 */

#ifndef HAMON_ALGORITHM_IS_PERMUTATION_HPP
#define HAMON_ALGORITHM_IS_PERMUTATION_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::is_permutation;

}	// namespace hamon

#else

#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/iterator_category.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
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
inline HAMON_CXX14_CONSTEXPR bool
is_permutation_impl_2(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using D1 = hamon::iter_difference_t<ForwardIterator1>;

	// For each element in [f1, l1) see if there are the same number of
	//    equal elements in [f2, l2)
	for (auto i = first1; i != last1; ++i)
	{
		//  Have we already counted the number of *i in [f1, l1)?
		auto match = first1;

		for (; match != i; ++match)
		{
			if (pred(*match, *i))
			{
				break;
			}
		}

		if (match == i)
		{
			// Count number of *i in [f2, l2)
			D1 c2 = 0;
			for (auto j = first2; j != last2; ++j)
			{
				if (pred(*i, *j))
				{
					++c2;
				}
			}

			if (c2 == 0)
			{
				return false;
			}

			// Count number of *i in [i, l1) (we can start with 1)
			D1 c1 = 1;
			for (auto j = hamon::next(i); j != last1; ++j)
			{
				if (pred(*i, *j))
				{
					++c1;
				}
			}

			if (c1 != c2)
			{
				return false;
			}
		}
	}

	return true;
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation_impl(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2,
	BinaryPredicate pred)
{
	//  shorten sequences as much as possible by lopping of any equal prefix
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			break;
		}
	}

	if (first1 == last1)
	{
		return true;
	}

	//  first1 != last1 && *first1 != *first2
	auto const l1 = hamon::distance(first1, last1);
	if (l1 == 1)
	{
		return false;
	}

	ForwardIterator2 last2 = hamon::next(first2, l1);

	return is_permutation_impl_2(first1, last1, first2, last2, pred);
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation_impl(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred,
	hamon::forward_iterator_tag const*,
	hamon::forward_iterator_tag const*)
{
	//  shorten sequences as much as possible by lopping of any equal prefix
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (!pred(*first1, *first2))
		{
			break;
		}
	}

	if (first1 == last1)
	{
		return first2 == last2;
	}
	else if (first2 == last2)
	{
		return false;
	}

	auto const l1 = hamon::distance(first1, last1);
	auto const l2 = hamon::distance(first2, last2);

	if (l1 != l2)
	{
		return false;
	}

	return is_permutation_impl_2(first1, last1, first2, last2, pred);
}

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation_impl(
	RandomAccessIterator1 first1, RandomAccessIterator2 last1,
	RandomAccessIterator1 first2, RandomAccessIterator2 last2,
	BinaryPredicate pred,
	hamon::random_access_iterator_tag const*,
	hamon::random_access_iterator_tag const*)
{
	if (hamon::distance(first1, last1) != hamon::distance(first2, last2))
	{
		return false;
	}

	return hamon::detail::is_permutation_impl(first1, last1, first2, pred);
}

}	// namespace detail

/**
 *	@brief		first2 で始まる範囲を並べ替えたものが、[first1, last1) の範囲と一致するか判定する。
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
 *	@require	decltype(*first1) と decltype(*first2) の型が同じであること。
 *				BinaryPredicate は等価関係を持っていること。
 *
 *	@return		last2 が与えられている形式の場合、last1 - first1 != last2 - first2 であれば false を返す。
 *				そうでなければ、[first1, last1) の範囲と
 *				[first2, first2 + (last1 - first1)) の範囲を並び変えたもので、
 *				equal(first1, last1, first2)、あるいは
 *				equal(first1, last1, first2, pred) が true を返すようなものがあれば true を、
 *				そうでなければ false を返す。
 *				なお、実際に並べ替えが行われるわけではない。
 *
 *	@complexity	last2 が与えられている形式の場合、
 *				ForwardIterator1 と ForwardIterator2 がどちらもランダムアクセスイテレータの要件を満たし、
 *				かつ last1 - first1 != last2 - first2 であれば 1 度も述語の適用を行わない。
 *				そうでなければ、equal(first1, last1, first2, last2) == true
 *				もしくは equal(first1, last1, first2, last2, pred) == true の場合
 *				（last2 が無い形式の場合、equal も last2 の無い形式で置き換える）、
 *				distance(first1, last1) 回の述語適用で完了する。
 *				そうでなければ、distance(first1, last1) をNとした場合に最悪O(N^2)回の述語適用で完了する。
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2,
	BinaryPredicate pred)
{
	return hamon::detail::is_permutation_impl(
		first1, last1, first2, pred);
}

/**
 *
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2)
{
	return hamon::is_permutation(
		first1, last1, first2, hamon::equal_to<>());
}

/**
 *
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred)
{
	using Category1 = hamon::iterator_category<ForwardIterator1>*;
	using Category2 = hamon::iterator_category<ForwardIterator2>*;
	return hamon::detail::is_permutation_impl(
		first1, last1, first2, last2, pred, Category1(), Category2());
}

/**
 *
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline HAMON_CXX14_CONSTEXPR bool
is_permutation(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2)
{
	return hamon::is_permutation(
		first1, last1, first2, last2, hamon::equal_to<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_IS_PERMUTATION_HPP
