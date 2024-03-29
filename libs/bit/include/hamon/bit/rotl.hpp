﻿/**
 *	@file	rotl.hpp
 *
 *	@brief	rotl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_ROTL_HPP
#define HAMON_BIT_ROTL_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::rotl;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
rotl_impl(T x, unsigned int shift) HAMON_NOEXCEPT
{
	return
		shift == 0 ?	// このチェックをしないとビット幅ぶんのシフトが発生して実装依存の動作になってしまう。
			x :
		static_cast<T>((x << shift) | (x >> (bitsof(x) - shift)));
}

}	// namespace detail

/**
 *	@brief	環状左シフト(キャリーなし左ローテート)
 *
 *	@tparam	T		xの型(符号なし整数型)
 *
 *	@param	x		シフトされる値
 *	@param	shift	シフトするビット数
 *
 *	xをshiftビットだけ環状左シフト(キャリーなし左ローテート)した値を返します。
 *	shiftがxのビット数以上の場合でも正しく計算します。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		hamon::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR T
rotl(T x, unsigned int shift) HAMON_NOEXCEPT
{
	return detail::rotl_impl(x, shift & static_cast<unsigned int>(bitsof(x) - 1));
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_ROTL_HPP
