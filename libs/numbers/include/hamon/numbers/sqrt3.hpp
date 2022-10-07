/**
 *	@file	sqrt3.hpp
 *
 *	@brief	3の平方根√3
 */

#ifndef HAMON_NUMBERS_SQRT3_HPP
#define HAMON_NUMBERS_SQRT3_HPP

#include <hamon/concepts/floating_point.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>
#if HAMON_HAS_INCLUDE(<numbers>) && (HAMON_CXX_STANDARD >= 20)
#include <numbers>
#endif

namespace hamon
{
namespace numbers
{

#if defined(__cpp_lib_math_constants) && (__cpp_lib_math_constants >= 201907L)

using std::numbers::sqrt3_v;
using std::numbers::sqrt3;

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T sqrt3_fn() HAMON_NOEXCEPT
{
	return std::numbers::sqrt3_v<T>;
}

#else

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
inline HAMON_CONSTEXPR T sqrt3_fn() HAMON_NOEXCEPT
{
	return static_cast<T>(1.732050807568877293527446341505872367L);
}

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <HAMON_CONSTRAINED_PARAM(hamon::floating_point, T)>
HAMON_INLINE_VAR HAMON_CONSTEXPR T sqrt3_v = sqrt3_fn<T>();

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR double sqrt3 = sqrt3_fn<double>();

#endif

}	// namespace numbers
}	// namespace hamon

#endif // HAMON_NUMBERS_SQRT3_HPP
