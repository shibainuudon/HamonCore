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
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
erfc_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return T(1) - hamon::erf(x);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
erfc_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::erfc(x);
}

inline HAMON_CXX11_CONSTEXPR float
erfc_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_erfcf(x);
#elif HAMON_HAS_BUILTIN(__builtin_erfcf)
	return hamon::is_constant_evaluated() ? erfc_unchecked_ct(x) : __builtin_erfcf(x);
#else
	return hamon::is_constant_evaluated() ? erfc_unchecked_ct(x) : erfc_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
erfc_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_erfc(x);
#elif HAMON_HAS_BUILTIN(__builtin_erfc)
	return hamon::is_constant_evaluated() ? erfc_unchecked_ct(x) : __builtin_erfc(x);
#else
	return hamon::is_constant_evaluated() ? erfc_unchecked_ct(x) : erfc_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
erfc_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_erfcl(x);
#elif HAMON_HAS_BUILTIN(__builtin_erfcl)
	return hamon::is_constant_evaluated() ? erfc_unchecked_ct(x) : __builtin_erfcl(x);
#else
	return hamon::is_constant_evaluated() ? erfc_unchecked_ct(x) : erfc_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
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

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
erfc(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::erfc_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ERFC_HPP
