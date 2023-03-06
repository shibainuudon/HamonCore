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
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#include <type_traits>	// is_constant_evaluated
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
tan_unchecked(float x) HAMON_NOEXCEPT
{
	return __builtin_tanf(x);
}

inline HAMON_CONSTEXPR double
tan_unchecked(double x) HAMON_NOEXCEPT
{
	return __builtin_tan(x);
}

inline HAMON_CONSTEXPR long double
tan_unchecked(long double x) HAMON_NOEXCEPT
{
	return __builtin_tanl(x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
tan_unchecked(T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::tan(x);
	}
#endif
	return sin_unchecked_ct(x) / cos_unchecked_ct(x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
tan_impl(FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::iszero(x) ?
			x :
		hamon::isinf(x) || hamon::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
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
HAMON_NODISCARD inline HAMON_CONSTEXPR float
tan(float arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
tanf(float arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
tan(double arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
tan(long double arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
tanl(long double arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(arg);
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
HAMON_NODISCARD inline HAMON_CONSTEXPR double
tan(IntegralType arg) HAMON_NOEXCEPT
{
	return detail::tan_impl(static_cast<double>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_TAN_HPP
