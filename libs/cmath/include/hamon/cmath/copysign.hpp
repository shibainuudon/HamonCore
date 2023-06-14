/**
 *	@file	copysign.hpp
 *
 *	@brief	copysign
 */

#ifndef HAMON_CMATH_COPYSIGN_HPP
#define HAMON_CMATH_COPYSIGN_HPP

#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)

inline HAMON_CXX11_CONSTEXPR float
copysign_impl(float x, float y) HAMON_NOEXCEPT
{
	return __builtin_copysignf(x, y);
}

inline HAMON_CXX11_CONSTEXPR double
copysign_impl(double x, double y) HAMON_NOEXCEPT
{
	return __builtin_copysign(x, y);
}

inline HAMON_CXX11_CONSTEXPR long double
copysign_impl(long double x, long double y) HAMON_NOEXCEPT
{
	return __builtin_copysignl(x, y);
}

#else

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR FloatType
copysign_impl(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return
		hamon::iszero(y) || hamon::isnan(y) ?
			x :
		hamon::signbit(x) != hamon::signbit(y) ?
			-x :
		x;
}

#endif

}	// namespace detail

/**
 *	@brief	std::copysign のconstexpr版
 *
 *	※std::copysignとの違い
 *	yが±0または±NaNのとき、xの符号は変更されない。
 *	これはconstexpr関数にするための制限。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR FloatType
copysign(FloatType x, FloatType y) HAMON_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
copysignf(float x, float y) HAMON_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
copysignl(long double x, long double y) HAMON_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
copysign(Arithmetic1 x, Arithmetic2 y) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::copysign_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace hamon

#endif // HAMON_CMATH_COPYSIGN_HPP
