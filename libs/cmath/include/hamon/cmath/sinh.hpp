/**
 *	@file	sinh.hpp
 *
 *	@brief	sinh 関数の定義
 */

#ifndef HAMON_CMATH_SINH_HPP
#define HAMON_CMATH_SINH_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
sinh_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_sinhf(x);
}

inline HAMON_CXX11_CONSTEXPR double
sinh_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_sinh(x);
}

inline HAMON_CXX11_CONSTEXPR long double
sinh_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_sinhl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
sinh_unchecked_ct_1(T x) HAMON_NOEXCEPT
{
	return T(0.5) * x - T(0.5) / x;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
sinh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return sinh_unchecked_ct_1(hamon::exp(x));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
sinh_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::sinh(x);
	}
#endif
	return sinh_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
sinh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) || hamon::isinf(x) || hamon::isnan(x) ?
			x :
		sinh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	双曲線正弦（ハイパボリックサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの双曲線正弦を返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
sinh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
sinhf(float arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
sinhl(long double arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
sinh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_SINH_HPP
