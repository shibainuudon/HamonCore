﻿/**
 *	@file	popcount.hpp
 *
 *	@brief	popcount 関数テンプレートの定義
 */

#ifndef HAMON_BIT_POPCOUNT_HPP
#define HAMON_BIT_POPCOUNT_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::popcount;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/cstdint/uint64_t.hpp>

namespace hamon
{

namespace detail
{

// このアルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。

#if defined(HAMON_HAS_CXX14_CONSTEXPR)

inline constexpr int
popcount_impl(hamon::uint64_t x) HAMON_NOEXCEPT
{
	x = (x - ((x >> 1) & UINT64_C(0x5555555555555555)));
	x = ((x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333)));
	x = ((x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f));
	x = (x * UINT64_C(0x0101010101010101));
	return static_cast<int>(x >> 56);
}

#else

inline HAMON_CONSTEXPR int
popcount_impl_4(hamon::uint64_t x) HAMON_NOEXCEPT
{
	return static_cast<int>((x * UINT64_C(0x0101010101010101)) >> 56);
}

inline HAMON_CONSTEXPR int
popcount_impl_3(hamon::uint64_t x) HAMON_NOEXCEPT
{
	return popcount_impl_4((x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f));
}

inline HAMON_CONSTEXPR int
popcount_impl_2(hamon::uint64_t x) HAMON_NOEXCEPT
{
	return popcount_impl_3((x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333)));
}

inline HAMON_CONSTEXPR int
popcount_impl(hamon::uint64_t x) HAMON_NOEXCEPT
{
	return popcount_impl_2(x - ((x >> 1) & UINT64_C(0x5555555555555555)));
}

#endif

}	// namespace detail

/**
 *	@brief	1になっているビットを数える。(Population Count)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、1 となるビットの個数を返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR int
popcount(T x) HAMON_NOEXCEPT
{
	return detail::popcount_impl(x);
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_POPCOUNT_HPP
