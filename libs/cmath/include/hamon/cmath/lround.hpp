﻿/**
 *	@file	lround.hpp
 *
 *	@brief	lround 関数の定義
 */

#ifndef HAMON_CMATH_LROUND_HPP
#define HAMON_CMATH_LROUND_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::lround;
using std::lroundf;
using std::lroundl;

}	// namespace hamon

#else

#include <hamon/cmath/round.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR long
lround_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_lroundf(x);
}

inline HAMON_CXX11_CONSTEXPR long
lround_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_lround(x);
}

inline HAMON_CXX11_CONSTEXPR long
lround_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_lroundl(x);
}

#else

template <typename T>
HAMON_CXX11_CONSTEXPR long
lround_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::lround(x);
	}
#endif
	return static_cast<long>(round_unchecked(x));
}

#endif

template <typename FloatType>
HAMON_CXX11_CONSTEXPR long
lround_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<long>::min() :
		x < (FloatType)hamon::numeric_limits<long>::min() ?
			hamon::numeric_limits<long>::min() :
		x > (FloatType)hamon::numeric_limits<long>::max() ?
			hamon::numeric_limits<long>::max() :
		lround_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	四捨五入により丸めた整数値をlong型として得る。
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x を四捨五入により丸めた整数値を、long型の範囲に収めて返す。
 *
 *	ここで引数 x の四捨五入とは、x を最も近い整数に丸めるが、
 *	x の小数部分が 0.5 の場合には、x の符号が正負のいずれであってもゼロから遠い方向に丸めることを指す。
 *
 *	x が numeric_limits<long>::min() より小さい場合、numeric_limits<long>::min() を返す。
 *	x が numeric_limits<long>::max() より大きい場合、numeric_limits<long>::max() を返す。
 *	x が NaN の場合、numeric_limits<long>::min() を返す。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR long
lround(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::lround_impl(static_cast<type>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long
lroundf(float arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long
lroundl(long double arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_LROUND_HPP
