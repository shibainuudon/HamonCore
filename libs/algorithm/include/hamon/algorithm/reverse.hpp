/**
 *	@file	reverse.hpp
 *
 *	@brief	reverse の定義
 */

#ifndef HAMON_ALGORITHM_REVERSE_HPP
#define HAMON_ALGORITHM_REVERSE_HPP

#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		要素の並びを逆にする。
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	*first は Swappable でなければならない
 *
 *	@effect		0 以上 (last - first) / 2 未満の整数 i について、
 *				iter_swap(first + i, (last - i) - 1) を行う
 *
 *	@complexity	正確に (last - first) / 2 回 swap する
 */
template <typename BidirectionalIterator>
inline HAMON_CXX14_CONSTEXPR void
reverse(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	for (; first != last && first != --last; ++first)
	{
		hamon::ranges::iter_swap(first, last);
	}
}

}	// namespace hamon

#endif // HAMON_ALGORITHM_REVERSE_HPP
