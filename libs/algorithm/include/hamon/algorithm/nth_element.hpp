/**
 *	@file	nth_element.hpp
 *
 *	@brief	nth_element の定義
 */

#ifndef HAMON_ALGORITHM_NTH_ELEMENT_HPP
#define HAMON_ALGORITHM_NTH_ELEMENT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::nth_element;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/heap_select.hpp>
#include <hamon/algorithm/detail/unguarded_partition_pivot.hpp>
#include <hamon/algorithm/detail/lg.hpp>
#include <hamon/algorithm/detail/insertion_sort.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename RandomAccessIterator, typename Size, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
introselect(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Size depth_limit,
	Compare comp)
{
	while (last - first > 3)
	{
		if (depth_limit == 0)
		{
			hamon::detail::heap_select(first, nth + 1, last, comp);
			// Place the nth largest element in its final position.
			hamon::ranges::iter_swap(first, nth);
			return;
		}

		--depth_limit;
		auto cut = hamon::detail::unguarded_partition_pivot(first, last, comp);

		if (cut <= nth)
		{
			first = cut;
		}
		else
		{
			last = cut;
		}
	}

	hamon::detail::insertion_sort(first, last, comp);
}

}	// namespace detail

/**
 *	@brief		基準となる要素よりも小さい要素が前に来るよう並べ替える。
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		nth
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		nth_element() を呼び出した後、nth が指している位置の要素は、
 *				全ての範囲がソートされた場合の位置にある要素になる。
 *				そして、[first,nth) にあるイテレータ i と、[nth,last) にあるイテレータ j について、
 *				comp(*j, *i) == false になる。
 *
 *	@complexity	平均で線形時間
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Compare comp)
{
	if (first == last || nth == last)
	{
		return;
	}

	hamon::detail::introselect(
		first, nth, last, hamon::detail::lg(last - first) * 2, comp);
}

/**
 *	@brief		基準となる要素よりも小さい要素が前に来るよう並べ替える。
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		nth
 *	@param		last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		nth_element() を呼び出した後、nth が指している位置の要素は、
 *				全ての範囲がソートされた場合の位置にある要素になる。
 *				そして、[first,nth) にあるイテレータ i と、[nth,last) にあるイテレータ j について、
 *				!(*j < *i) になる。
 *
 *	@complexity	平均で線形時間
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR void
nth_element(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last)
{
	return hamon::nth_element(first, nth, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_NTH_ELEMENT_HPP
