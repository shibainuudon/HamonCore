/**
 *	@file	trunc.hpp
 *
 *	@brief	trunc
 */

#ifndef HAMON_CMATH_TRUNC_HPP
#define HAMON_CMATH_TRUNC_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <cstdint>
#include <type_traits>
#include <limits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
trunc_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_truncf(x);
}

inline HAMON_CONSTEXPR double
trunc_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_trunc(x);
}

inline HAMON_CONSTEXPR long double
trunc_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_truncl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
trunc_unchecked(T x) HAMON_NOEXCEPT
{
	return x < 0 ?
		-static_cast<T>(static_cast<std::uintmax_t>(-x)) :
		 static_cast<T>(static_cast<std::uintmax_t>( x));
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
trunc_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isinf(x) || hamon::iszero(x) ?
			x :
		trunc_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	ゼロ方向への丸め
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg をゼロ方向に丸めた整数値
 *
 *	ゼロ方向に丸めた整数値とは、絶対値が引数 arg の絶対値以下で、かつ、引数 arg に最も近い整数値である。
 *
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline HAMON_CONSTEXPR float
trunc(float arg) HAMON_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline HAMON_CONSTEXPR float
truncf(float arg) HAMON_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline HAMON_CONSTEXPR double
trunc(double arg) HAMON_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline HAMON_CONSTEXPR long double
trunc(long double arg) HAMON_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline HAMON_CONSTEXPR long double
truncl(long double arg) HAMON_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

template <
	typename IntegralType,
	typename = hamon::enable_if_t<
		std::is_integral<IntegralType>::value
	>
>
inline HAMON_CONSTEXPR double
trunc(IntegralType arg) HAMON_NOEXCEPT
{
	return static_cast<double>(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_TRUNC_HPP
