/**
 *	@file	bit_floor.hpp
 *
 *	@brief	bit_floor 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BIT_FLOOR_HPP
#define HAMON_BIT_BIT_FLOOR_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_INT_POW2)

#include <bit>

namespace hamon
{

using std::bit_floor;

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

// このアルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。
//
//	元々のコードは
//	uint64_t bit_floor(uint64_t x)
//	{
//		x = x | (x >> 1);
//		x = x | (x >> 2);
//		x = x | (x >> 4);
//		x = x | (x >> 8);
//		x = x | (x >>16);
//		x = x | (x >>32);
//		return x - (x >> 1);
//	}
//
//	これを任意のビット数に拡張しています。

template <typename T, hamon::size_t N>
struct bit_floor_impl
{
	static HAMON_CONSTEXPR T invoke(T x) HAMON_NOEXCEPT
	{
		return bit_floor_impl<T, N / 2>::invoke(static_cast<T>(x | (x >> N)));
	}
};

template <typename T>
struct bit_floor_impl<T, 0>
{
	static HAMON_CONSTEXPR T invoke(T x) HAMON_NOEXCEPT
	{
		return static_cast<T>(x - (x >> 1));
	}
};

}	// namespace detail

/**
 *	@brief	2の累乗への切り下げ
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return xが0のときは0を返す。
 *          そうでない場合、x 以下の最大の2の累乗を返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR T
bit_floor(T x) HAMON_NOEXCEPT
{
	return detail::bit_floor_impl<T, bitsof(x) / 2>::invoke(x);
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_BIT_FLOOR_HPP
