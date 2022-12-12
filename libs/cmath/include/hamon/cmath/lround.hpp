/**
 *	@file	lround.hpp
 *
 *	@brief	lround 関数の定義
 */

#ifndef HAMON_CMATH_LROUND_HPP
#define HAMON_CMATH_LROUND_HPP

#include <hamon/cmath/round.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR long
lround_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_lroundf(x);
}

inline HAMON_CONSTEXPR long
lround_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_lround(x);
}

inline HAMON_CONSTEXPR long
lround_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_lroundl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR long
lround_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::lround(x);
	}
#endif
	return static_cast<long>(round_unchecked(x));
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR long
lround_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			std::numeric_limits<long>::min() :
		x < (FloatType)std::numeric_limits<long>::min() ?
			std::numeric_limits<long>::min() :
		x > (FloatType)std::numeric_limits<long>::max() ?
			std::numeric_limits<long>::max() :
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
inline HAMON_CONSTEXPR long
lround(float arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline HAMON_CONSTEXPR long
lroundf(float arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline HAMON_CONSTEXPR long
lround(double arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline HAMON_CONSTEXPR long
lround(long double arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline HAMON_CONSTEXPR long
lroundl(long double arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
inline HAMON_CONSTEXPR long
lround(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::lround_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_LROUND_HPP
