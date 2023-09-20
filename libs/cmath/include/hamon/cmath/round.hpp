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
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
round_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_roundf(x);
}

inline HAMON_CXX11_CONSTEXPR double
round_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_round(x);
}

inline HAMON_CXX11_CONSTEXPR long double
round_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_roundl(x);
}

#else

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
round_unchecked_ct_1(T x, T x0) HAMON_NOEXCEPT
{
	return hamon::fabs(x - x0) < T(0.5) ?
		x0 :
		x0 + (x < 0 ? -T(1) : T(1));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
round_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return round_unchecked_ct_1(x, trunc_unchecked(x));
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
round_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::round(x);
	}
#endif
	return round_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
round(FloatType arg) HAMON_NOEXCEPT
{
	return detail::round_impl(arg);
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

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR double
round(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::round_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ROUND_HPP
