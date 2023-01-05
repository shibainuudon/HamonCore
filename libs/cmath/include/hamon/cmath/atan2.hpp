/**
 *	@file	atan2.hpp
 *
 *	@brief	atan2 関数の定義
 */

#ifndef HAMON_CMATH_ATAN2_HPP
#define HAMON_CMATH_ATAN2_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isfinite.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/copysign.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/atan.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <cmath>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CONSTEXPR float
atan2_unchecked(float y, float x) HAMON_NOEXCEPT
{
	return __builtin_atan2f(y, x);
}

inline HAMON_CONSTEXPR double
atan2_unchecked(double y, double x) HAMON_NOEXCEPT
{
	return __builtin_atan2(y, x);
}

inline HAMON_CONSTEXPR long double
atan2_unchecked(long double y, long double x) HAMON_NOEXCEPT
{
	return __builtin_atan2l(y, x);
}

#else

template <typename T>
inline HAMON_CONSTEXPR T
atan2_unchecked_ct_1(T y, T x, T pi) HAMON_NOEXCEPT
{
	return
		x < 0 ?
			hamon::atan(y / x) + (y < 0 ? -pi : pi) :
			hamon::atan(y / x);
}

template <typename T>
inline HAMON_CONSTEXPR T
atan2_unchecked_ct(T y, T x) HAMON_NOEXCEPT
{
	return atan2_unchecked_ct_1(y, x, hamon::numbers::pi_fn<T>());
}

template <typename T>
inline HAMON_CONSTEXPR T
atan2_unchecked(T y, T x) HAMON_NOEXCEPT
{
#if defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811
	if (!std::is_constant_evaluated())
	{
		return std::atan2(y, x);
	}
#endif
	return atan2_unchecked_ct(y, x);
}

#endif

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
atan2_impl_1(FloatType y, FloatType x, FloatType pi) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isnan(y) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(y) ?
			hamon::signbit(x) ?
				hamon::copysign(pi, y) :
				hamon::copysign(FloatType(0), y) :
		hamon::isinf(y) ?
			hamon::isinf(x) ?
				hamon::signbit(x) ?
					hamon::copysign(pi*3/4, y) :
					hamon::copysign(pi/4, y) :
				hamon::copysign(pi/2, y) :
		hamon::iszero(x) ?
			hamon::copysign(pi/2, y) :
		hamon::isinf(x) && hamon::isfinite(y) ?
			hamon::signbit(x) ?
				hamon::copysign(pi, y) :
				hamon::copysign(FloatType(0), y) :
		atan2_unchecked(y, x);
}

template <typename FloatType>
inline HAMON_CONSTEXPR FloatType
atan2_impl(FloatType y, FloatType x) HAMON_NOEXCEPT
{
	return atan2_impl_1(y, x, hamon::numbers::pi_fn<FloatType>());
}

}	// namespace detail

/**
 *	@brief	アークタンジェントを取得する
 *
 *	@param	y	算術型の値
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、y/xのアークタンジェントを返す
 *
 *	y が ±0  かつ、x が負の値または -0 の場合、±π を返す。
 *	y が ±0  かつ、x が正の値または +0 の場合、±0  を返す。
 *	y が ±∞ かつ、x が有限の値の場合、±π/2  を返す。
 *	y が ±∞ かつ、x が -∞ の場合、±3π/4  を返す。
 *	y が ±∞ かつ、x が +∞ の場合、±π/4 を返す。
 *	x が ±0  かつ、y が負の値の場合、-π/2 を返す。
 *	x が ±0  かつ、y が正の値の場合、+π/2 を返す。
 *	x が -∞  かつ、y が有限の正の値の場合、+π を返す。
 *	x が -∞  かつ、y が有限の負の値の場合、-π を返す。
 *	x が +∞  かつ、y が有限の正の値の場合、+0 を返す。
 *	x が +∞  かつ、y が有限の負の値の場合、-0 を返す。
 *	x か y の少なくともどちらかが NaN の場合、NaN を返す。
 */
HAMON_NODISCARD inline HAMON_CONSTEXPR float
atan2(float y, float x) HAMON_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR float
atan2f(float y, float x) HAMON_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR double
atan2(double y, double x) HAMON_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
atan2(long double y, long double x) HAMON_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

HAMON_NODISCARD inline HAMON_CONSTEXPR long double
atan2l(long double y, long double x) HAMON_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
atan2(Arithmetic1 y, Arithmetic2 x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::atan2_impl(static_cast<type>(y), static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_ATAN2_HPP
