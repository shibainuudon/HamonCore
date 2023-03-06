/**
 *	@file	countl_zero.hpp
 *
 *	@brief	countl_zero 関数テンプレートの定義
 */

#ifndef HAMON_BIT_COUNTL_ZERO_HPP
#define HAMON_BIT_COUNTL_ZERO_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::countl_zero;

}	// namespace hamon

#else

#include <hamon/bit/popcount.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/config.hpp>
#include <cstddef>

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
//	int countl_zero(uint64_t x)
//	{
//		x = (x | (x >>  1));
//		x = (x | (x >>  2));
//		x = (x | (x >>  4));
//		x = (x | (x >>  8));
//		x = (x | (x >> 16));
//		x = (x | (x >> 32));
//		return popcount(uint64_t(~x));
//	}
//
//	これを任意のビット数に拡張しています。

template <typename T, std::size_t N>
struct countl_zero_impl
{
	static HAMON_CONSTEXPR int invoke(T x) HAMON_NOEXCEPT
	{
		return countl_zero_impl<T, N / 2>::invoke(static_cast<T>(x | (x >> N)));
	}
};

template <typename T>
struct countl_zero_impl<T, 0>
{
	static HAMON_CONSTEXPR int invoke(T x) HAMON_NOEXCEPT
	{
		return popcount(static_cast<T>(~x));
	}
};

}	// namespace detail

/**
 *	@brief	最上位から0のビットが連続でいくつあるかを返す。(Count Leading Zeros)
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x を2進数で表現した際に、最上位ビットから0が何ビット続くかを返す。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR int
countl_zero(T x) HAMON_NOEXCEPT
{
	return detail::countl_zero_impl<T, bitsof(x) / 2>::invoke(x);
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_COUNTL_ZERO_HPP
