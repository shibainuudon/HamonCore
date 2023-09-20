/**
 *	@file	tanh.hpp
 *
 *	@brief	tanh 関数の定義
 */

#ifndef HAMON_CMATH_TANH_HPP
#define HAMON_CMATH_TANH_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
tanh_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_tanhf(x);
}

inline HAMON_CXX11_CONSTEXPR double
tanh_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_tanh(x);
}

inline HAMON_CXX11_CONSTEXPR long double
tanh_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_tanhl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
tanh_unchecked_ct_2(T t, T u) HAMON_NOEXCEPT
{
	return (t - u) / (t + u);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
tanh_unchecked_ct_1(T x) HAMON_NOEXCEPT
{
	return tanh_unchecked_ct_2(x, T(1) / x);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
tanh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return tanh_unchecked_ct_1(hamon::exp(x));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
tanh_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::tanh(x);
	}
#endif
	return tanh_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
tanh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) ?
			hamon::copysign(FloatType(1), x) :
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		tanh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	双曲線正接（ハイパボリックタンジェント）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの正接を返す
 *
 *	arg が ±0  の場合、±0を返す。
 *	arg が ±∞ の場合、±1を返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
tanh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
tanhf(float arg) HAMON_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
tanhl(long double arg) HAMON_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
tanh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::tanh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_TANH_HPP
