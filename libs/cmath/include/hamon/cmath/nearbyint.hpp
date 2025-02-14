/**
 *	@file	nearbyint.hpp
 *
 *	@brief	nearbyint 関数の定義
 */

#ifndef HAMON_CMATH_NEARBYINT_HPP
#define HAMON_CMATH_NEARBYINT_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
nearbyint_unchecked(T x) HAMON_NOEXCEPT
{
	return std::nearbyint(x);
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
nearbyint_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isinf(x) || hamon::iszero(x) ?
			x :
		nearbyint_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	現在の丸めモードで整数値に丸めた値を得る
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg を現在の丸めモードで整数値に丸めた値
 *
 *	arg が ±∞  の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
nearbyint(FloatType arg) HAMON_NOEXCEPT
{
	return detail::nearbyint_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
nearbyint(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::nearbyint_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
nearbyintf(float arg) HAMON_NOEXCEPT
{
	return detail::nearbyint_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
nearbyintl(long double arg) HAMON_NOEXCEPT
{
	return detail::nearbyint_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_NEARBYINT_HPP
