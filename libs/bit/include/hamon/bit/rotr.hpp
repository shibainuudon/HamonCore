/**
 *	@file	rotr.hpp
 *
 *	@brief	rotr 関数テンプレートを定義
 */

#ifndef HAMON_BIT_ROTR_HPP
#define HAMON_BIT_ROTR_HPP

#include <hamon/bit/config.hpp>

#if defined(HAMON_HAS_CXX_LIB_BITOPS)

#include <bit>

namespace hamon
{

using std::rotr;

}	// namespace hamon

#else

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/bit/bitsof.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
rotr_impl(T x, unsigned int shift) HAMON_NOEXCEPT
{
	return
		shift == 0 ?	// このチェックをしないとビット幅ぶんのシフトが発生して実装依存の動作になってしまう。
			x :
		static_cast<T>((x >> shift) | (x << (bitsof(x) - shift)));
}

}	// namespace detail

/**
 *	@brief	環状右シフト(キャリーなし右ローテート)
 *
 *	@tparam	T		xの型(符号なし整数型)
 *
 *	@param	x		シフトされる値
 *	@param	shift	シフトするビット数
 *
 *	xをshiftビットだけ環状右シフト(キャリーなし右ローテート)した値を返します。
 *	shiftがxのビット数以上の場合でも正しく計算します。
 */
template <
	typename T,
	typename = hamon::enable_if_t<
		std::is_unsigned<T>::value
	>
>
inline HAMON_CONSTEXPR T
rotr(T x, unsigned int shift) HAMON_NOEXCEPT
{
	return detail::rotr_impl(x, shift & (bitsof(x) - 1));
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_ROTR_HPP
