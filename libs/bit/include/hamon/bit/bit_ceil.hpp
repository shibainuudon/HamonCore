﻿/**
 *	@file	bit_ceil.hpp
 *
 *	@brief	bit_ceil 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BIT_CEIL_HPP
#define HAMON_BIT_BIT_CEIL_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace hamon
{

using std::bit_ceil;

}	// namespace hamon

#else

#include <hamon/bit/bitsof.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// アルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。
//
//	元々のコードは
//	uint64_t bit_ceil(uint64_t x)
//	{
//		x = x - 1;
//		x = x | (x >> 1);
//		x = x | (x >> 2);
//		x = x | (x >> 4);
//		x = x | (x >> 8);
//		x = x | (x >>16);
//		x = x | (x >>32);
//		return x + 1;
//	}
//
//	これを任意のビット数に拡張しています。

template <typename T, hamon::size_t N>
struct bit_ceil_impl2
{
	static HAMON_CONSTEXPR T invoke(T x) HAMON_NOEXCEPT
	{
		return bit_ceil_impl2<T, N / 2>::invoke(static_cast<T>(x | (x >> N)));
	}
};

template <typename T>
struct bit_ceil_impl2<T, 0>
{
	static HAMON_CONSTEXPR T invoke(T x) HAMON_NOEXCEPT
	{
		return static_cast<T>(x + 1);
	}
};

template <typename T>
inline HAMON_CONSTEXPR T
bit_ceil_impl(T x) HAMON_NOEXCEPT
{
	return (x == 0) ? T(1) : detail::bit_ceil_impl2<T, bitsof(x) / 2>::invoke(static_cast<T>(x - 1));
}

}	// namespace detail

/**
 *	@brief	2の累乗への切り上げ
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x以上で最小の2の累乗を返す。
 *          戻り値をTとして表現できない場合、0を返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR T
bit_ceil(T x) HAMON_NOEXCEPT
{
	return detail::bit_ceil_impl(x);
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_BIT_CEIL_HPP
