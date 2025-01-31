/**
 *	@file	isgreater.hpp
 *
 *	@brief	isgreater 関数の定義
 */

#ifndef HAMON_CMATH_ISGREATER_HPP
#define HAMON_CMATH_ISGREATER_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::isgreater;

}	// namespace hamon

#else

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isgreater_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isgreater(x, y);
#else
	return !hamon::isnan(x) && !hamon::isnan(y) && (x > y);
#endif
}

}	// namespace detail

/**
 *	@brief	xがyより大きいかどうかを判定する
 *
 *	@param	x
 *	@param	y
 *
 *	@return x > y
 *
 *	@note	isgreater(x, y)の値は、常に x > y と等しい。
 *			ただし、isgreaterはxとyが順序付けられていない場合に浮動小数点例外を生成しない。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isgreater(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::isgreater_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isgreater(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::isgreater_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif

#endif // HAMON_CMATH_ISGREATER_HPP
