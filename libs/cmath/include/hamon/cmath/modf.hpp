/**
 *	@file	modf.hpp
 *
 *	@brief	modf 関数の定義
 */

#ifndef HAMON_CMATH_MODF_HPP
#define HAMON_CMATH_MODF_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/trunc.hpp>
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

template <typename T>
inline HAMON_CXX14_CONSTEXPR T
modf_unchecked(T x, T* iptr) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::modf(x, iptr);
	}
#endif
	*iptr = hamon::trunc(x);
	return hamon::copysign(x - (*iptr), x);
}

template <typename FloatType>
inline HAMON_CXX14_CONSTEXPR FloatType
modf_impl(FloatType x, FloatType* iptr) HAMON_NOEXCEPT
{
	if (hamon::iszero(x))
	{
		*iptr = x;
		return x;
	}

	if (hamon::isinf(x))
	{
		*iptr = x;
		return hamon::copysign(FloatType(0), x);
	}

	if (hamon::isnan(x))
	{
		*iptr = x;
		return x;
	}

	return modf_unchecked(x, iptr);
}

}	// namespace detail

/**
 *	@brief	引数を整数部と小数部に分割します
 *
 *	@param	x	算術型の値
 *
 *	@return	引数xの小数部を符号付きとして返す。また、引数xの整数部を*iptrに書き込む。
 *
 *	x が ±0  の場合、±0 を返し、*iptrに ±0 がセットされる。
 *	x が ±∞  の場合、±0 を返し、*iptrに ±∞ がセットされる。
 *	x が NaN の場合、NaN を返し、*iptrに NaN がセットされる。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
inline HAMON_CXX14_CONSTEXPR FloatType
modf(FloatType x, FloatType* iptr) HAMON_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CXX14_CONSTEXPR double
modf(IntegralType x, double* iptr) HAMON_NOEXCEPT
{
	return detail::modf_impl(static_cast<double>(x), iptr);
}

inline HAMON_CXX14_CONSTEXPR float
modff(float x, float* iptr) HAMON_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

inline HAMON_CXX14_CONSTEXPR long double
modfl(long double x, long double* iptr) HAMON_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

}	// namespace hamon

#endif // HAMON_CMATH_MODF_HPP
