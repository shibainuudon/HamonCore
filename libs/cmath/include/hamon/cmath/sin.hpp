/**
 *	@file	sin.hpp
 *
 *	@brief	sin 関数の定義
 */

#ifndef HAMON_CMATH_SIN_HPP
#define HAMON_CMATH_SIN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
sin_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_sinf(x);
}

inline HAMON_CXX11_CONSTEXPR double
sin_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_sin(x);
}

inline HAMON_CXX11_CONSTEXPR long double
sin_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_sinl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
sin_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return -cos_unchecked(x + hamon::numbers::pi_fn<T>() / 2);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
sin_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::sin(x);
	}
#endif
	return sin_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
sin_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) || hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		sin_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	正弦（サイン）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argのサインを返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
sin(FloatType arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
sinf(float arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
sinl(long double arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
sin(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sin_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_SIN_HPP
