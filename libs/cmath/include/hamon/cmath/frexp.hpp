/**
 *	@file	frexp.hpp
 *
 *	@brief	frexp 関数の定義
 */

#ifndef HAMON_CMATH_FREXP_HPP
#define HAMON_CMATH_FREXP_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/logb.hpp>
#include <hamon/cmath/scalbn.hpp>
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
frexp_unchecked_ct(T x, int* exp) HAMON_NOEXCEPT
{
	*exp = static_cast<int>(1 + hamon::logb(x));
	return hamon::scalbn(x, -(*exp));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
frexp_unchecked_rt(T x, int* exp) HAMON_NOEXCEPT
{
	// TODO
	return std::frexp(x, exp);
}

inline HAMON_CXX11_CONSTEXPR float
frexp_unchecked(float x, int* exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_frexpf(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_frexpf)
	return hamon::is_constant_evaluated() ? frexp_unchecked_ct(x, exp) : __builtin_frexpf(x, exp);
#else
	return hamon::is_constant_evaluated() ? frexp_unchecked_ct(x, exp) : frexp_unchecked_rt(x, exp);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
frexp_unchecked(double x, int* exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_frexp(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_frexp)
	return hamon::is_constant_evaluated() ? frexp_unchecked_ct(x, exp) : __builtin_frexp(x, exp);
#else
	return hamon::is_constant_evaluated() ? frexp_unchecked_ct(x, exp) : frexp_unchecked_rt(x, exp);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
frexp_unchecked(long double x, int* exp) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_frexpl(x, exp);
#elif HAMON_HAS_BUILTIN(__builtin_frexpl)
	return hamon::is_constant_evaluated() ? frexp_unchecked_ct(x, exp) : __builtin_frexpl(x, exp);
#else
	return hamon::is_constant_evaluated() ? frexp_unchecked_ct(x, exp) : frexp_unchecked_rt(x, exp);
#endif
}

template <typename FloatType>
HAMON_CXX14_CONSTEXPR FloatType
frexp_impl(FloatType x, int* exp) HAMON_NOEXCEPT
{
	if (hamon::iszero(x))
	{
		*exp = 0;
		return x;
	}

	if (hamon::isinf(x)  ||
		hamon::isnan(x))
	{
		return x;
	}

	return frexp_unchecked(x, exp);
}

}	// namespace detail

/**
 *	@brief	引数を正規化された仮数部と 2 の累乗へ分解する
 *
 *	@param	arg	算術型の値
 *
 *	frexp関数は引数argを仮数部と指数部に分解し、仮数部を戻り値で返し、指数を*expに書き込んで返す。
 *
 *	arg が ±0 の場合、 arg をそのまま返し、*expに0がセットされる
 *	arg が ±∞ の場合、 arg をそのまま返し、*expの値は不定
 *	arg が NaN の場合、NaN を返し、*expの値は不定
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_CXX14_CONSTEXPR FloatType
frexp(FloatType arg, int* exp) HAMON_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_CXX14_CONSTEXPR double
frexp(IntegralType arg, int* exp) HAMON_NOEXCEPT
{
	return detail::frexp_impl(static_cast<double>(arg), exp);
}

inline HAMON_CXX14_CONSTEXPR float
frexpf(float arg, int* exp) HAMON_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

inline HAMON_CXX14_CONSTEXPR long double
frexpl(long double arg, int* exp) HAMON_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

}	// namespace hamon

#endif // HAMON_CMATH_FREXP_HPP
