/**
 *	@file	is_heap_until.hpp
 *
 *	@brief	is_heap_until の定義
 */

#ifndef HAMON_ALGORITHM_IS_HEAP_UNTIL_HPP
#define HAMON_ALGORITHM_IS_HEAP_UNTIL_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_ALGORITHM)

#include <algorithm>

namespace hamon
{

using std::is_heap_until;

}	// namespace hamon

#else

#include <hamon/functional/less.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		範囲がヒープ化されているか判定し、ヒープ化されていない最初の要素を指すイテレータを取得する
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		distance(first, last) < 2 の場合は last を返す。
 *				そうでない場合、[first,last] 内のイテレータ i について、
 *				[first,i) が heap であるような最後の i を返す。
 *
 *	@complexity	線形時間
 */
template <typename RandomAccessIterator, typename Compare>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
is_heap_until(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	using difference_type =
		hamon::iter_difference_t<RandomAccessIterator>;

	difference_type const len = last - first;
	difference_type p = 0;
	difference_type c = 1;
	auto pp = first;

	while (c < len)
	{
		auto cp = first + c;
		
		if (comp(*pp, *cp))
		{
			return cp;
		}

		++c;
		++cp;
		
		if (c == len)
		{
			return last;
		}

		if (comp(*pp, *cp))
		{
			return cp;
		}

		++p;
		++pp;
		c = 2 * p + 1;
	}

	return last;
}

/**
 *	@brief		範囲がヒープ化されているか判定し、ヒープ化されていない最初の要素を指すイテレータを取得する
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		distance(first, last) < 2 の場合は last を返す。
 *				そうでない場合、[first,last] 内のイテレータ i について、
 *				[first,i) が heap であるような最後の i を返す。
 *
 *	@complexity	線形時間
 */
template <typename RandomAccessIterator>
inline HAMON_CXX14_CONSTEXPR RandomAccessIterator
is_heap_until(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	return hamon::is_heap_until(first, last, hamon::less<>());
}

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_IS_HEAP_UNTIL_HPP
