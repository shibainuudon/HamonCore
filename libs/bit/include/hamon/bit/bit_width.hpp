/**
 *	@file	bit_width.hpp
 *
 *	@brief	bit_width 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BIT_WIDTH_HPP
#define HAMON_BIT_BIT_WIDTH_HPP

#include <hamon/bit/countl_zero.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.11.5 Integral powers of 2[bit.pow.two]

/**
 *	@brief	値を表現するために必要なビット幅を求める。
 *
 *	@tparam	T	xの型(符号なし整数型)
 *
 *	@param	x	対象の整数
 *
 *	@return x == 0である場合、0を返す。
 *			そうでない場合、2を底としてxの対数を求めて、それに1を足した値を返す。
 *			その際、小数点以下の値は破棄される。
 *
 *	戻り値に1を足す理由は、対数を求められない0を引数として許容することでnoexceptとし、
 *	かつx == 1である場合と区別するためである。
 */
template <HAMON_CONSTRAINT(hamon::unsigned_integral, T)>	// [bit.pow.two]/11
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
int bit_width(T x) HAMON_NOEXCEPT
{
	// [bit.pow.two]/12
	return hamon::numeric_limits<T>::digits - hamon::countl_zero(x);
}

}	// namespace hamon

#endif // HAMON_BIT_BIT_WIDTH_HPP
