/**
 *	@file	abs.hpp
 *
 *	@brief	abs
 */

#ifndef HAMON_CMATH_ABS_HPP
#define HAMON_CMATH_ABS_HPP

#include <hamon/cmath/fabs.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T
abs_impl_2(T x, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
	return hamon::fabs(x);
}

template <HAMON_CONSTRAINED_PARAM(hamon::unsigned_integral, T)>
inline HAMON_CONSTEXPR T
abs_impl_2(T x, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	return x;
}

template <typename T>
inline HAMON_CONSTEXPR T
abs_impl_2(T x, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return x < 0 ? -x : x;
}

template <typename T>
inline HAMON_CONSTEXPR T
abs_impl(T x) HAMON_NOEXCEPT
{
	return abs_impl_2(x, hamon::detail::overload_priority<2>{});
}

}	// namespace detail

/**
 *	@brief	絶対値を求める
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの絶対値を返す
 *
 *	hamon::fabs関数との違い：
 *	・戻り値の型が引数の型と同じ(fabsに整数型を渡した時の戻り値はdouble型)
 *
 *	・xが整数型(IntegralType)の場合
 *	　結果の値を戻り値の型の範囲で表せない場合、動作は未定義となる。
 *	　例えば2の補数を使う処理系において、
 *	　abs(INT_MIN)の結果はINT_MAXより大きいためint型で表すことができない。
 *
 *	・xが浮動小数点型(FloatingPointType)の場合
 *	　+0と-0を区別しない。
 *	　+NaNと-NaNを区別しない。
 *
 *	・上記のようなチェックをしていないぶん、fabs関数より高速になる可能性がある。
 *
 *	標準ライブラリ<cmath>のabs関数との違い:
 *	・constexpr指定している
 *	・hamon::absは全ての算術型に対応している。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
inline HAMON_CONSTEXPR Arithmetic
abs(Arithmetic x) HAMON_NOEXCEPT
{
	return detail::abs_impl(x);
}

}	// namespace hamon

#endif // HAMON_CMATH_ABS_HPP
