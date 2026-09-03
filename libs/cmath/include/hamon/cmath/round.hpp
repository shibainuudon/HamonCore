/**
 *	@file	round.hpp
 *
 *	@brief	round 関数の定義
 */

#ifndef HAMON_CMATH_ROUND_HPP
#define HAMON_CMATH_ROUND_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/cmath/fabs.hpp>
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
round_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const x0 = trunc_unchecked(x);
	return hamon::fabs(x - x0) < T(0.5) ?
		x0 :
		x0 + (x < 0 ? -T(1) : T(1));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
round_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::round(x);
}

inline HAMON_CXX11_CONSTEXPR float
round_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_roundf(x);
#elif HAMON_HAS_BUILTIN(__builtin_roundf)
	return hamon::is_constant_evaluated() ? round_unchecked_ct(x) : __builtin_roundf(x);
#else
	return hamon::is_constant_evaluated() ? round_unchecked_ct(x) : round_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
round_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_round(x);
#elif HAMON_HAS_BUILTIN(__builtin_round)
	return hamon::is_constant_evaluated() ? round_unchecked_ct(x) : __builtin_round(x);
#else
	return hamon::is_constant_evaluated() ? round_unchecked_ct(x) : round_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
round_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_roundl(x);
#elif HAMON_HAS_BUILTIN(__builtin_roundl)
	return hamon::is_constant_evaluated() ? round_unchecked_ct(x) : __builtin_roundl(x);
#else
	return hamon::is_constant_evaluated() ? round_unchecked_ct(x) : round_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
round_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isinf(x) || hamon::isnan(x) || hamon::iszero(x) ?
			x :
		round_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	四捨五入により丸めた整数値を得る。
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x を四捨五入により丸めた整数値
 *
 *	ここで引数 x の四捨五入とは、x を最も近い整数に丸めるが、
 *	x の小数部分が 0.5 の場合には、x の符号が正負のいずれであってもゼロから遠い方向に丸めることを指す。
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0  の場合、xをそのまま返す。
 *	x が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
round(FloatType arg) HAMON_NOEXCEPT
{
	return detail::round_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
round(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::round_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
roundf(float arg) HAMON_NOEXCEPT
{
	return detail::round_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
roundl(long double arg) HAMON_NOEXCEPT
{
	return detail::round_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_ROUND_HPP
