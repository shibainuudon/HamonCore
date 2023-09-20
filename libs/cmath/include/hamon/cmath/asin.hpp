/**
 *	@file	asin.hpp
 *
 *	@brief	asin 関数の定義
 */

#ifndef HAMON_CMATH_ASIN_HPP
#define HAMON_CMATH_ASIN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/cmath/sqrt.hpp>
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
asin_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_asinf(x);
}

inline HAMON_CXX11_CONSTEXPR double
asin_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_asin(x);
}

inline HAMON_CXX11_CONSTEXPR long double
asin_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_asinl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asin_impl_center_1(T x, T x2) HAMON_NOEXCEPT
{
	return ((((((((((((
		T( 0.0316658385792867081040808)) * x2 +
		T(-0.0158620440988475212803145)) * x2 +
		T( 0.0192942786775238654913582)) * x2 +
		T( 0.0066153165197009078340075)) * x2 +
		T( 0.0121483892822292648695383)) * x2 +
		T( 0.0138885410156894774969889)) * x2 +
		T( 0.0173593516996479249428647)) * x2 +
		T( 0.0223717830666671020710108)) * x2 +
		T( 0.0303819580081956423799529)) * x2 +
		T( 0.0446428568582815922683933)) * x2 +
		T( 0.0750000000029696112392353)) * x2 +
		T( 0.1666666666666558995379880)) * x2 * x + x;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asin_impl_center(T x) HAMON_NOEXCEPT
{
	return asin_impl_center_1(x, x * x);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asin_impl_tail(T x) HAMON_NOEXCEPT
{
	return (hamon::numbers::pi_fn<T>() / 2) + hamon::sqrt(T(1) - x) *
		(((((((((((((
			T(-0.0000121189820098929624806)) * x +
			T( 0.0001307564187657962919394)) * x +
			T(-0.0006702485124770180942917)) * x +
			T( 0.0021912255981979442677477)) * x +
			T(-0.0052049731575223952626203)) * x +
			T( 0.0097868293573384001221447)) * x +
			T(-0.0156746038587246716524035)) * x +
			T( 0.0229883479552557203133368)) * x +
			T(-0.0331919619444009606270380)) * x +
			T( 0.0506659694457588602631748)) * x +
			T(-0.0890259194305537131666744)) * x +
			T( 0.2145993335526539017488949)) * x +
			T(-1.5707961988153774692344105));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asin_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return
		x < T(-0.5) ?
			-asin_impl_tail(-x) :
		x > T(0.5) ?
			asin_impl_tail(x) :
			asin_impl_center(x);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
asin_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::asin(x);
	}
#endif
	return asin_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
asin_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) ?
			x :
		hamon::fabs(x) > FloatType(1) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		asin_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	アークサインを取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argのアークサインを返す
 *
 *	arg が ±0 の場合、arg をそのまま返す。
 *	|arg| > 1  の場合、NaN を返す。
 *	arg が NaN の場合、NaN を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
asin(FloatType arg) HAMON_NOEXCEPT
{
	return detail::asin_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
asinf(float arg) HAMON_NOEXCEPT
{
	return detail::asin_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
asinl(long double arg) HAMON_NOEXCEPT
{
	return detail::asin_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
asin(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::asin_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ASIN_HPP
