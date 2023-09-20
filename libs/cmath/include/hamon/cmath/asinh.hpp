/**
 *	@file	asinh.hpp
 *
 *	@brief	asinh 関数の定義
 */

#ifndef HAMON_CMATH_ASINH_HPP
#define HAMON_CMATH_ASINH_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
asinh_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_asinhf(x);
}

inline HAMON_CXX11_CONSTEXPR double
asinh_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_asinh(x);
}

inline HAMON_CXX11_CONSTEXPR long double
asinh_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_asinhl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asinh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return hamon::log(x + hamon::sqrt(x * x + 1));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asinh_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::asinh(x);
	}
#endif
	return asinh_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
asinh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) || hamon::isinf(x) || hamon::isnan(x) ?
			x :
		asinh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	逆双曲線正弦（アークハイパボリックサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの逆双曲線正弦を返す
 *
 *	arg が ±0  の場合、arg をそのまま返す。
 *	arg が ±∞ の場合、arg をそのまま返す。
 *	arg が NaN  の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
asinh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
asinhf(float arg) HAMON_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
asinhl(long double arg) HAMON_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
asinh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::asinh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ASINH_HPP
