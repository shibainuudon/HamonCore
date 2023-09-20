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
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <cmath>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CXX11_CONSTEXPR T
fmod_unchecked(T x, T y) HAMON_NOEXCEPT
{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return std::fmod(x, y);
	}
#endif
	return x - (hamon::trunc(x / y) * y);
}

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
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
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
fmod(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::fmod_impl(x, y);
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

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
fmod(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmod_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_FMOD_HPP
