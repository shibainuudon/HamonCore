/**
 *	@file	atan.hpp
 *
 *	@brief	atan 関数の定義
 */

#ifndef HAMON_CMATH_ATAN_HPP
#define HAMON_CMATH_ATAN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/factorial.hpp>
#include <hamon/cmath/detail/pow_n.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/numbers/sqrt2.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
atan_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_atanf(x);
}

inline HAMON_CXX11_CONSTEXPR double
atan_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_atan(x);
}

inline HAMON_CXX11_CONSTEXPR long double
atan_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_atanl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
atan_unchecked_ct_2(T x, unsigned int n, unsigned int last) HAMON_NOEXCEPT
{
	return last - n == 1 ?
		(n % 2 ? -1 : 1) * pow_n(x, 2 * n + 1) / T(2 * n + 1) :
		atan_unchecked_ct_2(x, n, n + (last - n) / 2) +
		atan_unchecked_ct_2(x, n + (last - n) / 2, last);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
atan_unchecked_ct_1(T x, T sqrt2, T pi, unsigned int last) HAMON_NOEXCEPT
{
	return
		x > sqrt2 + 1 ?
			(pi / 2) - atan_unchecked_ct_2(1 / x, 0, last) :
		x > sqrt2 - 1 ?
			(pi / 4) + atan_unchecked_ct_2((x - 1) / (x + 1), 0, last) :
			x + atan_unchecked_ct_2(x, 1, last);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
atan_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return x < 0 ?
		-atan_unchecked_ct(-x) :
		atan_unchecked_ct_1(
			x,
			hamon::numbers::sqrt2_fn<T>(),
			hamon::numbers::pi_fn<T>(),
			max_factorial<T>() + 1);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
atan_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::atan(x);
	}
#endif
	return atan_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
atan_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) ?
			hamon::copysign(hamon::numbers::pi_fn<FloatType>() / 2, x) :
		hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		atan_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	アークタンジェントを取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argのアークタンジェントを返す
 *
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が +∞ の場合、+π/2 を返す。
 *	arg が -∞ の場合、-π/2 を返す。
 *	arg が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
atan(FloatType arg) HAMON_NOEXCEPT
{
	return detail::atan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
atanf(float arg) HAMON_NOEXCEPT
{
	return detail::atan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
atanl(long double arg) HAMON_NOEXCEPT
{
	return detail::atan_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
atan(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::atan_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ATAN_HPP
