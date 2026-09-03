/**
 *	@file	nexttoward.hpp
 *
 *	@brief	nexttoward 関数の定義
 */

#ifndef HAMON_CMATH_NEXTTOWARD_HPP
#define HAMON_CMATH_NEXTTOWARD_HPP

#include <hamon/cmath/nextafter.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINT(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
nexttoward(FloatType from, long double to) HAMON_NOEXCEPT
{
	return hamon::nextafter(from, static_cast<FloatType>(to));
}

template <HAMON_CONSTRAINT(hamon::integral, IntegralType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR double
nexttoward(IntegralType from, long double to) HAMON_NOEXCEPT
{
	return hamon::nexttoward(static_cast<double>(from), to);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR float
nexttowardf(float from, long double to) HAMON_NOEXCEPT
{
	return hamon::nexttoward(from, to);
}

HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR long double
nexttowardl(long double from, long double to) HAMON_NOEXCEPT
{
	return hamon::nexttoward(from, to);
}

}	// namespace hamon

#endif // HAMON_CMATH_NEXTTOWARD_HPP
