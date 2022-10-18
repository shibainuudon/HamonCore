/**
 *	@file	iter_swap.hpp
 *
 *	@brief	iter_swap の定義
 */

#ifndef HAMON_ALGORITHM_ITER_SWAP_HPP
#define HAMON_ALGORITHM_ITER_SWAP_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::iter_swap;

}	// namespace hamon

#else

#include <hamon/concepts/swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		2つのイテレータの要素を入れ替える
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		a
 *	@param		b
 *
 *	@require	a と b は Dereferenceable でなければならない。
 *				*a は *b と Swappable でなければならない。
 *
 *	@effect		swap(*a, *b)
 */
template <typename ForwardIterator1, typename ForwardIterator2>
inline HAMON_CXX14_CONSTEXPR void
iter_swap(ForwardIterator1 a, ForwardIterator2 b)
{
	hamon::ranges::swap(*a, *b);
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_ITER_SWAP_HPP
