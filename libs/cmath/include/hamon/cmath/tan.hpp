/**
 *	@file	tan.hpp
 *
 *	@brief	tan 関数の定義
 */

#ifndef HAMON_CMATH_TAN_HPP
#define HAMON_CMATH_TAN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/cos.hpp>
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
HAMON_CXX11_CONSTEXPR T
tan_unchecked_ct(T x) HAMON_NOEXCEPT
{
	return sin_unchecked_ct(x) / cos_unchecked_ct(x);
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
tan_unchecked_rt(T x) HAMON_NOEXCEPT
{
	// TODO
	return std::tan(x);
}

inline HAMON_CXX11_CONSTEXPR float
tan_unchecked(float x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_tanf(x);
#elif HAMON_HAS_BUILTIN(__builtin_tanf)
	return hamon::is_constant_evaluated() ? tan_unchecked_ct(x) : __builtin_tanf(x);
#else
	return hamon::is_constant_evaluated() ? tan_unchecked_ct(x) : tan_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
tan_unchecked(double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_tan(x);
#elif HAMON_HAS_BUILTIN(__builtin_tan)
	return hamon::is_constant_evaluated() ? tan_unchecked_ct(x) : __builtin_tan(x);
#else
	return hamon::is_constant_evaluated() ? tan_unchecked_ct(x) : tan_unchecked_rt(x);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
tan_unchecked(long double x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_tanl(x);
#elif HAMON_HAS_BUILTIN(__builtin_tanl)
	return hamon::is_constant_evaluated() ? tan_unchecked_ct(x) : __builtin_tanl(x);
#else
	return hamon::is_constant_evaluated() ? tan_unchecked_ct(x) : tan_unchecked_rt(x);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
tan_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) || hamon::isnan(x) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		tan_unchecked(x);
}

}	// namespace detail

/**
 *	@brief	正接（タンジェント）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argの正接を返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
tan(FloatType arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
tanf(float arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
tanl(long double arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
tan(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_TAN_HPP
