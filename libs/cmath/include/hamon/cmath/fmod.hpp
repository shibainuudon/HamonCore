/**
 *	@file	fmod.hpp
 *
 *	@brief	fmod 関数の定義
 */

#ifndef HAMON_CMATH_FMOD_HPP
#define HAMON_CMATH_FMOD_HPP

#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/trunc.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
HAMON_CXX11_CONSTEXPR T
fmod_unchecked_ct(T x, T y) HAMON_NOEXCEPT
{
	return (x - (hamon::trunc(x / y) * y));
}

template <typename T>
HAMON_CXX11_CONSTEXPR T
fmod_unchecked_rt(T x, T y) HAMON_NOEXCEPT
{
	// TODO
	return std::fmod(x, y);
}

inline HAMON_CXX11_CONSTEXPR float
fmod_unchecked(float x, float y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_fmodf(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_fmodf)
	return hamon::is_constant_evaluated() ? fmod_unchecked_ct(x, y) : __builtin_fmodf(x, y);
#else
	return hamon::is_constant_evaluated() ? fmod_unchecked_ct(x, y) : fmod_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR double
fmod_unchecked(double x, double y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_fmod(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_fmod)
	return hamon::is_constant_evaluated() ? fmod_unchecked_ct(x, y) : __builtin_fmod(x, y);
#else
	return hamon::is_constant_evaluated() ? fmod_unchecked_ct(x, y) : fmod_unchecked_rt(x, y);
#endif
}

inline HAMON_CXX11_CONSTEXPR long double
fmod_unchecked(long double x, long double y) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC)
	return __builtin_fmodl(x, y);
#elif HAMON_HAS_BUILTIN(__builtin_fmodl)
	return hamon::is_constant_evaluated() ? fmod_unchecked_ct(x, y) : __builtin_fmodl(x, y);
#else
	return hamon::is_constant_evaluated() ? fmod_unchecked_ct(x, y) : fmod_unchecked_rt(x, y);
#endif
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR FloatType
fmod_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::isnan(x) || hamon::isnan(y) || hamon::isinf(x) || hamon::iszero(y) ?
			hamon::numeric_limits<FloatType>::quiet_NaN() :
		hamon::iszero(x) || hamon::isinf(y) ?
			x :
		fmod_unchecked(x, y);
}

}	// namespace detail

/**
 *	@brief	剰余を求めます
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x / y の余り。符号はxの符号と同じです。
 *
 *	x が ±0  かつ、y が 0   でない場合、±0 を返す。
 *	x が ±∞ かつ、y が NaN でない場合、NaN を返す。
 *	y が ±0  かつ、x が NaN でない場合、NaN を返す。
 *	y が ±∞ かつ、x が 有限の値の場合、x をそのまま返す。
 *	x か y の少なくともどちらかがNaNの場合、NaNを返す。
 */
template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
fmod(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

template <
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
fmod(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmod_impl(static_cast<type>(x), static_cast<type>(y));
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
fmodf(float x, float y) HAMON_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
fmodl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

}	// namespace hamon

#endif // HAMON_CMATH_FMOD_HPP
