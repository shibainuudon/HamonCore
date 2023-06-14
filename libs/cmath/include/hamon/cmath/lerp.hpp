/**
 *	@file	lerp.hpp
 *
 *	@brief	lerp 関数の定義
 */

#ifndef HAMON_CMATH_LERP_HPP
#define HAMON_CMATH_LERP_HPP

#include <hamon/config.hpp>
#include <cmath>

#if defined(__cpp_lib_interpolate) && (__cpp_lib_interpolate >= 201902) &&	\
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000))

namespace hamon
{

using std::lerp;

}	// namespace hamon

#else

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
lerp_impl_2(T a, T b, T t, T x) HAMON_NOEXCEPT
{
	return (t > 1) == (b > a) ?
		(b < x ? x : b) :
		(b > x ? x : b);
}

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
lerp_impl(T a, T b, T t) HAMON_NOEXCEPT
{
	return
		((a <= 0 && b >= 0) || (a >= 0 && b <= 0)) ?
			(t * b + (1 - t) * a) :
		(t == 1) ?
			b :
		lerp_impl_2(a, b, t, a + t * (b - a));
}

}	// namespace detail

/**
 *	@brief	２つの値の間を線形補間します
 *
 *	@param	a		1つ目の値
 *	@param	b		2つ目の値
 *	@param	t		補間係数
 *	@return	２つの値を線形補間した値
 *
 *	tは 0.0 から 1.0 までの値を基本的には指定するが、1.0を超える指定も許可されている。
 *
 *	isfinite(a) && isfinite(b)である場合、戻り値rは以下のようになる：
 *	・t == 0である場合、r == a
 *	・t == 1である場合、r == b
 *	・t >= 0 && t <= 1である場合、isfinite(r) != 0
 *	・isfinite(t) && a == bである場合、r == a
 *	・isfinite(t) || !isnan(t) && b - a != 0である場合、!isnan(r)
 * 
 *	比較関数CMP(x, y)を、x > yであれば1、x < yであれば-1、そうでなければ0を返すものであるとして、
 *	あらゆる時間値t1とt2についてCMP(lerp(a,b,t2), lerp(a,b,t1))、CMP(t2, t1)、CMP(b,a)はいずれも非負となる
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
lerp(FloatType a, FloatType b, FloatType t) HAMON_NOEXCEPT
{
	return detail::lerp_impl(a, b, t);
}

}	// namespace hamon

#endif

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief
 *
 *	@note	LWG-3223 により、このオーバーロードが標準に含まれるかどうかは不透明である。
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic3)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
lerp(Arithmetic1 x, Arithmetic2 y, Arithmetic3 z) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return hamon::lerp(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
}

}	// namespace hamon

#endif // HAMON_CMATH_LERP_HPP
