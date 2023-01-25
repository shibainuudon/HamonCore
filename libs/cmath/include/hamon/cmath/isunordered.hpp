﻿/**
 *	@file	isunordered.hpp
 *
 *	@brief	isunordered 関数の定義
 */

#ifndef HAMON_CMATH_ISUNORDERED_HPP
#define HAMON_CMATH_ISUNORDERED_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CONSTEXPR bool
isunordered_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isunordered(x, y);
#else
	return hamon::isnan(x) || hamon::isnan(y);
#endif
}

}	// namespace detail

/**
 *	@brief	引数が unordered かどうか判定する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return x と y が unordered なら true
 *
 *	x と y が unordered かどうか、つまり x と y の少なくとも一方が NaN かどうか を判定する。
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isunordered(float x, float y) HAMON_NOEXCEPT
{
	return detail::isunordered_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isunordered(double x, double y) HAMON_NOEXCEPT
{
	return detail::isunordered_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isunordered(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::isunordered_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
isunordered(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::isunordered_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISUNORDERED_HPP
