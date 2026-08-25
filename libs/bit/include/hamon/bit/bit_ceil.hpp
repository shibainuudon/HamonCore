/**
 *	@file	bit_ceil.hpp
 *
 *	@brief	bit_ceil 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BIT_CEIL_HPP
#define HAMON_BIT_BIT_CEIL_HPP

#include <hamon/bit/countl_zero.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.5 Integral powers of 2[bit.pow.two]

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
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.pow.two]/4
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T bit_ceil(T x) HAMON_NOEXCEPT
{
	// [bit.pow.two]/6
	return (x == 0) ? T(1) : static_cast<T>(T(1) << (hamon::numeric_limits<T>::digits - hamon::countl_zero(static_cast<T>(x - 1))));
}

}	// namespace hamon

#endif // HAMON_BIT_BIT_CEIL_HPP
