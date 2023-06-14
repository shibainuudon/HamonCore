/**
 *	@file	almost_equal.hpp
 *
 *	@brief	almost_equal
 */

#ifndef HAMON_CMATH_ALMOST_EQUAL_HPP
#define HAMON_CMATH_ALMOST_EQUAL_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/arithmetic_promote.hpp>
#include <hamon/config.hpp>
#include <limits>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
tmax(T a, T b) HAMON_NOEXCEPT
{
	return b < a ? a : b;
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
eps(T x, T y) HAMON_NOEXCEPT
{
	return std::numeric_limits<T>::epsilon() *
		tmax(tmax(hamon::fabs(x), hamon::fabs(y)), T(1));
}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4056)	// 浮動小数点数の定数演算でオーバーフローしました。

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
inline HAMON_CXX11_CONSTEXPR bool
almost_equal_impl(FloatType x, FloatType y, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	return
		(hamon::isnan(x) || hamon::isnan(y) ||
		 hamon::isinf(x) || hamon::isinf(y)) ?
			x == y :
		x == y ||
		hamon::fabs(x - y) <= eps(x, y);
}

HAMON_WARNING_POP()

template <typename IntType>
inline HAMON_CXX11_CONSTEXPR bool
almost_equal_impl(IntType x, IntType y, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return x == y;
}

}	// namespace detail

/**
 *	@brief	2つの値がほぼ同じかどうかを調べる
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	xとyがほぼ同じ値ならtrue
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
almost_equal(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::arithmetic_promote_t<Arithmetic1, Arithmetic2>;
	return detail::almost_equal_impl(
		static_cast<type>(x), static_cast<type>(y),
		hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif // HAMON_CMATH_ALMOST_EQUAL_HPP
