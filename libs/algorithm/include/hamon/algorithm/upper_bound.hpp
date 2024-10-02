/**
 *	@file	upper_bound.hpp
 *
 *	@brief	upper_bound の定義
 */

#ifndef HAMON_ALGORITHM_UPPER_BOUND_HPP
#define HAMON_ALGORITHM_UPPER_BOUND_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

using std::upper_bound;

}	// namespace hamon

#else

#include <hamon/iterator/distance.hpp>
#include <hamon/iterator/advance.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 27.8.4.3 upper_bound[upper.bound]

/**
 *	@brief		指定された要素より大きい値が現れる最初の位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *	@param		comp
 *
 *	@require	first、last は前方向イテレータの要件を満たすこと。
 *				comp は 2 引数の関数オブジェクトで、結果の型は bool 型に変換可能であること。
 *				また、引数に非 const の関数を適用しないこと。
 *				[first,last) の要素 e は !comp(value, e) によって区分化されていること。
 *				つまり、!comp(value, e) が true となる全ての要素 e は、
 *				false となる全ての要素よりも左側（first に近い方）になければならない。
 *
 *	@return		[first, last] 内のイテレータ i のうち、以下の条件を満たす、最も右側（first から遠い方）のもの
 *				・[first, i) 内の全てのイテレータ j が comp(value, *j) == false である
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T = typename hamon::iterator_traits<ForwardIterator>::value_type,
	typename Compare
>
HAMON_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	auto len = hamon::distance(first, last);

	while (len != 0)
	{
		auto half = len / 2;
		auto middle = first;
		hamon::advance(middle, half);

		if (comp(value, *middle))
		{
			len = half;
		}
		else
		{
			first = ++middle;
			len -= half + 1;
		}
	}

	return first;
}

/**
 *	@brief		指定された要素より大きい値が現れる最初の位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	first、last は前方向イテレータの要件を満たすこと。
 *				[first,last) の要素 e は !(value < e) によって区分化されていること。
 *				つまり、!(value < e) が true となる全ての要素 e は、
 *				false となる全ての要素よりも左側（first に近い方）になければならない。
 *
 *	@return		[first, last] 内のイテレータ i のうち、以下の条件を満たす、最も右側（first から遠い方）のもの
 *				・[first, i) 内の全てのイテレータ j が !(value < *j) である
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T = typename hamon::iterator_traits<ForwardIterator>::value_type>
HAMON_CXX14_CONSTEXPR ForwardIterator
upper_bound(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return hamon::upper_bound(
		first, last, value, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_UPPER_BOUND_HPP
