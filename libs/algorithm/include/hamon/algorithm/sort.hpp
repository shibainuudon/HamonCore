/**
 *	@file	sort.hpp
 *
 *	@brief	sort の定義
 */

#ifndef HAMON_ALGORITHM_SORT_HPP
#define HAMON_ALGORITHM_SORT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::sort;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/sort_impl.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	N log N (N == last - first) 回の比較
 */
template <typename RandomAccessIterator, typename Compare>
HAMON_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	hamon::detail::sort_impl(hamon::move(first), hamon::move(last), comp);
}

template <typename RandomAccessIterator>
HAMON_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last)
{
	hamon::detail::sort_impl(hamon::move(first), hamon::move(last), hamon::less<>{});
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_SORT_HPP
