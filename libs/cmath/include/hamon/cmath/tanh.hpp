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
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
tanh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const t = hamon::exp(x);
	T const u =  T(1) / t;
	return (t - u) / (t + u);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
tanh_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::tanh(x);
}

inline HAMON_CXX11_CONSTEXPR float
tanh_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_tanhf(x);
#elif HAMON_HAS_BUILTIN(__builtin_tanhf)
	return hamon::is_constant_evaluated() ? tanh_unchecked_ct(x) : __builtin_tanhf(x);
#else
	return hamon::is_constant_evaluated() ? tanh_unchecked_ct(x) : tanh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
tanh_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_tanh(x);
#elif HAMON_HAS_BUILTIN(__builtin_tanh)
	return hamon::is_constant_evaluated() ? tanh_unchecked_ct(x) : __builtin_tanh(x);
#else
	return hamon::is_constant_evaluated() ? tanh_unchecked_ct(x) : tanh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
tanh_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_tanhl(x);
#elif HAMON_HAS_BUILTIN(__builtin_tanhl)
	return hamon::is_constant_evaluated() ? tanh_unchecked_ct(x) : __builtin_tanhl(x);
#else
	return hamon::is_constant_evaluated() ? tanh_unchecked_ct(x) : tanh_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
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

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
tanh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::tanh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_TANH_HPP
