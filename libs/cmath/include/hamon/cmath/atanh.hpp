/**
 *	@file	atanh.hpp
 *
 *	@brief	atanh 関数の定義
 */

#ifndef HAMON_CMATH_ATANH_HPP
#define HAMON_CMATH_ATANH_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/log.hpp>
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
atanh_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_atanhf(x);
}

inline HAMON_CXX11_CONSTEXPR double
atanh_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_atanh(x);
}

inline HAMON_CXX11_CONSTEXPR long double
atanh_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_atanhl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
atanh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log((1 + x) / (1 - x)) / 2;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
atanh_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::atanh(x);
	}
#endif
	return atanh_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
atanh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			x :
		x == FloatType(1) ?
			hamon::numeric_limits<FloatType>::infinity() :
		x == FloatType(-1) ?
			-hamon::numeric_limits<FloatType>::infinity() :
		hamon::fabs(x) > FloatType(1) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		atanh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	逆双曲線正接（アークハイパボリックタンジェント）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの逆双曲線正接を返す
 *
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が ±1 の場合、±∞を返す。
 *	|arg| > 1  の場合、NaN を返す。
 *	arg が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
atanh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
atanhf(float arg) HAMON_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
atanhl(long double arg) HAMON_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
atanh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::atanh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ATANH_HPP
