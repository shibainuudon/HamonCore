/**
 *	@file	isgreater.hpp
 *
 *	@brief	isgreater 関数の定義
 */

#ifndef HAMON_CMATH_ISGREATER_HPP
#define HAMON_CMATH_ISGREATER_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isgreater_impl_ct(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return !hamon::isnan(x) && !hamon::isnan(y) && (x > y);
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
isgreater_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC) || (defined(HAMON_CLANG) && HAMON_CLANG >= 200000)
	// gcc または clang-20以上 なら constexpr
	return __builtin_isgreater(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_isgreater)
	return hamon::is_constant_evaluated() ? isgreater_impl_ct(x, y) : __builtin_isgreater(x, y);
#else
	return isgreater_impl_ct(x, y);
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
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isgreater(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::isgreater_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
isgreater(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::isgreater_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISGREATER_HPP
