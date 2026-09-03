/**
 *	@file	sqrt.hpp
 *
 *	@brief	sqrt 関数の定義
 */

#ifndef HAMON_CMATH_SQRT_HPP
#define HAMON_CMATH_SQRT_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T
sqrt_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T s = x > 1 ? x : T(1);
	for (;;)
	{
		T const s1 = (x / s + s) / 2;
		if (s <= s1)
		{
			break;
		}
		s = s1;
	}
	return s;
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
sqrt_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::sqrt(x);
}

inline HAMON_CXX11_CONSTEXPR float
sqrt_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sqrtf(x);
#elif HAMON_HAS_BUILTIN(__builtin_sqrtf)
	return hamon::is_constant_evaluated() ? sqrt_unchecked_ct(x) : __builtin_sqrtf(x);
#else
	return hamon::is_constant_evaluated() ? sqrt_unchecked_ct(x) : sqrt_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
sqrt_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sqrt(x);
#elif HAMON_HAS_BUILTIN(__builtin_sqrt)
	return hamon::is_constant_evaluated() ? sqrt_unchecked_ct(x) : __builtin_sqrt(x);
#else
	return hamon::is_constant_evaluated() ? sqrt_unchecked_ct(x) : sqrt_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
sqrt_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sqrtl(x);
#elif HAMON_HAS_BUILTIN(__builtin_sqrtl)
	return hamon::is_constant_evaluated() ? sqrt_unchecked_ct(x) : __builtin_sqrtl(x);
#else
	return hamon::is_constant_evaluated() ? sqrt_unchecked_ct(x) : sqrt_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
sqrt_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		x < 0 ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::isinf(x) || hamon::iszero(x) ?
			x :
		sqrt_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	平方根を取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの平方根を返す
 *
 *	arg が 0 よりも小さい場合、NaNを返す。
 *	arg が +∞ の場合、argをそのまま返す。
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が NaN の場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
sqrt(FloatType arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
sqrt(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(static_cast<double>(arg));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
sqrtf(float arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
sqrtl(long double arg) HAMON_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

}	// namespace hamon

#endif // HAMON_CMATH_SQRT_HPP
