/**
 *	@file	iota.hpp
 *
 *	@brief	iota の定義
 */

#ifndef HAMON_NUMERIC_IOTA_HPP
#define HAMON_NUMERIC_IOTA_HPP

#include <hamon/numeric/config.hpp>

#if defined(HAMON_USE_STD_NUMERIC)

#include <numeric>

namespace hamon
{

using std::iota;

}	// namespace hamon

#else

#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		指定された値から始まる整数列を生成する。
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	ForwardIteratorの値型が、型Tに変換可能であること
 *				型Tの値valに対して、式++valが有効であること
 *
 *	@effect		範囲[first, last)の各要素itについて、先頭から順番に *it = value; ++value; を行う
 *
 *	@complexity	範囲[first, last)の要素数をnとして、n回のインクリメントと代入が行われる。
 */
template <typename ForwardIterator, typename T>
HAMON_CXX14_CONSTEXPR void
iota(ForwardIterator first, ForwardIterator last, T value)
{
	for (; first != last; ++first)
	{
		*first = value;
		++value;
	}
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_IOTA_HPP
