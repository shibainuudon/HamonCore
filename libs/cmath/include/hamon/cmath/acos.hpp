/**
 *	@file	acos.hpp
 *
 *	@brief	acos 関数の定義
 */

#ifndef HAMON_CMATH_ACOS_HPP
#define HAMON_CMATH_ACOS_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/asin.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
acos_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_acosf(x);
}

inline HAMON_CXX11_CONSTEXPR double
acos_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_acos(x);
}

inline HAMON_CXX11_CONSTEXPR long double
acos_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_acosl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
acos_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return (hamon::numbers::pi_fn<T>() / 2) - hamon::asin(x);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
acos_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::acos(x);
	}
#endif
	return acos_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
acos_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			x :
		hamon::fabs(x) > FloatType(1) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		x == FloatType(1) ?
			FloatType(0) :
		acos_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	アークコサインを取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argのアークコサインを返す
 *
 *	arg が +1  の場合、+0  を返す。
 *	|arg| > 1  の場合、NaN を返す。
 *	arg が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
acos(FloatType arg) HAMON_NOEXCEPT
{
	return detail::acos_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
acosf(float arg) HAMON_NOEXCEPT
{
	return detail::acos_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
acosl(long double arg) HAMON_NOEXCEPT
{
	return detail::acos_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
acos(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::acos_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ACOS_HPP
