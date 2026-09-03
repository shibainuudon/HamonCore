/**
 *	@file	sinh.hpp
 *
 *	@brief	sinh 関数の定義
 */

#ifndef HAMON_CMATH_SINH_HPP
#define HAMON_CMATH_SINH_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
sinh_unchecked_ct(T x) HAMON_NOEXCEPT
{
	T const y = hamon::exp(x);
	return T(0.5) * y - T(0.5) / y;
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
sinh_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::sinh(x);
}

inline HAMON_CXX11_CONSTEXPR float
sinh_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sinhf(x);
#elif HAMON_HAS_BUILTIN(__builtin_sinhf)
	return hamon::is_constant_evaluated() ? sinh_unchecked_ct(x) : __builtin_sinhf(x);
#else
	return hamon::is_constant_evaluated() ? sinh_unchecked_ct(x) : sinh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
sinh_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sinh(x);
#elif HAMON_HAS_BUILTIN(__builtin_sinh)
	return hamon::is_constant_evaluated() ? sinh_unchecked_ct(x) : __builtin_sinh(x);
#else
	return hamon::is_constant_evaluated() ? sinh_unchecked_ct(x) : sinh_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
sinh_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_sinhl(x);
#elif HAMON_HAS_BUILTIN(__builtin_sinhl)
	return hamon::is_constant_evaluated() ? sinh_unchecked_ct(x) : __builtin_sinhl(x);
#else
	return hamon::is_constant_evaluated() ? sinh_unchecked_ct(x) : sinh_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
sinh_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) || hamon::isinf(x) || hamon::isnan(x) ?
			x :
		sinh_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	双曲線正弦（ハイパボリックサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの双曲線正弦を返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
sinh(FloatType arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
sinhf(float arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
sinhl(long double arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
sinh(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::sinh_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_SINH_HPP
