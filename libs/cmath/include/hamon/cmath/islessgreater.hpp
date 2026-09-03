/**
 *	@file	islessgreater.hpp
 *
 *	@brief	islessgreater 関数の定義
 */

#ifndef HAMON_CMATH_ISLESSGREATER_HPP
#define HAMON_CMATH_ISLESSGREATER_HPP

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
islessgreater_impl_ct(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return !hamon::isnan(x) && !hamon::isnan(y) && ((x < y) || (x > y));
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
islessgreater_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC) || (defined(HAMON_CLANG) && HAMON_CLANG >= 200000)
	// gcc または clang-20以上 なら constexpr
	return __builtin_islessgreater(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_islessgreater)
	return hamon::is_constant_evaluated() ? islessgreater_impl_ct(x, y) : __builtin_islessgreater(x, y);
#else
	return islessgreater_impl_ct(x, y);
#endif
}

}	// namespace detail

/**
 *	@brief	xがyより小さいか、あるいは大きいかどうかを判定する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return x < y || x > y
 *
 *	@note	islessgreater(x, y)の値は、常に x < y || x > y と等しい。
 *			ただし、islessgreaterはxとyが順序付けられていない場合に浮動小数点例外を生成しない。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
islessgreater(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::islessgreater_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
islessgreater(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::islessgreater_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISLESSGREATER_HPP
