/**
 *	@file	equal_range.hpp
 *
 *	@brief	equal_range の定義
 */

#ifndef HAMON_ALGORITHM_EQUAL_RANGE_HPP
#define HAMON_ALGORITHM_EQUAL_RANGE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::equal_range;

}	// namespace hamon

#else

#include <hamon/algorithm/lower_bound.hpp>
#include <hamon/algorithm/upper_bound.hpp>
#include <hamon/iterator/advance.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/pair.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		lower_bound()とupper_bound()の結果を組で取得する
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
 *	@require	[first,last) の要素 e は comp(e, value) および !comp(value, e) によって区分化されていなければならない。
 *				また、[first, last) の要素 e は全て暗黙に、comp(e, value) が !comp(value, e) を意味している必要がある。
 *
 *	@return		make_pair(lower_bound(first, last, value, comp), upper_bound(first, last, value, comp))
 *
 *	@complexity	最大で 2 * log2(last - first) + O(1) 回の比較を行う
 */
template <typename ForwardIterator, typename T, typename Compare>
inline HAMON_CXX14_CONSTEXPR
hamon::pair<ForwardIterator, ForwardIterator>
equal_range(
	ForwardIterator first,
	ForwardIterator last,
	T const& value,
	Compare comp)
{
	auto len = hamon::distance(first, last);

	while (len != 0)
	{
		auto l2 = len / 2;
		auto m = first;
		hamon::advance(m, l2);

		if (comp(*m, value))
		{
			first = ++m;
			len -= l2 + 1;
		}
		else if (comp(value, *m))
		{
			last = m;
			len = l2;
		}
		else
		{
			auto mp1 = m;
			return hamon::make_pair(
				hamon::lower_bound(first, m, value, comp),
				hamon::upper_bound(++mp1, last, value, comp));
		}
	}

	return hamon::make_pair(first, first);
}

/**
 *	@brief		lower_bound()とupper_bound()の結果を組で取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	[first,last) の要素 e は e < value および !(value < e) によって区分化されていなければならない。
 *				また、[first, last) の要素 e は全て暗黙に、e < value が !(value < e) を意味している必要がある。
 *
 *	@return		make_pair(lower_bound(first, last, value), upper_bound(first, last, value))
 *
 *	@complexity	最大で 2 * log2(last - first) + O(1) 回の比較を行う
 */
template <typename ForwardIterator, typename T>
inline HAMON_CXX14_CONSTEXPR
hamon::pair<ForwardIterator, ForwardIterator>
equal_range(
	ForwardIterator first,
	ForwardIterator last,
	T const& value)
{
	return hamon::equal_range(
		first, last, value, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_EQUAL_RANGE_HPP
