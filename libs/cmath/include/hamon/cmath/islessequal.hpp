/**
 *	@file	islessequal.hpp
 *
 *	@brief	islessequal 関数の定義
 */

#ifndef HAMON_CMATH_ISLESSEQUAL_HPP
#define HAMON_CMATH_ISLESSEQUAL_HPP

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
inline HAMON_CXX11_CONSTEXPR bool
islessequal_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_islessequal(x, y);
#else
	return !hamon::isnan(x) && !hamon::isnan(y) && (x <= y);
#endif
}

}	// namespace detail

/**
 *	@brief	xがyより小さいか、あるいは等しいかどうかを判定する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return x <= y
 *
 *	@note	islessequal(x, y)の値は、常に x <= y と等しい。
 *			ただし、islessequalはxとyが順序付けられていない場合に浮動小数点例外を生成しない。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
islessequal(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::islessequal_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
islessequal(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::islessequal_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISLESSEQUAL_HPP
