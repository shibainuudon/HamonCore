/**
 *	@file	nexttoward.hpp
 *
 *	@brief	nexttoward 関数の定義
 */

#ifndef HAMON_CMATH_NEXTTOWARD_HPP
#define HAMON_CMATH_NEXTTOWARD_HPP

#include <cmath>

#if defined(__cpp_lib_constexpr_cmath) && (__cpp_lib_constexpr_cmath >= 202202L)

namespace hamon
{

using std::nexttoward;
using std::nexttowardf;
using std::nexttowardl;

}	// namespace hamon

#else

#include <hamon/cmath/nextafter.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, FloatType)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR FloatType
nexttoward(FloatType from, long double to) HAMON_NOEXCEPT
{
	return hamon::nextafter(from, static_cast<FloatType>(to));
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, IntegralType)>
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

#endif

#endif // HAMON_CMATH_NEXTTOWARD_HPP
