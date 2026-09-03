/**
 *	@file	exp.hpp
 *
 *	@brief	exp 関数の定義
 */

#ifndef HAMON_CMATH_EXP_HPP
#define HAMON_CMATH_EXP_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/cmath/detail/exp_table.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
exp_unchecked_around_zero_recur(T x, unsigned int n, unsigned int last) HAMON_NOEXCEPT
{
	return last - n == 1 ?
		pow_n(x, n) / unchecked_factorial<T>(n) :
		exp_unchecked_around_zero_recur(x, n, n + (last - n) / 2) +
		exp_unchecked_around_zero_recur(x, n + (last - n) / 2, last);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
exp_unchecked_around_zero(T x) HAMON_NOEXCEPT
{
	return !(x > -1) ?
		T(1) / (T(1) + exp_unchecked_around_zero_recur(-x, 1, max_factorial<T>() / 2 + 1)) :
		        T(1) + exp_unchecked_around_zero_recur( x, 1, max_factorial<T>() / 2 + 1);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
exp_unchecked_ct(T x) HAMON_NOEXCEPT
{
	// 指数関数はマクローリン展開によって求めることができるが、
	// xの絶対値が大きくなると急激に精度が落ちてしまう。
	// そこで、e^(a+b) = e^a * e^b であることを利用して、xを整数部と小数部にわけて、
	// 整数部はテーブル引きで求め、小数部はマクローリン展開で求めてそれらを乗算する。
	int const i = static_cast<int>(x);
	return
		i > exp_table_max ?
			hamon::numeric_limits<T>::infinity() :
		i < exp_table_min ?
			T(0) :
			static_cast<T>(exp_table[i - exp_table_min] * exp_unchecked_around_zero(x - static_cast<T>(i)));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
exp_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::exp(x);
}

inline HAMON_CXX11_CONSTEXPR float
exp_unchecked(float x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_expf)
	return hamon::is_constant_evaluated() ? exp_unchecked_ct(x) : __builtin_expf(x);
#else
	return hamon::is_constant_evaluated() ? exp_unchecked_ct(x) : exp_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
exp_unchecked(double x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_exp)
	return hamon::is_constant_evaluated() ? exp_unchecked_ct(x) : __builtin_exp(x);
#else
	return hamon::is_constant_evaluated() ? exp_unchecked_ct(x) : exp_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
exp_unchecked(long double x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_expl)
	return hamon::is_constant_evaluated() ? exp_unchecked_ct(x) : __builtin_expl(x);
#else
	return hamon::is_constant_evaluated() ? exp_unchecked_ct(x) : exp_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
exp_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			FloatType(1) :
		hamon::isinf(x) ?
			hamon::signbit(x) ?
				FloatType(0) :
			x :
		hamon::isnan(x) ?
			x :
		exp_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	e (ネイピア数) を底とする指数関数を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、e (ネイピア数) の arg 乗を返す。
 *
 *	arg が ±0  の場合、1  を返す。
 *	arg が -∞  の場合、+0 を返す。
 *	arg が +∞  の場合、+∞ を返す。
 *	arg が NaN  の場合、NaN を返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
exp(FloatType arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
expf(float arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
expl(long double arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
exp(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::exp_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_EXP_HPP
