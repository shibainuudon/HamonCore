/**
 *	@file	bit_floor.hpp
 *
 *	@brief	bit_floor 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BIT_FLOOR_HPP
#define HAMON_BIT_BIT_FLOOR_HPP

#include <hamon/bit/countl_zero.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.5 Integral powers of 2[bit.pow.two]

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
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.pow.two]/9
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T bit_floor(T x) HAMON_NOEXCEPT
{
	// [bit.pow.two]/10
	return x == 0 ? T(0) : static_cast<T>(T(1) << (hamon::numeric_limits<T>::digits - hamon::countl_zero(static_cast<T>(x >> 1))));
}

}	// namespace hamon

#endif // HAMON_BIT_BIT_FLOOR_HPP
