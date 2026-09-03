/**
 *	@file	rint.hpp
 *
 *	@brief	rint 関数の定義
 */

#ifndef HAMON_CMATH_RINT_HPP
#define HAMON_CMATH_RINT_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
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
rint_unchecked_ct(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::rint(x);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
rint_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::rint(x);
}

inline HAMON_CXX11_CONSTEXPR float
rint_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_rintf(x);
#elif HAMON_HAS_BUILTIN(__builtin_rintf)
	return hamon::is_constant_evaluated() ? rint_unchecked_ct(x) : __builtin_rintf(x);
#else
	return hamon::is_constant_evaluated() ? rint_unchecked_ct(x) : rint_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
rint_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_rint(x);
#elif HAMON_HAS_BUILTIN(__builtin_rint)
	return hamon::is_constant_evaluated() ? rint_unchecked_ct(x) : __builtin_rint(x);
#else
	return hamon::is_constant_evaluated() ? rint_unchecked_ct(x) : rint_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
rint_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_rintl(x);
#elif HAMON_HAS_BUILTIN(__builtin_rintl)
	return hamon::is_constant_evaluated() ? rint_unchecked_ct(x) : __builtin_rintl(x);
#else
	return hamon::is_constant_evaluated() ? rint_unchecked_ct(x) : rint_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
rint_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isinf(x) || hamon::iszero(x) ?
			x :
		rint_unchecked(x);
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
rint(FloatType arg) HAMON_NOEXCEPT
{
	return detail::rint_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
rint(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::rint_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
rintf(float arg) HAMON_NOEXCEPT
{
	return detail::rint_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
rintl(long double arg) HAMON_NOEXCEPT
{
	return detail::rint_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_RINT_HPP
