/**
 *	@file	erfc.hpp
 *
 *	@brief	erfc 関数の定義
 */

#ifndef HAMON_CMATH_ERFC_HPP
#define HAMON_CMATH_ERFC_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/erf.hpp>
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

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
erfc_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return T(1) - hamon::erf(x);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
erfc_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::erfc(x);
	}
#endif
	return erfc_unchecked_ct(x);
}

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
erfc_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x)?
			x :
		hamon::isinf(x) ?
			hamon::signbit(x) ?
				FloatType(+2.0) :
				FloatType(+0.0) :
		erfc_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	算術型の相補誤差関数 (complementary error function) を求める。
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の相補誤差関数を返す。
 *
 *	arg が +∞  の場合、+0 を返す。
 *	arg が -∞  の場合、2  を返す。
 *	arg が NaN の場合、NaNを返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
erfc(FloatType arg) HAMON_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
erfcf(float arg) HAMON_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
erfcl(long double arg) HAMON_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
erfc(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::erfc_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ERFC_HPP
