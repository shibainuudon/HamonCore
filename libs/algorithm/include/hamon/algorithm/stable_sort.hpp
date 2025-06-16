/**
 *	@file	stable_sort.hpp
 *
 *	@brief	stable_sort の定義
 */

#ifndef HAMON_ALGORITHM_STABLE_SORT_HPP
#define HAMON_ALGORITHM_STABLE_SORT_HPP

#include <algorithm>

#if defined(__cpp_lib_constexpr_algorithms) && (__cpp_lib_constexpr_algorithms >= 202306L)

namespace hamon
{

using std::stable_sort;

}	// namespace hamon

#else

#include <hamon/algorithm/detail/stable_sort_impl.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲を安定ソートで並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	最大で N log^2(N) （N == last - first）回の比較を行う。
 *				ただし、十分なメモリがあれば N log(N) になる。
 */
template <typename RandomAccessIterator, typename Compare>
HAMON_CXX14_CONSTEXPR void
stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	hamon::detail::stable_sort_impl(hamon::move(first), hamon::move(last), comp);
}

template <typename RandomAccessIterator>
HAMON_CXX14_CONSTEXPR void
stable_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	hamon::detail::stable_sort_impl(hamon::move(first), hamon::move(last), hamon::less<>{});
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_STABLE_SORT_HPP
